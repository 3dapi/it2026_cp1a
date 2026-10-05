#include "Ui.h"

#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <string>
#include <thread>

#include "glc2d.h"

namespace {

constexpr double kPi = 3.14159265358979323846;
constexpr int kTableCenterX = 640;
constexpr int kTableCenterY = 345;
constexpr double kSeatRadiusX = 520.0;
constexpr double kSeatRadiusY = 255.0;
constexpr int kPlateW = 200;
constexpr int kPlateH = 62;
constexpr int kBigW = 64;
constexpr int kBigH = 90;
constexpr int kSmallW = 44;
constexpr int kSmallH = 62;
constexpr int kChipAnimMs = 650;
constexpr int kLeaveConfirmMs = 3000;
constexpr int kMaxTypedDigits = 9;

const DWORD kColText = 0xFFE6EDF3;
const DWORD kColMuted = 0xFF6B7785;
const DWORD kColSoft = 0xFFB8C5D6;
const DWORD kColGold = 0xFFFFD166;
const DWORD kColCyan = 0xFF48CAE4;
const DWORD kColGreen = 0xFF7CFC9B;
const DWORD kColRed = 0xFFFF6B6B;
const DWORD kColHint = 0xFF8FB8DE;
const DWORD kColPurple = 0xFFD9B3FF;

enum class Wait { None, Action, Continue, Result };

struct Shared {
    std::mutex mutex;
    std::condition_variable cv;

    TableView view;
    bool hasView = false;

    Wait wait = Wait::None;
    bool answered = false;
    Action answer;
    ActionPrompt prompt;
    int promptSerial = 0;
    std::string message;
    bool resultWon = false;
    int resultHands = 0;

    bool animActive = false;
    int animSeat = 0;
    int animAmount = 0;
    std::chrono::steady_clock::time_point animStart;
};

Shared g_shared;
std::atomic<bool> g_quit{false};
std::atomic<double> g_timeScale{1.0};

struct Textures {
    int table = -1;
    int titleBg = -1;
    int titleArt = -1;
    int howtoBg = -1;
    int plate[5] = {-1, -1, -1, -1, -1};
    int panelLog = -1;
    int panelAction = -1;
    int chip = -1;
    int dealer = -1;
    int bannerWin = -1;
    int bannerLose = -1;
    int bigFace[52];
    int smallFace[52];
    int bigBack = -1;
    int smallBack = -1;
    int bigEmpty = -1;
    int smallFlip = -1;
};

enum PlateKind { PlateNormal = 0, PlateYou, PlateActive, PlateWinner, PlateDim };

Textures g_tex;
bool g_assetsLoaded = false;
int g_fontHead = -1;
int g_fontMenu = -1;
int g_fontBody = -1;
int g_fontSmall = -1;
int g_fontSeat = -1;

int g_selTarget = 0;
std::string g_typed;
int g_lastSerial = -1;
std::string g_hint;
std::chrono::steady_clock::time_point g_leaveArmedUntil;

int clampInt(int value, int low, int high) {
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

bool keyDown(const KEYCODE* keys, int key) {
    return keys != nullptr && keys[key] == EINPUT_DOWN;
}

int loadTexture(const char* path, int& failures) {
    const int id = g2_TextureLoad(path);
    if (id < 0) {
        std::fprintf(stderr, "texture load failed: %s\n", path);
        ++failures;
    }
    return id;
}

void drawTex(int texture, int x, int y) {
    if (texture < 0) {
        return;
    }
    VEC2 pos(static_cast<float>(x), static_cast<float>(y));
    g2_Draw2D(texture, {}, &pos);
}

void drawText(int font, int x, int y, DWORD color, const std::string& text, int width = 520) {
    if (font < 0 || text.empty()) {
        return;
    }
    g2_FontDrawText(font, {x, y, x + width, y + 40}, color, "%s", text.c_str());
}

int cardIndex(const Card& card) {
    return clampInt(card.rank - 2, 0, 12) * 4 + static_cast<int>(card.suit);
}

std::string timeText(int seconds) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%d:%02d", seconds / 60, seconds % 60);
    return buffer;
}

void seatCenter(int index, int& x, int& y) {
    const double angle = (90.0 + 40.0 * index) * kPi / 180.0;
    x = kTableCenterX + static_cast<int>(std::lround(kSeatRadiusX * std::cos(angle)));
    y = kTableCenterY + static_cast<int>(std::lround(kSeatRadiusY * std::sin(angle)));
}

void betMarker(int index, int seatX, int seatY, int& x, int& y) {
    if (index == 0) {
        x = 770;
        y = 440;
        return;
    }
    x = seatX + static_cast<int>(std::lround((kTableCenterX - seatX) * 0.34));
    y = seatY + static_cast<int>(std::lround((kTableCenterY - seatY) * 0.34));
}

struct Snapshot {
    TableView view;
    bool hasView = false;
    Wait wait = Wait::None;
    ActionPrompt prompt;
    int serial = 0;
    std::string message;
    bool resultWon = false;
    int resultHands = 0;
    bool animActive = false;
    int animSeat = 0;
    int animAmount = 0;
    double animT = 0.0;
};

Snapshot takeSnapshot() {
    Snapshot snap;
    std::lock_guard<std::mutex> lock(g_shared.mutex);
    snap.view = g_shared.view;
    snap.hasView = g_shared.hasView;
    snap.wait = g_shared.wait;
    snap.prompt = g_shared.prompt;
    snap.serial = g_shared.promptSerial;
    snap.message = g_shared.message;
    snap.resultWon = g_shared.resultWon;
    snap.resultHands = g_shared.resultHands;
    if (g_shared.animActive) {
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - g_shared.animStart);
        snap.animActive = true;
        snap.animSeat = g_shared.animSeat;
        snap.animAmount = g_shared.animAmount;
        snap.animT = clampInt(static_cast<int>(elapsed.count()), 0, kChipAnimMs) /
                     static_cast<double>(kChipAnimMs);
    }
    return snap;
}

