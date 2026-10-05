#include "Game.h"

#include "Ui.h"

#include <algorithm>
#include <stdexcept>

namespace {

constexpr int kSeats = 9;
constexpr int kStartStack = 150 * 200;
constexpr int kLevelSeconds = 7 * 60;
constexpr int kHeadlessHandsPerLevel = 25;
constexpr size_t kLogLines = 8;

struct Blinds {
    int small;
    int big;
};

const Blinds kSchedule[] = {
    {100, 200},   {150, 300},   {200, 400},   {300, 600},
    {400, 800},   {600, 1200},  {800, 1600},  {1000, 2000},
    {1500, 3000}, {2000, 4000}, {3000, 6000}, {4000, 8000},
};
constexpr int kLevels = static_cast<int>(sizeof(kSchedule) / sizeof(kSchedule[0]));

const char* streetLabel(Street street) {
    switch (street) {
    case Street::Preflop: return "PREFLOP";
    case Street::Flop: return "FLOP";
    case Street::Turn: return "TURN";
    default: return "RIVER";
    }
}

}

Game::Game(GameConfig config) : config_(config) {
    std::vector<Style> styles = {
        Style::TightAggressive, Style::TightAggressive, Style::TightAggressive,
        Style::TightLoose,      Style::TightLoose,      Style::TightLoose,
        Style::Fish,            Style::Fish};
    std::shuffle(styles.begin(), styles.end(), rng());

    players_.resize(kSeats);
    for (int i = 0; i < kSeats; ++i) {
        Player& player = players_[i];
        player.id = i;
        player.isUser = (i == 0 && !config_.headless);
        player.name = (i == 0) ? "YOU" : "Bot" + std::to_string(i);
        player.style = (i == 0) ? Style::TightAggressive : styles[i - 1];
        player.stack = kStartStack;
    }
    levelEnd_ = std::chrono::steady_clock::now() + std::chrono::seconds(kLevelSeconds);
}

int Game::smallBlind() const { return kSchedule[level_].small; }
int Game::bigBlind() const { return kSchedule[level_].big; }

int Game::potTotal() const {
    int total = 0;
    for (const Player& player : players_) {
        total += player.contrib;
    }
    return total;
}

bool Game::canAct(const Player& player) const {
    return player.dealt && !player.folded && !player.allIn;
}

int Game::contenders() const {
    int count = 0;
    for (const Player& player : players_) {
        if (player.dealt && !player.folded) {
            ++count;
        }
    }
    return count;
}

int Game::canActCount() const {
    int count = 0;
    for (const Player& player : players_) {
        if (canAct(player)) {
            ++count;
        }
    }
    return count;
}

int Game::aliveCount() const {
    int count = 0;
    for (const Player& player : players_) {
        if (player.stack > 0) {
            ++count;
        }
    }
    return count;
}

int Game::nextAlive(int from) const {
    for (int step = 1; step <= kSeats; ++step) {
        const int index = (from + step) % kSeats;
        if (players_[index].stack > 0) {
            return index;
        }
    }
    return from;
}

int Game::countCallers(const Player& player) const {
    int count = 0;
    for (const Player& other : players_) {
        if (other.id != player.id && other.dealt && !other.folded && other.streetContrib >= bigBlind()) {
            ++count;
        }
    }
    return count;
}

void Game::addLog(const std::string& text) {
    log_.push_back(text);
    while (log_.size() > kLogLines) {
        log_.pop_front();
    }
}

void Game::pause(int milliseconds) {
    if (!config_.headless) {
        ui::sleepMs(milliseconds);
    }
}

void Game::render() {
    if (config_.headless) {
        return;
    }

    TableView view;
    view.handNo = handNo_;
    view.level = level_ + 1;
    view.smallBlind = smallBlind();
    view.bigBlind = bigBlind();
    const auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
        levelEnd_ - std::chrono::steady_clock::now());
    view.secondsToNextLevel = static_cast<int>(std::max<long long>(0, remaining.count()));
    view.pot = potTotal();
    view.streetName = streetLabel(street_);
    view.board = board_;
    view.hiddenBoardCards = hiddenBoard_;

    for (const Player& player : players_) {
        SeatView seat;
        seat.name = player.name;
        seat.stack = player.stack;
        seat.bet = player.streetContrib;
        seat.isDealer = player.id == dealerIdx_;
        seat.isActing = player.id == actingIdx_;
        seat.isUser = player.isUser;
        seat.eliminated = player.stack <= 0 && !player.dealt;
        seat.folded = player.dealt && player.folded;
        seat.allIn = player.allIn && !player.folded;
        seat.winner = player.winner;
        seat.cardsOut = player.cardsOut;
        seat.faceState = player.faceState;
        seat.hole[0] = player.hole[0];
        seat.hole[1] = player.hole[1];
        seat.handName = player.handName;
        view.seats.push_back(seat);
    }
    view.log.assign(log_.begin(), log_.end());
    ui::draw(view);
}

