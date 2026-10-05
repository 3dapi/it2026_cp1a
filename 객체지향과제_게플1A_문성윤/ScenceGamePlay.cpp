#include "ScenceGamePlay.h"
#include <cstdio>
#include <cstring>

namespace
{
const RECT Next{1460, 1260, 1830, 1360};
const RECT Menu{1510, 35, 1860, 115};
const RECT Items{1510, 135, 1860, 215};
const RECT Choices[2]{{200, 730, 1720, 840}, {200, 870, 1720, 980}};
const RECT Commands[4]{{90, 850, 510, 970}, {530, 850, 950, 970},
    {970, 850, 1390, 970}, {1410, 850, 1830, 970}};
const RECT Dialog{90, 1020, 1830, 1370};
const RECT OverlayPanel{410, 360, 1510, 1080};
const RECT Resume{540, 720, 1380, 830};
const RECT Exit{540, 870, 1380, 980};
const RECT CloseItems{540, 890, 1380, 1000};
}

int ScenceGamePlay::Init()
{
    m_background = g2_TextureLoad("resource/background/bg_corridor.png");
    m_classroom = g2_TextureLoad("resource/background/bg_classroom.png");
    m_character = g2_TextureLoad("resource/character/ghost_seoyeon.png", 0);
    m_shadow = g2_TextureLoad("resource/character/ghost_shadow.png", 0);
    m_attackSound = g2_SoundLoad("resource/sound/se_attack.mp3");
    m_healSound = g2_SoundLoad("resource/sound/se_heal.mp3");
    Reset();
    return m_background < 0 || m_classroom < 0 || m_character < 0 || m_shadow < 0 ||
        m_attackSound < 0 || m_healSound < 0 ? -1 : 0;
}

void ScenceGamePlay::Reset()
{
    m_story.Reset();
    m_battle.Reset();
    m_stage = Stage::Story;
    m_overlay = Overlay::None;
    m_choiceFocus = m_menuFocus = 0;
}

int ScenceGamePlay::Destroy()
{
    for (int* sound : {&m_attackSound, &m_healSound})
    {
        if (*sound >= 0) { g2_SoundStop(*sound); g2_SoundRelease(*sound); }
        *sound = -1;
    }
    for (int* texture : {&m_background, &m_classroom, &m_character, &m_shadow})
    {
        if (*texture >= 0) g2_TextureRelease(*texture);
        *texture = -1;
    }
    return 0;
}

bool ScenceGamePlay::UpdateOverlay(const GameUI& ui)
{
    // Every open/close action consumes this update; no input reaches the story.
    if (m_overlay == Overlay::Items)
    {
        if (ui.Pressed(VK_ESCAPE) || ui.Pressed('I') || ui.Advance() || ui.Clicked(CloseItems))
        {
            ui.PlaySelect();
            m_overlay = Overlay::None;
        }
        return true;
    }
    if (m_overlay == Overlay::Pause)
    {
        if (ui.Pressed(VK_ESCAPE) || ui.Clicked(Menu))
        {
            ui.PlaySelect();
            m_overlay = Overlay::None;
            return true;
        }
        if (ui.Pressed(VK_UP) || ui.Pressed(VK_DOWN)) m_menuFocus = 1 - m_menuFocus;
        if (ui.Clicked(Exit) || ui.Pressed('2') || (ui.Pressed(VK_RETURN) && m_menuFocus == 1))
        {
            ui.PlaySelect();
            PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
        }
        else if (ui.Clicked(Resume) || ui.Pressed('1') || (ui.Pressed(VK_RETURN) && m_menuFocus == 0))
        {
            ui.PlaySelect();
            m_overlay = Overlay::None;
        }
        return true;
    }
    if (ui.Pressed(VK_ESCAPE) || ui.Clicked(Menu))
    {
        ui.PlaySelect();
        m_overlay = Overlay::Pause;
        m_menuFocus = 0;
        return true;
    }
    if (ui.Pressed('I') || ui.Clicked(Items))
    {
        ui.PlaySelect();
        m_overlay = Overlay::Items;
        return true;
    }
    return false;
}