void submitAnswer(const Action& action) {
    std::lock_guard<std::mutex> lock(g_shared.mutex);
    if (g_shared.wait == Wait::None || g_shared.answered) {
        return;
    }
    g_shared.answer = action;
    g_shared.answered = true;
    g_shared.cv.notify_all();
}

void drawCardFace(const Card& card, bool big, int x, int y) {
    const int index = cardIndex(card);
    drawTex(big ? g_tex.bigFace[index] : g_tex.smallFace[index], x, y);
}

void drawBoard(const Snapshot& snap) {
    const int count = static_cast<int>(snap.view.board.size());
    const int left = kTableCenterX - (5 * kBigW + 4 * 12) / 2;
    for (int i = 0; i < 5; ++i) {
        const int x = left + i * (kBigW + 12);
        const int y = 255;
        if (i >= count) {
            drawTex(g_tex.bigEmpty, x, y);
        } else if (i >= count - snap.view.hiddenBoardCards) {
            drawTex(g_tex.bigBack, x, y);
        } else {
            drawCardFace(snap.view.board[i], true, x, y);
        }
    }
}

void drawSeat(int index, const SeatView& seat) {
    int cx = 0;
    int cy = 0;
    seatCenter(index, cx, cy);
    const int px = cx - kPlateW / 2;
    const int py = cy - kPlateH / 2;
    const bool out = seat.eliminated || seat.folded;

    if (!out && seat.cardsOut) {
        if (seat.isUser) {
            const int y = py - kBigH - 6;
            drawCardFace(seat.hole[0], true, cx - kBigW - 4, y);
            drawCardFace(seat.hole[1], true, cx + 4, y);
        } else {
            const int y = py - 38;
            const int xs[2] = {cx - kSmallW - 2, cx + 2};
            for (int i = 0; i < 2; ++i) {
                if (seat.faceState == 2) {
                    drawCardFace(seat.hole[i], false, xs[i], y);
                } else if (seat.faceState == 1) {
                    drawTex(g_tex.smallFlip, xs[i], y);
                } else {
                    drawTex(g_tex.smallBack, xs[i], y);
                }
            }
        }
    }

    int kind = PlateNormal;
    if (out) {
        kind = PlateDim;
    } else if (seat.winner) {
        kind = PlateWinner;
    } else if (seat.isActing) {
        kind = PlateActive;
    } else if (seat.isUser) {
        kind = PlateYou;
    }
    drawTex(g_tex.plate[kind], px, py);

    DWORD nameColor = kColText;
    if (out) {
        nameColor = kColMuted;
    } else if (seat.winner) {
        nameColor = kColGreen;
    } else if (seat.isActing) {
        nameColor = kColGold;
    } else if (seat.isUser) {
        nameColor = kColCyan;
    }
    drawText(g_fontSeat, px + 12, py + 7, nameColor, seat.name, 90);
    drawText(g_fontSeat, px + 12, py + 33, out ? kColMuted : kColText, ui::formatChips(seat.stack), 110);

    if (seat.eliminated) {
        drawText(g_fontSmall, px + 120, py + 9, kColMuted, "OUT", 70);
    } else if (seat.folded) {
        drawText(g_fontSmall, px + 120, py + 9, kColMuted, "FOLD", 70);
    } else if (seat.allIn) {
        drawText(g_fontSmall, px + 112, py + 9, kColRed, "ALL-IN", 80);
    }
    if (!out && !seat.handName.empty()) {
        drawText(g_fontSmall, px + 6, py + kPlateH + 3, seat.winner ? kColGreen : kColGold, seat.handName, 190);
    }

    if (seat.isDealer) {
        drawTex(g_tex.dealer, px - 12, py - 10);
    }

    if (seat.bet > 0 && !seat.eliminated) {
        int bx = 0;
        int by = 0;
        betMarker(index, cx, cy, bx, by);
        drawTex(g_tex.chip, bx - 12, by - 12);
        drawText(g_fontSmall, bx + 18, by - 9, kColGold, ui::formatChips(seat.bet), 110);
    }
}

