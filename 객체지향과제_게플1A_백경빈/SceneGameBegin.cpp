#include "SceneGameBegin.h"
#include "KoreanText.h"
#include "glc2d.h"
#include <algorithm>
#include <string>

namespace
{
const char *const menuLabels[] = {"START", "SETTING", "EXIT"};
constexpr int TitleFontSize = 32;
constexpr int BodyFontSize = 24;
}

int SceneGameBegin::Init()
{
    const char *path = "resource/texture/Title.png";
    texture = g2_TextureLoad(path, 0);
    if (texture < 0)
    {
        MessageBoxW(g2_GetHwnd(),
                    L"표지 이미지를 불러올 수 없습니다. resource/texture/Title.png를 확인하세요.",
                    L"Dungeon Escape", MB_ICONERROR);
        return -1;
    }

    forestBackground = g2_TextureLoad("resource/texture/Forest.png", 0);
    ruinsBackground = g2_TextureLoad("resource/texture/Ruins.png", 0);
    caveBackground = g2_TextureLoad("resource/texture/Cave.png", 0);
    citadelBackground = g2_TextureLoad("resource/texture/Citadel.png", 0);
    playerSprite = g2_TextureLoad("resource/texture/Player.png", 0);
    forestEnemySprite = g2_TextureLoad("resource/texture/ForestEnemy.png", 0);
    ruinsEnemySprite = g2_TextureLoad("resource/texture/RuinsEnemy.png", 0);
    caveEnemySprite = g2_TextureLoad("resource/texture/CaveEnemy.png", 0);
    bossSprite = g2_TextureLoad("resource/texture/Boss.png", 0);
    potionSprite = g2_TextureLoad("resource/texture/Potion.png", 0);
    superPotionSprite = g2_TextureLoad("resource/texture/SuperPotion.png", 0);
    rewardIcons = g2_TextureLoad("resource/texture/RewardIcons.png", 0);
    pixel = g2_TextureLoad("resource/texture/Pixel.png", 0);

    const char *fontName = "Malgun Gothic";
    font = g2_FontCreate(fontName, TitleFontSize);
    smallFont = g2_FontCreate(fontName, BodyFontSize);

    HDC dc = GetDC(g2_GetHwnd());
    HFONT measuringFont = CreateFontA(TitleFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                      DEFAULT_PITCH | FF_DONTCARE, fontName);
    HGDIOBJ oldFont = SelectObject(dc, measuringFont);

    for (int i = 0; i < 3; ++i)
    {
        SIZE size{};
        std::string localLabel = ToLocalText(menuLabels[i]);
        GetTextExtentPoint32A(dc, localLabel.c_str(), static_cast<int>(localLabel.size()), &size);
        menuWidths[i] = size.cx;
    }

    SelectObject(dc, oldFont);
    DeleteObject(measuringFont);
    ReleaseDC(g2_GetHwnd(), dc);

    audioAvailable = audio.Init();
    if (audioAvailable)
    {
        audioAvailable = audio.SetVolume(volumePercent);
    }

    mainBgm = g2_SoundLoad("resource/sound/Main bgm.mp3");
    // 전투 음악은 선택 리소스다. 없으면 타이틀 음악을 유지한다.
    if (GetFileAttributesA("resource/sound/Battle bgm.mp3") != INVALID_FILE_ATTRIBUTES)
        battleBgm = g2_SoundLoad("resource/sound/Battle bgm.mp3");
    if (mainBgm >= 0)
    {
        PlayMusic(mainBgm);
    }
    else
    {
        MessageBoxW(g2_GetHwnd(), L"resource/sound/Main bgm.mp3를 불러올 수 없습니다.",
                    L"Dungeon Escape - 소리", MB_ICONWARNING);
    }

    return 0;
}
int SceneGameBegin::Update()
{
    const int keys[] = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN, VK_ESCAPE, 'A', 'B', 'Q'};

    bool pressed[256]{};

    for (int key : keys)
    {
        bool down = GetForegroundWindow() == g2_GetHwnd() && (GetAsyncKeyState(key) & 0x8000) != 0;
        pressed[key] = down && !previous[key];
        previous[key] = down;
    }
    if (pressed[VK_ESCAPE])
    {
        if (page == Page::Battle)
        {
            battle.Back();
        }
        else if (page != Page::Menu)
        {
            ReturnToTitle();
        }
        else
        {
            PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
        }
        return 0;
    }
    if (page == Page::Menu)
    {
        if (pressed[VK_UP])
        {
            if (selected == 0)
            {
                selected = 2;
            }
            else
            {
                selected--;
            }
        }
        if (pressed[VK_DOWN])
        {
            if (selected == 2)
            {
                selected = 0;
            }
            else
            {
                selected++;
            }
        }
        if (pressed[VK_RETURN])
        {
            if (selected == 0)
            {
                page = Page::Help;
                PlayMusic(battleBgm >= 0 ? battleBgm : mainBgm);
            }
            else if (selected == 1)
            {
                page = Page::Settings;
                settingSelected = 0;
            }
            else
            {
                PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
            }
        }
    }
    else if (page == Page::Help)
    {
        if (pressed[VK_RETURN])
            StartBattle();
    }
    else if (page == Page::Battle)
    {
        if (pressed['A'])
        {
            battle.QuickAttack();
        }
        else if (pressed['B'])
        {
            battle.QuickRun();
        }
        else if (pressed['Q'])
        {
            battle.QuickPotion();
        }
        if (pressed['A'] || pressed['B'] || pressed['Q'])
        {
            return 0;
        }
        if (pressed[VK_UP])
        {
            battle.MoveUp();
        }
        if (pressed[VK_DOWN])
        {
            battle.MoveDown();
        }
        if (pressed[VK_LEFT])
        {
            battle.MoveLeft();
        }
        if (pressed[VK_RIGHT])
        {
            battle.MoveRight();
        }
        if (pressed[VK_RETURN])
        {
            ForestBattle::Menu menu = battle.CurrentMenu();
            ForestBattle::Result beforeResult = battle.CurrentResult();
            if (menu == ForestBattle::Menu::Pause)
            {
                if (battle.Selection() == 0)
                {
                    battle.Back();
                }
                else
                {
                    ReturnToTitle();
                }
            }
            else if (menu == ForestBattle::Menu::Finished)
            {
                if (battle.Selection() == 0)
                {
                    battle.Start();
                }
                else
                {
                    ReturnToTitle();
                }
            }
            else
            {
                battle.Confirm();
            }
            if (battle.CurrentResult() == ForestBattle::Result::Clear &&
                beforeResult != ForestBattle::Result::Clear)
                MessageBeep(MB_ICONASTERISK);
            else if (battle.CurrentResult() == ForestBattle::Result::Defeat &&
                     beforeResult != ForestBattle::Result::Defeat)
                MessageBeep(MB_ICONHAND);
            else
                MessageBeep(MB_OK);
        }
    }
    else if (page == Page::Settings)
    {
        if (pressed[VK_UP])
        {
            if (settingSelected == 0)
            {
                settingSelected = 2;
            }
            else
            {
                settingSelected--;
            }
        }
        if (pressed[VK_DOWN])
        {
            if (settingSelected == 2)
            {
                settingSelected = 0;
            }
            else
            {
                settingSelected++;
            }
        }
        if (settingSelected == 0 && (pressed[VK_LEFT] || pressed[VK_RIGHT]))
        {
            int next = volumePercent;
            if (pressed[VK_RIGHT])
            {
                next += 10;
            }
            else
            {
                next -= 10;
            }
            next = (std::max)(0, (std::min)(100, next));
            audioAvailable = audio.SetVolume(next);
            if (audioAvailable)
            {
                volumePercent = next;
            }
        }
        else if (settingSelected == 1 &&
                 (pressed[VK_LEFT] || pressed[VK_RIGHT] || pressed[VK_RETURN]))
        {
            g2_ChangeWindow(!windowed);
            windowed = g2_GetWindowMode();
        }
        else if (settingSelected == 2 && pressed[VK_RETURN])
        {
            page = Page::Menu;
        }
    }
    else if (pressed[VK_RETURN])
    {
        page = Page::Menu;
    }
    return 0;
}
void SceneGameBegin::StartBattle()
{
    battle.Start();
    page = Page::Battle;
}
void SceneGameBegin::ReturnToTitle()
{
    page = Page::Menu;
    PlayMusic(mainBgm);
}
void SceneGameBegin::PlayMusic(int sound)
{
    if (sound < 0 || sound == currentBgm)
        return;
    if (currentBgm >= 0)
        g2_SoundStop(currentBgm);
    g2_SoundPlay(sound, true);
    currentBgm = sound;
}
int SceneGameBegin::Render() const
{
    if (texture < 0)
    {
        return 0;
    }
    const int width = g2_TextureWidth(texture);
    const int height = g2_TextureHeight(texture);
    if (width <= 0 || height <= 0)
    {
        return 0;
    }
    // 화면 비율을 유지하면서 창 전체를 채운다.
    const float scale = (std::max)(float(g2_GetScnW()) / width, float(g2_GetScnH()) / height);
    VEC2 scaling(scale, scale);
    VEC2 position((g2_GetScnW() - width * scale) / 2, (g2_GetScnH() - height * scale) / 2);
    if (page == Page::Battle)
    {
        int background = forestBackground;
        if (battle.CurrentBiome() == ForestBattle::Biome::Ruins)
            background = ruinsBackground;
        else if (battle.CurrentBiome() == ForestBattle::Biome::Cave)
            background = caveBackground;
        else if (battle.CurrentBiome() == ForestBattle::Biome::Citadel)
            background = citadelBackground;
        if (background >= 0)
        {
            int backgroundWidth = g2_TextureWidth(background);
            int backgroundHeight = g2_TextureHeight(background);
            float backgroundScale = (std::max)(float(g2_GetScnW()) / backgroundWidth,
                                               float(g2_GetScnH()) / backgroundHeight);
            VEC2 backgroundScaling(backgroundScale, backgroundScale);
            VEC2 backgroundPosition((g2_GetScnW() - backgroundWidth * backgroundScale) / 2,
                                    (g2_GetScnH() - backgroundHeight * backgroundScale) / 2);
            g2_Draw2D(background, nullptr, &backgroundPosition, &backgroundScaling, nullptr, 0,
                      0xff777777);
        }
    }
    else
    {
        g2_Draw2D(texture, nullptr, &position, &scaling);
    }
    float cx = g2_GetScnW() / 2.0f;
    float top = g2_GetScnH() * 0.70f;
    if (page == Page::Menu)
    {
        for (int i = 0; i < 3; ++i)
        {
            int y = int(top) + i * 64;
            DWORD color = 0xffd5c5a5;
            if (i == selected)
            {
                color = 0xffffd77a;
            }
            int x = int(cx) - menuWidths[i] / 2;
            DrawText(x, y, menuLabels[i], color);
            if (i == selected)
            {
                DrawText(x - 36, y, ">", color);
                DrawText(x + menuWidths[i] + 24, y, "<", color);
            }
        }
    }
    else if (page == Page::Settings)
    {
        DrawText(int(cx) - 50, int(top) - 64, "설정", 0xffffd77a);
        std::string volumeLabel = "사용 불가";
        if (audioAvailable)
        {
            volumeLabel = "<  " + std::to_string(volumePercent) + "%  >";
        }
        const char *labels[] = {"소리", "화면", "돌아가기"};
        for (int i = 0; i < 3; ++i)
        {
            int y = int(top) + i * 64;
            DWORD color = 0xffd5c5a5;
            if (settingSelected == i)
            {
                color = 0xffffd77a;
            }
            DrawText(int(cx) - 290, y, labels[i], color);
            if (settingSelected == i)
            {
                DrawText(int(cx) - 330, y, ">", color);
            }
            if (i == 0)
            {
                DrawText(int(cx) + 10, y, volumeLabel.c_str(), color);
            }
            if (i == 1)
            {
                const char *displayLabel = "< 전체 화면 >";
                if (windowed)
                {
                    displayLabel = "< 창 모드 >";
                }
                DrawText(int(cx) + 10, y, displayLabel, color);
            }
        }
    }
    else if (page == Page::Help)
    {
        if (pixel >= 0)
        {
            VEC2 position(100, 180), size(float(g2_GetScnW() - 200), 560);
            g2_Draw2D(pixel, nullptr, &position, &size, nullptr, 0, 0xf0101720);
        }
        DrawText(150, 220, "게임 방법", 0xffffd77a);
        const char *instructions[] = {
            "목표: 일반 전투 3회를 지나 성채 보스를 쓰러뜨리세요.",
            "방향키: 선택 이동   Enter: 확정 / 전투 메시지 계속",
            "공격이나 회복약을 사용하면 살아 있는 적이 반격합니다.",
            "승리 보상으로 강화하세요. 지역을 옮겨도 체력은 유지됩니다.",
            "도망에 성공하면 보상이 없습니다. 보스전에서는 도망칠 수 없습니다.",
            "Esc: 하위 메뉴 취소 / 전투 일시정지   A·B·Q: 공격·도망·회복약",
            "패배 후 새 도전을 시작하면 체력·도구·강화·점수가 초기화됩니다.",
            "Enter: 도전 시작     Esc: 타이틀로"};
        for (int i = 0; i < 8; ++i)
            DrawText(150, 300 + i * 48, instructions[i], 0xffedf0f4, true);
    }
    else if (page == Page::Battle)
    {
        RenderBattle();
    }
    return 0;
}
void SceneGameBegin::RenderBattle() const
{


    ForestBattle::Menu menu = battle.CurrentMenu();
    if (menu == ForestBattle::Menu::BiomeSelect)
    {
        DrawBattleText(70, "다음 바이옴 선택", 0xffffd77a);
        DrawPreview(ruinsBackground, 145, 210, 420);
        DrawPreview(caveBackground, 715, 210, 420);
        DrawBattleText(555, battle.Selection() == 0 ? "> 폐허 - 수호자의 땅 <" : "폐허 - 수호자의 땅",
             battle.Selection() == 0 ? 0xffffd77a : 0xffedf0f4);
        RECT caveBounds{715, 555, 1190, 591};
        std::string caveLabel = ToLocalText(battle.Selection() == 1 ? "> 동굴 - 박쥐의 둥지 <"
                                                                    : "동굴 - 박쥐의 둥지");
        g2_FontDrawText(smallFont, caveBounds,
                        battle.Selection() == 1 ? 0xffffd77a : 0xffedf0f4, "%s",
                        caveLabel.c_str());
        DrawBattleText(650, battle.Message(), 0xffffd77a);
        DrawBattleText(820, "← / → 선택   Enter 확정");
        return;
    }

    if (menu == ForestBattle::Menu::Reward)
    {
        DrawBattleText(65, "승리 보상 선택", 0xffffd77a);
        DrawBattleText(105, battle.Message());
        const char *names[] = {"공격 강화", "체력 강화", "도구 보급"};
        const char *effects[] = {"공격력 +5", "최대/현재 체력 +20", "회복약 +2"};
        const int iconWidth = rewardIcons >= 0 ? g2_TextureWidth(rewardIcons) / 3 : 0;
        const int iconHeight = rewardIcons >= 0 ? g2_TextureHeight(rewardIcons) : 0;
        for (int i = 0; i < 3; ++i)
        {
            const int cardWidth = (g2_GetScnW() - 240) / 3;
            const int cardX = 100 + i * (cardWidth + 20);
            DrawBox(cardX, 200, cardWidth, 420, 0xe0101720);
            DrawBox(cardX, 200, cardWidth, 4,
                i == battle.Selection() ? 0xffffd77a : 0xff777777);
            if (rewardIcons >= 0)
            {
                RECT source{i * iconWidth, 0, (i + 1) * iconWidth, iconHeight};
                float scaleFactor = (std::min)(230.0f / iconHeight,
                                               float(cardWidth - 40) / iconWidth);
                VEC2 position(cardX + (cardWidth - iconWidth * scaleFactor) / 2, 240.0f);
                VEC2 scale(scaleFactor, scaleFactor);
                g2_Draw2D(rewardIcons, &source, &position, &scale, nullptr, 0,
                          i == battle.Selection() ? 0xffffffff : 0xff777777);
            }
            RECT nameBounds{cardX + 20, 520, cardX + cardWidth - 20, 556};
            std::string name = ToLocalText(std::string(i == battle.Selection() ? "> " : "") +
                                           names[i]);
            g2_FontDrawText(smallFont, nameBounds,
                            i == battle.Selection() ? 0xffffd77a : 0xffedf0f4, "%s",
                            name.c_str());
            RECT effectBounds{cardX + 20, 565, cardX + cardWidth - 20, 601};
            std::string effect = ToLocalText(effects[i]);
            g2_FontDrawText(smallFont, effectBounds, 0xffedf0f4, "%s", effect.c_str());
        }
        DrawBattleText(820, "← / → 선택   Enter 확정");
        return;
    }

    int enemySprite = forestEnemySprite;
    if (battle.CurrentBiome() == ForestBattle::Biome::Ruins)
        enemySprite = ruinsEnemySprite;
    else if (battle.CurrentBiome() == ForestBattle::Biome::Cave)
        enemySprite = caveEnemySprite;
    else if (battle.CurrentBiome() == ForestBattle::Biome::Citadel)
        enemySprite = bossSprite;

    std::string progress = battle.IsBoss() ? "최종 보스전" :
        "일반 전투 " + std::to_string(battle.EncounterNumber()) + " / 3";
    DrawBattleText(45, battle.BiomeName() + " - " + progress, 0xffffd77a);
    DrawBattleText(82, "플레이어 체력: " + std::to_string(battle.PlayerHp()) + " / " +
                 std::to_string(battle.PlayerMaxHp()) + "   공격력: " +
                 std::to_string(battle.PlayerAttack()) + "   점수: " +
                 std::to_string(battle.Score()));
    DrawBattleText(118, battle.EnemyName() + " 체력: " + std::to_string(battle.EnemyHp()) + " / " +
                  std::to_string(battle.EnemyMaxHp()));
    const int barWidth = (g2_GetScnW() - 300) / 2;
    DrawHpBar(120, battle.PlayerHp(), battle.PlayerMaxHp(), 0xff77e1ba);
    DrawHpBar(180 + barWidth, battle.EnemyHp(), battle.EnemyMaxHp(), 0xffff8f8f);
    DrawSprite(playerSprite, 180, 235, 360);
    if (battle.EnemyHp() > 0)
        DrawSprite(enemySprite, 750, battle.IsBoss() ? 225.0f : 285.0f,
               battle.IsBoss() ? 380.0f : 310.0f);
    DrawBattleText(630, battle.Message(), 0xffffd77a);

    std::string options[3];
    int count = 0;
    if (menu == ForestBattle::Menu::Main)
    {
        options[0] = "공격";
        options[1] = "도구";
        options[2] = battle.IsBoss() ? "도망 (보스전 사용 불가)" : "도망 (성공 확률 60%)";
        count = 3;
    }
    else if (menu == ForestBattle::Menu::Attack)
    {
        options[0] = "기본 공격 - 피해 " + std::to_string(battle.PlayerAttack());
        options[1] = "강한 공격 - 피해 " + std::to_string(battle.PlayerAttack() * 3 / 2) +
                     ", 명중률 75%";
        options[2] = "흡수 공격 - 피해 " + std::to_string(battle.PlayerAttack() / 2) +
                     ", 준 피해의 절반 회복";
        count = 3;
    }
    else if (menu == ForestBattle::Menu::Item)
    {
        options[0] = "회복약 - 체력 30 회복 (" + std::to_string(battle.Potions()) + "개)";
        options[1] = "고급 회복약 - 체력 60 회복 (" + std::to_string(battle.SuperPotions()) + "개)";
        count = 2;
    }
    else if (menu == ForestBattle::Menu::Pause)
    {
        options[0] = "계속하기";
        options[1] = "타이틀로";
        count = 2;
    }
    else if (menu == ForestBattle::Menu::Finished)
    {
        options[0] = "새 도전 시작";
        options[1] = "타이틀로";
        count = 2;
        const char *resultText = battle.CurrentResult() == ForestBattle::Result::Clear
                                     ? "GAME CLEAR"
                                     : "GAME OVER";
        DrawBattleText(575, resultText,
             battle.CurrentResult() == ForestBattle::Result::Clear ? 0xff77e1ba : 0xffff8f8f);
        DrawBattleText(535, "최종 점수: " + std::to_string(battle.Score()));
    }

    for (int i = 0; i < count; ++i)
    {
        std::string choice = options[i];
        if (i == battle.Selection())
        {
            choice = "> " + choice;
        }
        DrawBattleText(700 + i * 45, choice);
        if (menu == ForestBattle::Menu::Item)
        {
            int itemSprite = potionSprite;
            if (i == 1)
            {
                itemSprite = superPotionSprite;
            }
            DrawSprite(itemSprite, 900, float(690 + i * 45), 42);
        }
    }
    if (menu == ForestBattle::Menu::Message)
    {
        DrawBattleText(700, "Enter - 계속");
    }
    else if (menu == ForestBattle::Menu::Attack || menu == ForestBattle::Menu::Item)
    {
        DrawBattleText(865, "Esc - 턴을 쓰지 않고 돌아가기");
    }
    else if (menu == ForestBattle::Menu::Main)
    {
        DrawBattleText(865, "A - 공격   B - 도망   Q - 회복약   Esc - 일시정지");
    }
}
int SceneGameBegin::Destroy()
{
    if (battleBgm >= 0)
    {
        g2_SoundStop(battleBgm);
        g2_SoundRelease(battleBgm);
        battleBgm = -1;
    }
    currentBgm = -1;
    if (mainBgm >= 0)
    {
        g2_SoundStop(mainBgm);
        g2_SoundRelease(mainBgm);
        mainBgm = -1;
    }
    audio.Destroy();
    if (texture >= 0)
    {
        g2_TextureRelease(texture);
        texture = -1;
    }
    int *battleTextures[] = {&pixel, &forestBackground,   &ruinsBackground, &caveBackground,
                             &citadelBackground,  &playerSprite,     &forestEnemySprite,
                             &ruinsEnemySprite,   &caveEnemySprite,  &bossSprite,
                             &potionSprite,       &superPotionSprite, &rewardIcons};
    for (int *id : battleTextures)
    {
        if (*id >= 0)
        {
            g2_TextureRelease(*id);
            *id = -1;
        }
    }
    return 0;
}