bool ScenceGamePlay::Update(const GameUI& ui, Player& player)
{
    if (UpdateOverlay(ui)) return false;
    if (m_stage == Stage::Complete) return true;
    if (m_stage == Stage::Battle)
    {
        if (m_battle.GetPhase() == BattleProgress::Phase::Choosing)
        {
            if (ui.Pressed(VK_UP)) m_choiceFocus = (m_choiceFocus + 3) % 4;
            else if (ui.Pressed(VK_DOWN)) m_choiceFocus = (m_choiceFocus + 1) % 4;
            int selection = -1;
            for (int i = 0; i < 4; ++i)
                if (ui.Pressed('1' + i) || ui.Clicked(Commands[i])) { selection = i; break; }
            if (selection < 0 && ui.Pressed(VK_RETURN)) selection = m_choiceFocus;
            if (selection >= 0 && m_battle.Choose(static_cast<BattleProgress::Command>(selection), player))
            {
                m_choiceFocus = selection;
                ui.PlaySelect();
                PlayBattleSound();
            }
        }
        else if (ui.Advance() || ui.Clicked(Next) || ui.Clicked(Dialog))
        {
            ui.PlaySelect();
            m_battle.Advance(player);
            PlayBattleSound();
            if (m_battle.IsFinished())
            {
                m_story.BeginEnding(m_battle.GetPhase() == BattleProgress::Phase::Won, player);
                m_stage = Stage::Ending;
                m_choiceFocus = 0;
            }
        }
        return false;
    }
    if (m_story.IsChoosing())
    {
        if (ui.Pressed(VK_UP) || ui.Pressed(VK_DOWN)) m_choiceFocus = 1 - m_choiceFocus;
        int selection = -1;
        if (ui.Pressed('1') || ui.Clicked(Choices[0])) selection = 0;
        else if (ui.Pressed('2') || ui.Clicked(Choices[1])) selection = 1;
        else if (ui.Pressed(VK_RETURN)) selection = m_choiceFocus;
        if (selection >= 0 && m_story.Choose(selection, player))
        {
            ui.PlaySelect();
            m_choiceFocus = 0;
        }
        return false;
    }
    if (ui.Advance() || ui.Clicked(Next) || ui.Clicked(Dialog))
    {
        ui.PlaySelect();
        m_story.Advance(player);
        m_choiceFocus = 0;
        if (player.GetLife() == 0 && m_stage == Stage::Story)
        {
            m_story.BeginEnding(false, player);
            m_stage = Stage::Ending;
        }
        else if (m_story.IsComplete())
        {
            if (m_stage == Stage::Ending) { m_stage = Stage::Complete; return true; }
            m_battle.Start(m_story.HasPhoto(), m_story.HasRecord());
            m_stage = Stage::Battle;
        }
    }
    return false;
}

void ScenceGamePlay::Render(const GameUI& ui, const Player& player)
{
    if (m_stage == Stage::Battle) RenderBattle(ui, player);
    else RenderStory(ui, player);
    if (m_overlay != Overlay::None) RenderOverlay(ui);
}

void ScenceGamePlay::RenderStatus(const GameUI& ui, const Player& player, const char* title, bool classroom)
{
    ui.Panel({30, 35, 1460, 215}, 0xE8101923);
    char text[256];
    sprintf_s(text, "%s | %s", classroom ? "폐교 교실" : "폐교 복도", title);
    ui.Text(text, {60, 55, 1430, 105}, 0, 0xFFD4BB86);
    sprintf_s(text, "서준 HP %d / LIFE %d / 점수 %d / 핵심 단서 %d / 2",
        player.GetHP(), player.GetLife(), player.GetScore(), m_story.ClueCount());
    ui.Text(text, {60, 110, 1430, 160}, 0);
    sprintf_s(text, "회복약 %d개 | 열쇠 %s | 사진 %s | 기록 %s", m_battle.Potions(),
        m_story.HasKey() ? "보유" : "없음", m_story.HasPhoto() ? "보유" : "없음", m_story.HasRecord() ? "보유" : "없음");
    ui.Text(text, {60, 165, 1430, 210}, 0, 0xFFABBDCD);
    ui.Button("메뉴 [Esc]", Menu);
    ui.Button("아이템 [I]", Items);
}