bool Game::waitForNextHand() {
    ui::waitContinue("Hand finished.");
    return true;
}

void Game::showResult(bool won) {
    ui::showResult(won, handNo_);
}

void Game::run() {
    if (!config_.headless) {
        levelEnd_ = std::chrono::steady_clock::now() + std::chrono::seconds(kLevelSeconds);
    }

    while (aliveCount() >= 2 && handNo_ < config_.maxHands) {
        playHand();
        if (config_.headless) {
            continue;
        }
        if (players_[0].stack <= 0) {
            showResult(false);
            return;
        }
        if (aliveCount() == 1) {
            showResult(true);
            return;
        }
        if (!waitForNextHand()) {
            return;
        }
    }
}

void Game::updateLevel() {
    if (config_.headless) {
        level_ = std::min(handNo_ / kHeadlessHandsPerLevel, kLevels - 1);
        return;
    }
    const auto now = std::chrono::steady_clock::now();
    while (now >= levelEnd_) {
        levelEnd_ += std::chrono::seconds(kLevelSeconds);
        if (level_ < kLevels - 1) {
            ++level_;
            addLog("Blinds up: " + ui::formatChips(smallBlind()) + "/" + ui::formatChips(bigBlind()));
        }
    }
}

void Game::putChips(Player& player, int amount) {
    amount = std::min(amount, player.stack);
    player.stack -= amount;
    player.contrib += amount;
    player.streetContrib += amount;
    if (player.stack == 0) {
        player.allIn = true;
    }
}

void Game::dealHoleCards() {
    for (Player& player : players_) {
        if (!player.dealt) {
            continue;
        }
        player.hole[0] = deck_.draw();
        player.hole[1] = deck_.draw();
        player.cardsOut = true;
        player.faceState = player.isUser ? 2 : 0;
        render();
        pause(70);
    }
}

void Game::playHand() {
    ++handNo_;
    updateLevel();

    deck_.reset();
    board_.clear();
    hiddenBoard_ = 0;
    street_ = Street::Preflop;
    actingIdx_ = -1;
    for (Player& player : players_) {
        player.dealt = player.stack > 0;
        player.folded = !player.dealt;
        player.allIn = false;
        player.contrib = 0;
        player.streetContrib = 0;
        player.acted = false;
        player.cardsOut = false;
        player.faceState = 0;
        player.winner = false;
        player.handName.clear();
    }

    dealerIdx_ = nextAlive(dealerIdx_);
    int smallSeat;
    int bigSeat;
    if (aliveCount() == 2) {
        smallSeat = dealerIdx_;
        bigSeat = nextAlive(smallSeat);
    } else {
        smallSeat = nextAlive(dealerIdx_);
        bigSeat = nextAlive(smallSeat);
    }

    putChips(players_[smallSeat], smallBlind());
    putChips(players_[bigSeat], bigBlind());
    curBet_ = bigBlind();
    minRaise_ = bigBlind();

    addLog("-- Hand #" + std::to_string(handNo_) + " | Dealer " + players_[dealerIdx_].name + " --");
    render();
    dealHoleCards();

    bool revealedEarly = false;
    bettingRound((bigSeat + 1) % kSeats);

    while (true) {
        if (contenders() <= 1) {
            awardUncontested();
            finishHand();
            return;
        }
        if (street_ == Street::River) {
            break;
        }
        if (canActCount() <= 1 && !revealedEarly) {
            revealContenders();
            revealedEarly = true;
        }
        if (revealedEarly) {
            pause(700);
        }
        advanceStreet();
        bettingRound((dealerIdx_ + 1) % kSeats);
    }

    showdown();
    finishHand();
}

void Game::advanceStreet() {
    for (Player& player : players_) {
        player.streetContrib = 0;
        player.acted = false;
    }
    curBet_ = 0;
    minRaise_ = bigBlind();

    if (street_ == Street::Preflop) {
        street_ = Street::Flop;
        dealBoard(3);
    } else if (street_ == Street::Flop) {
        street_ = Street::Turn;
        dealBoard(1);
    } else {
        street_ = Street::River;
        dealBoard(1);
    }

    std::string text = std::string(streetLabel(street_)) + ":";
    for (const Card& card : board_) {
        text += " " + cardText(card);
    }
    addLog(text);
    render();
}

void Game::dealBoard(int count) {
    for (int i = 0; i < count; ++i) {
        board_.push_back(deck_.draw());
    }
    hiddenBoard_ = count;
    actingIdx_ = -1;
    render();
    pause(220);
    for (int i = 0; i < count; ++i) {
        --hiddenBoard_;
        render();
        pause(260);
    }
}

