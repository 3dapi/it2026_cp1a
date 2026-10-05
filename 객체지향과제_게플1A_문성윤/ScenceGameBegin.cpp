#include "ScenceGameBegin.h"

namespace
{
const RECT Start{160, 830, 800, 940};
const RECT Exit{160, 970, 800, 1080};
} // namespace

int ScenceGameBegin::Init()
{
    m_background = g2_TextureLoad("resource/background/bg_corridor.png");
    return m_background < 0 ? -1 : 0;
}

int ScenceGameBegin::Destroy()
{
    if (m_background >= 0)
        g2_TextureRelease(m_background);
    m_background = -1;
    return 0;
}

bool ScenceGameBegin::Update(const GameUI &ui)
{
    if (ui.Clicked(Exit) || ui.Pressed(VK_ESCAPE))
        PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
    bool start = ui.Advance() || ui.Clicked(Start);
    if (start)
        ui.PlaySelect();
    return start;
}

void ScenceGameBegin::Render(const GameUI &ui)
{
    ui.Image(m_background, 0, 0, 1920, 1440);
    ui.Panel({0, 0, 1920, 1440}, 0x6607101A);
    ui.Panel({100, 250, 1000, 1170}, 0xBF101923);
    ui.Text("THE LAST CLUE", {160, 320, 960, 400}, 0, 0xFFD4BB86);
    ui.Text("마지막 단서", {150, 420, 1100, 590}, 2);
    ui.Text("사흘째, 폐교에서 내 이름을 부르는 목소리.", {160, 640, 1100, 715});
    ui.Text("그 목소리의 주인을 만나러 간다.", {160, 710, 1100, 785});
    ui.Button("이야기 시작   [Enter]", Start);
    ui.Button("게임 종료   [Esc]", Exit);
    ui.Text("문성윤  |  26311027", {160, 1280, 900, 1340}, 0);
}