void ScenceGamePlay::RenderDialogue(const GameUI& ui, const char* speaker, const char* text, bool choosing)
{
    ui.Panel(Dialog, 0xF2101923);
    ui.Panel({90, 1020, 1830, 1025}, 0xFFD4BB86);
    ui.Text(speaker, {140, 1060, 1790, 1130}, 1, 0xFFD4BB86);
    ui.Text(text, {140, 1145, 1790, 1265});
    if (!choosing)
    {
        ui.Text("Enter / Space / 대화창 클릭", {140, 1290, 1260, 1350}, 0, 0xFFABBDCD);
        ui.Button("다음 >", Next);
    }
}

void ScenceGamePlay::RenderStory(const GameUI& ui, const Player& player)
{
    const auto& section = m_story.Section();
    const auto& line = m_story.Line();
    const bool classroom = section.chapter >= 5;
    ui.Image(classroom ? m_classroom : m_background, 0, 0, 1920, 1440);
    if (line.visual == StoryVisual::Both)
    {
        ui.Image(m_character, 180, 195, 700, 1080, std::strcmp(line.speaker, "그림자") == 0 ? 0xFFAAAAAA : 0xFFFFFFFF);
        ui.Image(m_shadow, 1070, 165, 700, 1080, std::strcmp(line.speaker, "서연") == 0 ? 0xFFAAAAAA : 0xFFFFFFFF);
    }
    else if (line.visual == StoryVisual::Seoyeon) ui.Image(m_character, 980, 135, 778, 1200);
    RenderStatus(ui, player, section.title, classroom);
    if (m_story.IsChoosing())
        for (int i = 0; i < 2; ++i)
        {
            const auto& r = Choices[i];
            if (i == m_choiceFocus) ui.Panel({r.left - 5, r.top - 5, r.right + 5, r.bottom + 5}, 0xFFD4BB86);
            char label[256];
            sprintf_s(label, "%d. %s", i + 1, section.options[i]);
            ui.Button(label, r);
        }
    RenderDialogue(ui, line.speaker, line.text, m_story.IsChoosing());
    if (m_story.IsChoosing()) ui.Text("위 / 아래 + Enter | 숫자 1 / 2 | 선택지 클릭", {140, 1300, 1770, 1360}, 0, 0xFFABBDCD);
}

void ScenceGamePlay::PlayBattleSound() const
{
    const auto sound = m_battle.GetSound();
    const int handle = sound == BattleProgress::Sound::Attack ? m_attackSound : sound == BattleProgress::Sound::Heal ? m_healSound : -1;
    if (handle >= 0) { g2_SoundStop(handle); g2_SoundPlay(handle); }
}

