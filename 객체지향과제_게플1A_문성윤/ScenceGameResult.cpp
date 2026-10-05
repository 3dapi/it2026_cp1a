#include "ScenceGameResult.h"
#include <cstdio>

namespace
{
const RECT Restart{260, 1060, 920, 1170};
const RECT Exit{1000, 1060, 1660, 1170};
}

int ScenceGameResult::Init()
{
    m_background = g2_TextureLoad("resource/background/bg_corridor.png");
    return m_background < 0 ? -1 : 0;
}

void ScenceGameResult::SetResult(EndingKind ending, int score, int clues)
{
    m_ending = ending;
    m_score = score;
    m_clues = clues;
    m_focus = 0;
}

bool ScenceGameResult::Update(const GameUI& ui)
{
    if (ui.Pressed(VK_LEFT) || ui.Pressed(VK_RIGHT) || ui.Pressed(VK_UP) || ui.Pressed(VK_DOWN)) m_focus = 1 - m_focus;
    if (ui.Clicked(Exit) || ui.Pressed(VK_ESCAPE) || ui.Pressed('2') || (ui.Pressed(VK_RETURN) && m_focus == 1))
    {
        ui.PlaySelect();
        PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
        return false;
    }
    if (ui.Clicked(Restart) || ui.Pressed('1') || ui.Pressed(VK_SPACE) || (ui.Pressed(VK_RETURN) && m_focus == 0))
    {
        ui.PlaySelect();
        return true;
    }
    return false;
}

void ScenceGameResult::Render(const GameUI& ui)
{
    const char* kind = m_ending == EndingKind::Good ? "좋은 결말" : m_ending == EndingKind::Normal ? "보통 결말" : "실패 결말";
    const char* title = m_ending == EndingKind::Good ? "마지막 단서" :
        m_ending == EndingKind::Normal ? "사실과 마음의 거리" :
        m_ending == EndingKind::MissingClues ? "확인하지 못한 빈칸" : "여기서 멈추는 조사";
    const char* description = m_ending == EndingKind::Good ? "두 단서로 진실을 확인했다.\n서연은 자신의 기억을 받아들이고 교실을 떠났다." :
        m_ending == EndingKind::Normal ? "사건의 사실은 확인했다.\n서연은 남은 마음을 천천히 정리하기로 했다." :
        m_ending == EndingKind::MissingClues ? "그림자는 물리쳤지만 단서가 부족했다.\n서연의 기억에는 확인하지 못한 빈칸이 남았다." :
        "Life를 모두 소진했다.\n서연은 서준을 밖으로 보내며 조사를 끝냈다.";
    ui.Image(m_background, 0, 0, 1920, 1440);
    ui.Panel({0, 0, 1920, 1440}, 0x9907101A);
    ui.Panel({160, 220, 1760, 1240}, 0xF0101923);
    ui.Text(kind, {260, 300, 1650, 360}, 1, 0xFFD4BB86);
    ui.Text(title, {260, 430, 1650, 560}, 1);
    ui.Text(description, {260, 630, 1650, 800});
    char summary[128];
    sprintf_s(summary, "최종 점수 %d / 120   |   핵심 단서 %d / 2", m_score, m_clues);
    ui.Text(summary, {260, 860, 1650, 940}, 1, 0xFFD4BB86);
    ui.Text("다시 시작하면 모든 진행 상태가 초기화됩니다.", {260, 970, 1650, 1020});
    const RECT& focus = m_focus == 0 ? Restart : Exit;
    ui.Panel({focus.left - 5, focus.top - 5, focus.right + 5, focus.bottom + 5}, 0xFFD4BB86);
    ui.Button("1. 다시 시작", Restart);
    ui.Button("2. 게임 종료 [Esc]", Exit);
    ui.Text("방향키 + Enter | 숫자 1 / 2 | Space로 다시 시작", {260, 1300, 1660, 1360});
}

int ScenceGameResult::Destroy()
{
    if (m_background >= 0) g2_TextureRelease(m_background);
    m_background = -1;
    return 0;
}