void drawChipAnimation(const Snapshot& snap) {
    if (!snap.animActive) {
        return;
    }
    int sx = 0;
    int sy = 0;
    seatCenter(snap.animSeat, sx, sy);
    const double t = snap.animT;
    const double eased = t * t * (3.0 - 2.0 * t);
    const int startX = kTableCenterX;
    const int startY = 235;
    for (int i = 0; i < 4; ++i) {
        const double lag = clampInt(static_cast<int>((eased - i * 0.07) * 1000.0), 0, 1000) / 1000.0;
        const int x = startX + static_cast<int>((sx - startX) * lag);
        const int y = startY + static_cast<int>((sy - startY) * lag);
        drawTex(g_tex.chip, x - 12, y - 12 - i * 3);
    }
    drawText(g_fontBody, kTableCenterX + 40, 190, kColGreen, "+" + ui::formatChips(snap.animAmount), 200);
}

void drawActionPanel(const Snapshot& snap) {
    const int px = 770;
    const int py = 598;
    drawTex(g_tex.panelAction, px, py);
    const int x = px + 14;
    int y = py + 7;
    const int step = 20;

    if (snap.wait == Wait::Action) {
        const ActionPrompt& p = snap.prompt;
        drawText(g_fontSmall, x, y, kColGold, "YOUR TURN - " + p.street + "     POT " + ui::formatChips(p.pot), 470);
        y += step;

        if (!g_hint.empty()) {
            drawText(g_fontSmall, x, y, kColRed, g_hint, 470);
        } else if (p.toCall > 0) {
            char buffer[96];
            std::snprintf(buffer, sizeof(buffer), "To call %s  (win rate needed: %.1f%%)",
                          ui::formatChips(p.callCost).c_str(), p.breakEven);
            drawText(g_fontSmall, x, y, kColSoft, buffer, 470);
        } else {
            drawText(g_fontSmall, x, y, kColSoft, "Nothing to call - you may check", 470);
        }
        y += step;

        std::string line = "[F] Fold   [C] " + (p.toCall > 0 ? "Call " + ui::formatChips(p.callCost) : std::string("Check"));
        if (p.canRaise) {
            const int shown = g_typed.empty() ? g_selTarget : std::atoi(g_typed.c_str());
            line += "   [Enter] " + std::string(p.opening ? "Bet " : "Raise to ") +
                    ui::formatChips(clampInt(shown, p.minTo, p.maxTo));
        }
        drawText(g_fontSmall, x, y, kColText, line, 470);
        y += step;

        if (p.canRaise) {
            drawText(g_fontSmall, x, y, kColHint, "Up/Down +-1BB  Left/Right +-10BB  0-9 type amount", 470);
            y += step;
            drawText(g_fontSmall, x, y, kColHint, "[M] Min   [P] Pot   [A] All-in   [Back] Erase", 470);
        }
        return;
    }

    if (snap.wait == Wait::Continue) {
        drawText(g_fontSmall, x, y, kColGold, snap.message, 470);
        y += step;
        drawText(g_fontSmall, x, y, kColText, "Press Enter for the next hand", 470);
    } else if (snap.wait == Wait::Result) {
        drawText(g_fontSmall, x, y, kColGold, "Tournament finished", 470);
        y += step;
        drawText(g_fontSmall, x, y, kColText, "Press Enter to return to the menu", 470);
    } else {
        drawText(g_fontSmall, x, y, kColSoft, "Waiting for the other players...", 470);
    }
    drawText(g_fontSmall, x, py + 112 - 28, kColHint, "Esc twice: leave the table", 470);
}