void ScenceGamePlay::RenderBattle(const GameUI& ui, const Player& player)
{
    ui.Image(m_classroom, 0, 0, 1920, 1440);
    ui.Image(m_character, 180, 195, 700, 1080, std::strcmp(m_battle.Speaker(), "그림자") == 0 ? 0xFFAAAAAA : 0xFFFFFFFF);
    if (m_battle.Visual() == StoryVisual::Both)
        ui.Image(m_shadow, 1070, 165, 700, 1080, std::strcmp(m_battle.Speaker(), "서연") == 0 ? 0xFFAAAAAA : 0xFFFFFFFF);
    RenderStatus(ui, player, m_battle.EnemyHP() == 0 ? "그림자가 흩어지다" : "마지막 전투", true);
    char text[256];
    if (m_battle.EnemyHP() > 0 && !m_battle.IsFinished())
    {
        ui.Panel({1060, 245, 1860, 415}, 0xE8101923);
        sprintf_s(text, "그림자 HP %d / 100 | %d턴", m_battle.EnemyHP(), m_battle.Turn());
        ui.Text(text, {1090, 260, 1830, 310});
        ui.Panel({1090, 325, 1830, 350}, 0xFF333344);
        ui.Panel({1090, 325, 1090 + m_battle.EnemyHP() * 740 / 100, 350}, 0xFFB45D67);
        sprintf_s(text, "적 행동 예고: %s / 예상 피해 %d", m_battle.ExpectedDamage() == 25 ? "강한 공격" : "일반 공격", m_battle.ExpectedDamage());
        ui.Text(text, {1090, 365, 1840, 410}, 0, 0xFFD4BB86);
    }
    const bool choosing = m_battle.GetPhase() == BattleProgress::Phase::Choosing;
    if (choosing)
    {
        const char* labels[]{"1. 공격 (-20)", "2. 방어 (피해 10)", "3. 회복 (+30)", "4. 단서 (-40)"};
        for (int i = 0; i < 4; ++i)
        {
            const auto& r = Commands[i];
            const bool enabled = m_battle.CanUse(static_cast<BattleProgress::Command>(i), player);
            if (i == m_choiceFocus) ui.Panel({r.left - 5, r.top - 5, r.right + 5, r.bottom + 5}, 0xFFD4BB86);
            ui.Panel(r, enabled ? (ui.Hit(r) ? 0xEE456074 : 0xF21A2939) : 0xF222252A);
            ui.Text(labels[i], {r.left + 14, r.top + 18, r.right - 8, r.top + 65}, 0, enabled ? 0xFFF2EEE7 : 0xFF858585);
            if (!enabled)
            {
                const char* reason = i == 2 ? (m_battle.Potions() == 0 ? "회복약 없음" : "HP 최대") :
                    m_battle.ClueUsed() ? "이미 활용함" : "단서 없음";
                ui.Text(reason, {r.left + 14, r.top + 68, r.right - 8, r.bottom - 5}, 0, 0xFF858585);
            }
        }
    }
    RenderDialogue(ui, m_battle.Speaker(), m_battle.Message(), choosing);
    if (choosing) ui.Text("위 / 아래 + Enter | 숫자 1~4 | 명령 클릭", {140, 1290, 1770, 1350}, 0, 0xFFABBDCD);
}

void ScenceGamePlay::RenderOverlay(const GameUI& ui) const
{
    ui.Panel({0, 0, 1920, 1440}, 0xB007101A);
    ui.Panel(OverlayPanel, 0xFA101923);
    ui.Panel({410, 360, 1510, 367}, 0xFFD4BB86);
    if (m_overlay == Overlay::Items)
    {
        ui.Text("소지 아이템", {480, 420, 1450, 500}, 1, 0xFFD4BB86);
        char text[128];
        sprintf_s(text, "회복약: %d개 (전투 명령에서 사용)", m_battle.Potions());
        ui.Text(text, {480, 550, 1450, 610});
        sprintf_s(text, "열쇠: %s", m_story.HasKey() ? "보유" : "없음");
        ui.Text(text, {480, 630, 1450, 690});
        sprintf_s(text, "사진: %s", m_story.HasPhoto() ? "보유" : "없음");
        ui.Text(text, {480, 710, 1450, 770});
        sprintf_s(text, "사고 기록: %s", m_story.HasRecord() ? "보유" : "없음");
        ui.Text(text, {480, 790, 1450, 850});
        ui.Button("닫기 [Esc / I / Enter]", CloseItems);
    }
    else
    {
        ui.Text("일시 정지", {480, 420, 1450, 500}, 1, 0xFFD4BB86);
        ui.Text("위 / 아래 + Enter | 숫자 1 / 2 | Esc로 재개", {480, 560, 1450, 625});
        const RECT& focus = m_menuFocus == 0 ? Resume : Exit;
        ui.Panel({focus.left - 5, focus.top - 5, focus.right + 5, focus.bottom + 5}, 0xFFD4BB86);
        ui.Button("1. 재개", Resume);
        ui.Button("2. 게임 종료", Exit);
    }
}