void SceneGameBegin::DrawText(int x, int y, const char *value, DWORD color, bool useSmallFont) const
{
    float cx = g2_GetScnW() / 2.0f;
    RECT bounds{x, y, int(cx + 420), y + 44};
    RECT shadow{x + 2, y + 2, int(cx + 422), y + 46};
    int textFont = font;
    if (useSmallFont)
    {
        textFont = smallFont;
    }
    std::string localValue = ToLocalText(value);
    g2_FontDrawText(textFont, shadow, 0xff18202a, "%s", localValue.c_str());
    g2_FontDrawText(textFont, bounds, color, "%s", localValue.c_str());
}

void SceneGameBegin::DrawBox(int x, int y, int width, int height, DWORD color) const
{
    if (pixel < 0 || width <= 0 || height <= 0)
        return;
    VEC2 position{float(x), float(y)}, size{float(width), float(height)};
    g2_Draw2D(pixel, nullptr, &position, &size, nullptr, 0, color);
}

void SceneGameBegin::DrawBattleText(int y, const std::string &value, DWORD color) const
{
    RECT bounds{120, y, g2_GetScnW() - 100, y + 36};
    RECT shadow{122, y + 2, g2_GetScnW() - 98, y + 38};
    std::string localValue = ToLocalText(value);
    g2_FontDrawText(smallFont, shadow, 0xff101720, "%s", localValue.c_str());
    g2_FontDrawText(smallFont, bounds, color, "%s", localValue.c_str());
}