void drawLogPanel(const Snapshot& snap) {
    const int px = 16;
    const int py = 598;
    drawTex(g_tex.panelLog, px, py);
    const std::vector<std::string>& log = snap.view.log;
    const int total = static_cast<int>(log.size());
    const int shown = (total < 5) ? total : 5;
    for (int i = 0; i < shown; ++i) {
        const int line = total - shown + i;
        const bool latest = (i == shown - 1);
        drawText(g_fontSmall, px + 12, py + 8 + i * 20, latest ? kColText : kColSoft, log[line], 316);
    }
}

}  
namespace ui {

std::string formatChips(int amount) {
    std::string digits = std::to_string(amount < 0 ? -amount : amount);
    std::string result;
    int count = 0;
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        result.insert(result.begin(), digits[i]);
        if (++count % 3 == 0 && i > 0) {
            result.insert(result.begin(), ',');
        }
    }
    return amount < 0 ? "-" + result : result;
}

bool loadAssets() {
    int failures = 0;
    g_fontHead = g2_FontCreate("Arial", 30, 0);
    g_fontMenu = g2_FontCreate("Arial", 27, 0);
    g_fontBody = g2_FontCreate("Consolas", 20, 0);
    g_fontSmall = g2_FontCreate("Consolas", 16, 0);
    g_fontSeat = g2_FontCreate("Arial", 20, 0);
    if (g_fontHead < 0 || g_fontMenu < 0 || g_fontBody < 0 || g_fontSmall < 0 || g_fontSeat < 0) {
        std::fprintf(stderr, "glc2d font creation failed.\n");
        ++failures;
    }

    g_tex.table = loadTexture("Texture/table.png", failures);
    g_tex.titleBg = loadTexture("Texture/title_bg.png", failures);
    g_tex.titleArt = loadTexture("Texture/title_art.png", failures);
    g_tex.howtoBg = loadTexture("Texture/howto_bg.png", failures);
    g_tex.plate[PlateNormal] = loadTexture("Texture/plate_normal.png", failures);
    g_tex.plate[PlateYou] = loadTexture("Texture/plate_you.png", failures);
    g_tex.plate[PlateActive] = loadTexture("Texture/plate_active.png", failures);
    g_tex.plate[PlateWinner] = loadTexture("Texture/plate_winner.png", failures);
    g_tex.plate[PlateDim] = loadTexture("Texture/plate_dim.png", failures);
    g_tex.panelLog = loadTexture("Texture/panel_log.png", failures);
    g_tex.panelAction = loadTexture("Texture/panel_action.png", failures);
    g_tex.chip = loadTexture("Texture/chip.png", failures);
    g_tex.dealer = loadTexture("Texture/dealer.png", failures);
    g_tex.bannerWin = loadTexture("Texture/banner_win.png", failures);
    g_tex.bannerLose = loadTexture("Texture/banner_lose.png", failures);
    g_tex.bigBack = loadTexture("Texture/cards/L_back.png", failures);
    g_tex.smallBack = loadTexture("Texture/cards/S_back.png", failures);
    g_tex.bigEmpty = loadTexture("Texture/cards/L_empty.png", failures);
    g_tex.smallFlip = loadTexture("Texture/cards/S_flip.png", failures);

    const char* ranks = "23456789TJQKA";
    const char* suits = "shdc"; 
    for (int r = 0; r < 13; ++r) {
        for (int s = 0; s < 4; ++s) {
            char path[96];
            std::snprintf(path, sizeof(path), "Texture/cards/L_%c%c.png", ranks[r], suits[s]);
            g_tex.bigFace[r * 4 + s] = loadTexture(path, failures);
            std::snprintf(path, sizeof(path), "Texture/cards/S_%c%c.png", ranks[r], suits[s]);
            g_tex.smallFace[r * 4 + s] = loadTexture(path, failures);
        }
    }

    g_assetsLoaded = true;
    return failures == 0;
}

