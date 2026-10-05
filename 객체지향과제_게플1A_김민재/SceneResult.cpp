#include "SceneResult.h"
#include "glc2d.h"
#include "CApplication.h"
#include <windows.h>

extern CApplication g_app;

int SceneResult::Init()
{
    g2_SetClearColor(0xFF000000);

    m_font = g2_FontCreate("Arial", 40);

    m_select = 0;

    return 0;
}

void SceneResult::SetResult(bool clear)
{
    m_clear = clear;
}

int SceneResult::Update()
{
    int mouseX = g2_GetMouseX();
    int mouseY = g2_GetMouseY();

    if (mouseX >= 400 && mouseX <= 1000 &&
        mouseY >= 450 && mouseY <= 600)
    {
        m_select = 0;
    }

    if (mouseX >= 400 && mouseX <= 1000 &&
        mouseY >= 600 && mouseY <= 750)
    {
        m_select = 1;
    }

    if (g2_GetMouseEvent(0) == EINPUT_DOWN)
    {
        if (m_select == 0)
        {
            g_app.ChangeScene(SceneType::PLAY);
        }
        else if (m_select == 1)
        {
            PostQuitMessage(0);
        }
    }

    return 0;
}

int SceneResult::Render()
{
    RECT rcTitle{ 500, 180, 1000, 250 };
    RECT rcScore{ 500, 280, 1000, 340 };
    RECT rcStart{ 500, 500, 850, 580 };
    RECT rcExit{ 500, 600, 850, 680 };

    if (m_clear)
    {
        g2_FontDrawText(
            m_font,
            rcTitle,
            0xFFFFFFFF,
            "GAME CLEAR"
        );
    }
    else
    {
        g2_FontDrawText(
            m_font,
            rcTitle,
            0xFFFFFFFF,
            "GAME OVER"
        );
    }

    g2_FontDrawText(
        m_font,
        rcScore,
        0xFFFFFFFF,
        "SCORE : %d",
        g_app.m_score
    );

    g2_FontDrawText(
        m_font,
        rcStart,
        0xFFFFFFFF,
        "RESTART"
    );

    g2_FontDrawText(
        m_font,
        rcExit,
        0xFFFFFFFF,
        "EXIT"
    );

    return 0;
}

int SceneResult::Destroy()
{
    m_font = -1;

    return 0;
}