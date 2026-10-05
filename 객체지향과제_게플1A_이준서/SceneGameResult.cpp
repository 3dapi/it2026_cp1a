#include "CApplication.h"

void SceneGameResult::Render()
{
    g_app.DrawImage(BackgroundImage, 0, 0, 1280, 720, 0xFF444444);
    g2_FontDrawText(g_app.m_keyFont, { 335, 175, 1200, 300 }, 0xFFFF8866, "GAME OVER");
    g2_FontDrawText(g_app.m_largeFont, { 460, 335, 1100, 420 }, 0xFFFFFFFF, "SCORE: %d", g_app.m_scenePlay.m_rules.m_score);
    g2_FontDrawText(g_app.m_font, { 395, 490, 1200, 550 }, 0xFFDBFF89, "SPACE : Play Again      ESC : Exit");
}

void SceneGameResult::Update()
{
    if (g_app.Pressed(VK_SPACE)) g_app.StartGame();
}