void releaseAssets() {
    if (!g_assetsLoaded) {
        return;
    }
    auto release = [](int& id) {
        if (id >= 0) {
            g2_TextureRelease(id);
            id = -1;
        }
    };
    release(g_tex.table);
    release(g_tex.titleBg);
    release(g_tex.titleArt);
    release(g_tex.howtoBg);
    for (int& id : g_tex.plate) {
        release(id);
    }
    release(g_tex.panelLog);
    release(g_tex.panelAction);
    release(g_tex.chip);
    release(g_tex.dealer);
    release(g_tex.bannerWin);
    release(g_tex.bannerLose);
    release(g_tex.bigBack);
    release(g_tex.smallBack);
    release(g_tex.bigEmpty);
    release(g_tex.smallFlip);
    for (int i = 0; i < 52; ++i) {
        release(g_tex.bigFace[i]);
        release(g_tex.smallFace[i]);
    }
    g_assetsLoaded = false;
}

void resetSession() {
    std::lock_guard<std::mutex> lock(g_shared.mutex);
    g_quit = false;
    g_shared.view = TableView();
    g_shared.hasView = false;
    g_shared.wait = Wait::None;
    g_shared.answered = false;
    g_shared.animActive = false;
    g_shared.message.clear();
    g_lastSerial = -1;
    g_typed.clear();
    g_hint.clear();
    g_leaveArmedUntil = std::chrono::steady_clock::time_point();
}

void requestQuit() {
    g_quit = true;
    std::lock_guard<std::mutex> lock(g_shared.mutex);
    g_shared.cv.notify_all();
}