bool Game::roundComplete() const {
    int actors = 0;
    bool pending = false;
    const Player* only = nullptr;
    for (const Player& player : players_) {
        if (!canAct(player)) {
            continue;
        }
        ++actors;
        only = &player;
        if (!player.acted || player.streetContrib != curBet_) {
            pending = true;
        }
    }
    if (actors == 0) {
        return true;
    }
    if (actors == 1 && only->streetContrib >= curBet_) {
        return true;
    }
    return !pending;
}

void Game::bettingRound(int firstSeat) {
    int seat = firstSeat;
    for (int guard = 0; guard < 100000; ++guard) {
        if (contenders() <= 1 || roundComplete()) {
            break;
        }
        Player& player = players_[seat];
        seat = (seat + 1) % kSeats;
        if (!canAct(player)) {
            continue;
        }

        actingIdx_ = player.id;
        render();
        const Action action = player.isUser ? askUser(player) : askBot(player);
        applyAction(player, action);
        player.acted = true;
        actingIdx_ = -1;
        render();
        if (!player.isUser) {
            pause(250);
        }
    }
    actingIdx_ = -1;
}

Action Game::askBot(Player& player) {
    pause(450 + static_cast<int>(rand01() * 450));

    BotContext context;
    context.street = street_;
    context.board = &board_;
    context.pot = potTotal();
    context.curBet = curBet_;
    context.minRaise = minRaise_;
    context.bigBlind = bigBlind();
    context.stack = player.stack;
    context.streetContrib = player.streetContrib;
    context.limpersAndCallers = countCallers(player);
    return decideBot(player.style, player.hole, context);
}

Action Game::askUser(Player& player) {
    const int toCall = std::max(0, curBet_ - player.streetContrib);
    const int callCost = std::min(toCall, player.stack);
    const int maxTo = player.stack + player.streetContrib;
    const int minTo = std::min(maxTo, curBet_ + minRaise_);
    const int pot = potTotal();

    ActionPrompt prompt;
    prompt.street = streetLabel(street_);
    prompt.pot = pot;
    prompt.toCall = toCall;
    prompt.callCost = callCost;
    prompt.minTo = minTo;
    prompt.maxTo = maxTo;
    prompt.potTo = std::min(maxTo, std::max(minTo, curBet_ + pot + toCall));
    prompt.bigBlind = bigBlind();
    prompt.canRaise = player.stack > toCall;
    prompt.opening = curBet_ == 0;
    prompt.breakEven = toCall > 0 ? 100.0 * callCost / static_cast<double>(pot + callCost) : -1.0;

    render();
    return ui::askAction(prompt);
}

void Game::applyAction(Player& player, Action action) {
    const int toCall = std::max(0, curBet_ - player.streetContrib);

    if (action.type == ActionType::Raise) {
        action.amount = std::min(action.amount, player.stack + player.streetContrib);
        if (action.amount <= curBet_) {
            action.type = toCall > 0 ? ActionType::Call : ActionType::Check;
        }
    }
    if (action.type == ActionType::Check && toCall > 0) {
        action.type = ActionType::Call;
    }
    if (action.type == ActionType::Call && toCall == 0) {
        action.type = ActionType::Check;
    }

    switch (action.type) {
    case ActionType::Fold:
        player.folded = true;
        addLog(player.name + " folds");
        break;
    case ActionType::Check:
        addLog(player.name + " checks");
        break;
    case ActionType::Call: {
        const int paid = std::min(toCall, player.stack);
        putChips(player, paid);
        addLog(player.name + " calls " + ui::formatChips(paid) + (player.allIn ? " (all-in)" : ""));
        break;
    }
    case ActionType::Raise: {
        const int before = curBet_;
        const int target = action.amount;
        putChips(player, target - player.streetContrib);
        const int size = target - before;
        if (size >= minRaise_) {
            minRaise_ = size;
        }
        curBet_ = target;
        for (Player& other : players_) {
            if (other.id != player.id) {
                other.acted = false;
            }
        }
        addLog(player.name + (before == 0 ? " bets " : " raises to ") + ui::formatChips(target) +
               (player.allIn ? " (all-in)" : ""));
        break;
    }
    }
}

void Game::flipCards(Player& player) {
    player.faceState = 1;
    render();
    pause(140);
    player.faceState = 2;
    render();
    pause(260);
}

void Game::revealContenders() {
    actingIdx_ = -1;
    addLog("All-in: hands are revealed");
    for (Player& player : players_) {
        if (player.dealt && !player.folded && !player.isUser && player.faceState != 2) {
            flipCards(player);
        }
    }
}

