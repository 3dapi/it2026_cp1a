#include "CApplication.h"

void SceneGameBegin::Render()
{
    g_app.DrawImage(TitleImage, 0, 0, 1280, 720);
    g2_FontDrawText(g_app.m_largeFont, { 340, 575, 1100, 650 }, 0xFFDBFF89, "SPACE TO START");
    g2_FontDrawText(g_app.m_font, { 300, 650, 1200, 705 }, 0xFFFFFFFF, "Press the matching A / S / D / F key!   ESC: Exit");
}

void SceneGameBegin::Update()
{
    if (g_app.Pressed(VK_SPACE)) g_app.StartGame();
}