bool updateTable() {
    const KEYCODE* keys = g2_GetKeyboard();
    const auto now = std::chrono::steady_clock::now();

    bool leave = false;
    if (keyDown(keys, VK_ESCAPE)) {
        if (now < g_leaveArmedUntil) {
            leave = true;
            g_leaveArmedUntil = std::chrono::steady_clock::time_point();
        } else {
            g_leaveArmedUntil = now + std::chrono::milliseconds(kLeaveConfirmMs);
        }
    }

    Wait wait;
    ActionPrompt prompt;
    int serial;
    {
        std::lock_guard<std::mutex> lock(g_shared.mutex);
        wait = g_shared.wait;
        prompt = g_shared.prompt;
        serial = g_shared.promptSerial;
    }

    if (wait == Wait::Continue || wait == Wait::Result) {
        if (keyDown(keys, VK_RETURN)) {
            submitAnswer(Action());
        }
        return leave;
    }
    if (wait != Wait::Action) {
        return leave;
    }

    if (serial != g_lastSerial) {
        g_lastSerial = serial;
        g_selTarget = prompt.minTo;
        g_typed.clear();
        g_hint.clear();
    }

    const int bigBlind = prompt.bigBlind > 0 ? prompt.bigBlind : 100;
    auto commitTyped = [&]() {
        if (!g_typed.empty()) {
            g_selTarget = std::atoi(g_typed.c_str());
            g_typed.clear();
        }
    };
    auto adjust = [&](int delta) {
        commitTyped();
        g_selTarget = clampInt(g_selTarget + delta, prompt.minTo, prompt.maxTo);
        g_hint.clear();
    };

    if (keyDown(keys, 'F')) {
        submitAnswer({ActionType::Fold, 0});
        return leave;
    }
    if (keyDown(keys, 'C')) {
        submitAnswer({prompt.toCall > 0 ? ActionType::Call : ActionType::Check, 0});
        return leave;
    }

    if (!prompt.canRaise) {
        return leave;
    }

    if (keyDown(keys, VK_UP)) {
        adjust(bigBlind);
    }
    if (keyDown(keys, VK_DOWN)) {
        adjust(-bigBlind);
    }
    if (keyDown(keys, VK_RIGHT)) {
        adjust(bigBlind * 10);
    }
    if (keyDown(keys, VK_LEFT)) {
        adjust(-bigBlind * 10);
    }
    if (keyDown(keys, 'M')) {
        g_typed.clear();
        g_selTarget = prompt.minTo;
        g_hint.clear();
    }
    if (keyDown(keys, 'P')) {
        g_typed.clear();
        g_selTarget = prompt.potTo;
        g_hint.clear();
    }
    if (keyDown(keys, 'A')) {
        g_typed.clear();
        g_selTarget = prompt.maxTo;
        g_hint.clear();
    }
    for (int digit = 0; digit <= 9; ++digit) {
        if (keyDown(keys, '0' + digit) || keyDown(keys, VK_NUMPAD0 + digit)) {
            if (static_cast<int>(g_typed.size()) < kMaxTypedDigits) {
                g_typed += static_cast<char>('0' + digit);
                g_hint.clear();
            }
        }
    }
    if (keyDown(keys, VK_BACK) && !g_typed.empty()) {
        g_typed.pop_back();
    }

    if (keyDown(keys, VK_RETURN) || keyDown(keys, 'R')) {
        const int wanted = g_typed.empty() ? g_selTarget : std::atoi(g_typed.c_str());
        if (wanted < prompt.minTo && wanted < prompt.maxTo) {
            g_hint = "Minimum is " + formatChips(prompt.minTo);
            g_typed.clear();
            g_selTarget = prompt.minTo;
        } else {
            const int target = clampInt(wanted, prompt.minTo, prompt.maxTo);
            submitAnswer({ActionType::Raise, target});
        }
    }
    return leave;
}

void drawTable() {
    const Snapshot snap = takeSnapshot();
    drawTex(g_tex.table, 0, 0);
    if (!snap.hasView) {
        drawText(g_fontMenu, 520, 320, kColSoft, "Shuffling...", 300);
        return;
    }

    const TableView& view = snap.view;
    drawText(g_fontBody, 24, 10, kColGold,
             "HAND #" + std::to_string(view.handNo) + "   LEVEL " + std::to_string(view.level) + "   BLINDS " +
                 formatChips(view.smallBlind) + "/" + formatChips(view.bigBlind) + "   NEXT " +
                 timeText(view.secondsToNextLevel),
             600);

    drawTex(g_tex.chip, 556, 214);
    drawText(g_fontBody, 590, 212, kColGold, "POT " + formatChips(view.pot), 260);
    drawText(g_fontSmall, 590, 236, kColSoft, view.streetName, 200);

    drawBoard(snap);
    for (size_t i = 0; i < view.seats.size(); ++i) {
        drawSeat(static_cast<int>(i), view.seats[i]);
    }
    drawChipAnimation(snap);
    drawLogPanel(snap);
    drawActionPanel(snap);

    if (snap.wait == Wait::Result) {
        drawTex(snap.resultWon ? g_tex.bannerWin : g_tex.bannerLose, 380, 80);
        drawText(g_fontBody, 548, 80 + 130, kColText, "Hands played: " + std::to_string(snap.resultHands), 300);
    }

    if (std::chrono::steady_clock::now() < g_leaveArmedUntil) {
        drawTex(g_tex.panelAction, 393, 140);
        drawText(g_fontBody, 430, 168, kColGold, "Leave the table?", 400);
        drawText(g_fontSmall, 430, 200, kColText, "Press Esc again within 3 seconds to confirm.", 440);
    }
}