void SceneGameBegin::DrawSprite(int id, float x, float y, float height) const
{
    if (id < 0 || g2_TextureWidth(id) <= 0 || g2_TextureHeight(id) <= 0)
    {
        return;
    }
    float scaleFactor = height / g2_TextureHeight(id);
    VEC2 position(x, y);
    VEC2 scale(scaleFactor, scaleFactor);
    g2_Draw2D(id, nullptr, &position, &scale);
}

void SceneGameBegin::DrawPreview(int id, float x, float y, float width) const
{
    if (id < 0 || g2_TextureWidth(id) <= 0 || g2_TextureHeight(id) <= 0)
        return;
    float scaleFactor = width / g2_TextureWidth(id);
    VEC2 position(x, y);
    VEC2 scale(scaleFactor, scaleFactor);
    g2_Draw2D(id, nullptr, &position, &scale, nullptr, 0, 0xffbbbbbb);
}

void SceneGameBegin::DrawHpBar(int x, int hp, int maxHp, DWORD color) const
{
    const int barWidth = (g2_GetScnW() - 300) / 2;
    DrawBox(x, 165, barWidth, 22, 0xff101720);
    const int fill = maxHp > 0 ? (barWidth - 4) * hp / maxHp : 0;
    DrawBox(x + 2, 167, fill, 18, color);
}