void Game::showdown() {
    actingIdx_ = -1;
    std::vector<HandScore> scores(kSeats, 0);
    for (Player& player : players_) {
        if (!player.dealt || player.folded) {
            continue;
        }
        std::vector<Card> cards(board_);
        cards.push_back(player.hole[0]);
        cards.push_back(player.hole[1]);
        scores[player.id] = evaluateBest(cards);
        player.handName = categoryName(handCategory(scores[player.id]));
    }

    addLog("-- Showdown --");
    for (Player& player : players_) {
        if (player.dealt && !player.folded && !player.isUser && player.faceState != 2) {
            flipCards(player);
        }
    }
    render();
    pause(900);
    distributePots(scores);
}

void Game::awardUncontested() {
    int winnerId = -1;
    for (const Player& player : players_) {
        if (player.dealt && !player.folded) {
            winnerId = player.id;
        }
    }
    if (winnerId < 0) {
        return;
    }

    std::vector<int> payouts(kSeats, 0);
    payouts[winnerId] = potTotal();
    players_[winnerId].winner = true;
    addLog(players_[winnerId].name + " wins " + ui::formatChips(payouts[winnerId]) + " (all folded)");
    render();
    payOut(payouts);
}

void Game::distributePots(const std::vector<HandScore>& scores) {
    struct SidePot {
        int amount = 0;
        std::vector<int> eligible;
    };

    std::vector<int> levels;
    for (const Player& player : players_) {
        if (player.contrib > 0) {
            levels.push_back(player.contrib);
        }
    }
    std::sort(levels.begin(), levels.end());
    levels.erase(std::unique(levels.begin(), levels.end()), levels.end());

    std::vector<SidePot> pots;
    int previous = 0;
    for (int level : levels) {
        SidePot pot;
        for (const Player& player : players_) {
            pot.amount += std::max(0, std::min(player.contrib, level) - previous);
            if (player.dealt && !player.folded && player.contrib >= level) {
                pot.eligible.push_back(player.id);
            }
        }
        previous = level;
        if (!pots.empty() && (pot.eligible.empty() || pots.back().eligible == pot.eligible)) {
            pots.back().amount += pot.amount;
        } else {
            pots.push_back(pot);
        }
    }

    std::vector<int> payouts(kSeats, 0);
    for (const SidePot& pot : pots) {
        if (pot.eligible.empty()) {
            continue;
        }

        if (pot.eligible.size() == 1) {
            const int id = pot.eligible[0];
            payouts[id] += pot.amount;
            if (pots.size() > 1) {
                addLog(players_[id].name + " gets back uncalled " + ui::formatChips(pot.amount));
            }
            continue;
        }

        HandScore top = 0;
        for (int id : pot.eligible) {
            top = std::max(top, scores[id]);
        }
        std::vector<int> winners;
        for (int id : pot.eligible) {
            if (scores[id] == top) {
                winners.push_back(id);
            }
        }
        std::sort(winners.begin(), winners.end(), [&](int a, int b) {
            return (a - dealerIdx_ - 1 + kSeats) % kSeats < (b - dealerIdx_ - 1 + kSeats) % kSeats;
        });

        const int share = pot.amount / static_cast<int>(winners.size());
        const int remainder = pot.amount - share * static_cast<int>(winners.size());
        for (size_t i = 0; i < winners.size(); ++i) {
            payouts[winners[i]] += share + (i == 0 ? remainder : 0);
            players_[winners[i]].winner = true;
        }

        if (winners.size() == 1) {
            addLog(players_[winners[0]].name + " wins " + ui::formatChips(pot.amount) + " (" +
                   players_[winners[0]].handName + ")");
        } else {
            std::string names;
            for (int id : winners) {
                names += (names.empty() ? "" : ", ") + players_[id].name;
            }
            addLog(names + " split " + ui::formatChips(pot.amount));
        }
    }

    render();
    payOut(payouts);
}

void Game::payOut(const std::vector<int>& payouts) {
    pause(500);
    for (int i = 0; i < kSeats; ++i) {
        if (payouts[i] <= 0) {
            continue;
        }
        if (!config_.headless) {
            ui::animateChips(i, payouts[i]);
        }
        players_[i].stack += payouts[i];
    }
    for (Player& player : players_) {
        player.contrib = 0;
        player.streetContrib = 0;
    }
    render();
}

void Game::finishHand() {
    actingIdx_ = -1;
    for (Player& player : players_) {
        if (player.dealt && player.stack <= 0 && player.bustHand == 0) {
            player.bustHand = handNo_;
            addLog(player.name + " is out");
        }
    }
    render();

    if (config_.headless) {
        int total = 0;
        for (const Player& player : players_) {
            total += player.stack;
        }
        if (total != kStartStack * kSeats) {
            throw std::logic_error("chip total changed");
        }
    }
}