void drawTitleScreen(int selectedMenu) {
    drawTex(g_tex.titleBg, 0, 0);
    drawTex(g_tex.titleArt, 460, 205);

    const char* items[3] = {"GAME START", "HOW TO PLAY", "EXIT"};
    for (int i = 0; i < 3; ++i) {
        const int top = 478 + i * 54;
        const bool selected = (i == selectedMenu);
        drawText(g_fontMenu, selected ? 520 : 546, top, selected ? kColGold : kColText,
                 std::string(selected ? "> " : "") + items[i], 400);
    }
    drawText(g_fontSmall, 440, 662, kColHint, "W, S or Arrow Keys: Move     Enter: Select     Esc: Exit", 700);
}

void drawHowToScreen() {
    drawTex(g_tex.howtoBg, 0, 0);
    const char* lines[] = {
        "9 players: you against 8 bots. Everyone starts with 150 big blinds.",
        "Blinds start at 100/200 and rise every 7 minutes. Take every chip to win.",
        "Bots play three styles: TAG (tight-aggressive), TL (tight-loose) and FISH (loose).",
        "",
        "On your turn:",
        "   F = fold        C = call / check        Enter or R = bet / raise",
        "   Up / Down = +-1 big blind        Left / Right = +-10 big blinds",
        "   M = min raise   P = pot-size raise   A = all-in   0-9 = type an amount",
        "",
        "The panel shows the win rate you need to make a call profitable.",
        "Esc twice during a game leaves the table.",
    };
    int y = 150;
    for (const char* line : lines) {
        drawText(g_fontBody, 130, y, kColText, line, 1040);
        y += 34;
    }
    drawText(g_fontSmall, 470, 612, kColHint, "Enter or Esc: Return to Main Menu", 600);
}
///////////////////////////////////
void draw(const TableView& view) {
    std::lock_guard<std::mutex> lock(g_shared.mutex);
    g_shared.view = view;
    g_shared.hasView = true;
}

void setTimeScale(double scale) {
    g_timeScale = scale < 0.0 ? 0.0 : scale;
}

void sleepMs(int milliseconds) {
    int remaining = static_cast<int>(milliseconds * g_timeScale.load());
    while (remaining > 0) {
        if (g_quit) {
            throw QuitRequested{};
        }
        const int slice = remaining < 10 ? remaining : 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(slice));
        remaining -= slice;
    }
    if (g_quit) {
        throw QuitRequested{};
    }
}

void animateChips(int seat, int amount) {
    {
        std::lock_guard<std::mutex> lock(g_shared.mutex);
        g_shared.animActive = true;
        g_shared.animSeat = seat;
        g_shared.animAmount = amount;
        g_shared.animStart = std::chrono::steady_clock::now();
    }
    try {
        sleepMs(kChipAnimMs);
    } catch (...) {
        std::lock_guard<std::mutex> lock(g_shared.mutex);
        g_shared.animActive = false;
        throw;
    }
    std::lock_guard<std::mutex> lock(g_shared.mutex);
    g_shared.animActive = false;
}

namespace {

////////////////////////////
void blockUntilAnswered(std::unique_lock<std::mutex>& lock) {
    g_shared.cv.wait(lock, [] { return g_shared.answered || g_quit.load(); });
    g_shared.wait = Wait::None;
    if (g_quit) {
        throw QuitRequested{};
    }
}

}  

Action askAction(const ActionPrompt& prompt) {
    std::unique_lock<std::mutex> lock(g_shared.mutex);
    if (g_quit) {
        throw QuitRequested{};
    }
    g_shared.prompt = prompt;
    ++g_shared.promptSerial;
    g_shared.answered = false;
    g_shared.wait = Wait::Action;
    blockUntilAnswered(lock);
    return g_shared.answer;
}

void waitContinue(const std::string& message) {
    std::unique_lock<std::mutex> lock(g_shared.mutex);
    if (g_quit) {
        throw QuitRequested{};
    }
    g_shared.message = message;
    g_shared.answered = false;
    g_shared.wait = Wait::Continue;
    blockUntilAnswered(lock);
}

void showResult(bool won, int handsPlayed) {
    std::unique_lock<std::mutex> lock(g_shared.mutex);
    if (g_quit) {
        throw QuitRequested{};
    }
    g_shared.resultWon = won;
    g_shared.resultHands = handsPlayed;
    g_shared.answered = false;
    g_shared.wait = Wait::Result;
    blockUntilAnswered(lock);
}

}  
