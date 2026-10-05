#include "SceneBegin.h"
#include "glc2d.h"
#include "CApplication.h"

extern CApplication g_app;

int SceneBegin::Init()
{
    m_txBG = g2_TextureLoad(
        "resource/texture/begin/BG_Begin.png"
    );

    m_txUI_start = g2_TextureLoad(
        "resource/texture/begin/ui_START.png"
    );

    m_txUI_exit = g2_TextureLoad(
        "resource/texture/begin/ui_EXIT.png"
    );

    m_txUI_chose = g2_TextureLoad(
        "resource/texture/begin/ui_CHOSE.png"
    );

    m_select = 0;

    return 0;
}

int SceneBegin::Update()
{
    int mouseX = g2_GetMouseX();
    int mouseY = g2_GetMouseY();

    if (mouseX >= 1050 && mouseX <= 1650 &&
        mouseY >= 480 && mouseY <= 620)
    {
        m_select = 0;
    }

    if (mouseX >= 1050 && mouseX <= 1650 &&
        mouseY >= 630 && mouseY <= 770)
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

int SceneBegin::Render()
{
    {
        VEC2 position_BG{ 0.0f, 0.0f };
        VEC2 scale_BG{ 1.0f, 1.0f };

        g2_Draw2D(
            m_txBG,
            nullptr,
            &position_BG,
            &scale_BG
        );
    }

    {
        VEC2 position_UI_start{ 1050.0f, 470.0f };
        VEC2 scale_UI_start{ 0.30f, 0.30f };

        g2_Draw2D(
            m_txUI_start,
            nullptr,
            &position_UI_start,
            &scale_UI_start
        );
    }

    {
        VEC2 position_UI_exit{ 1050.0f, 620.0f };
        VEC2 scale_UI_exit{ 0.30f, 0.30f };

        g2_Draw2D(
            m_txUI_exit,
            nullptr,
            &position_UI_exit,
            &scale_UI_exit
        );
    }

    {
        VEC2 position_UI_chose;
        VEC2 scale_UI_chose{ 0.30f, 0.30f };

        if (m_select == 0)
        {
            position_UI_chose = VEC2{ 1050.0f, 464.0f };
        }
        else
        {
            position_UI_chose = VEC2{ 1050.0f, 614.0f };
        }

        g2_Draw2D(
            m_txUI_chose,
            nullptr,
            &position_UI_chose,
            &scale_UI_chose
        );
    }

    return 0;
}

int SceneBegin::Destroy()
{
    g2_TextureRelease(m_txBG);
    g2_TextureRelease(m_txUI_start);
    g2_TextureRelease(m_txUI_exit);
    g2_TextureRelease(m_txUI_chose);

    m_txBG = -1;
    m_txUI_start = -1;
    m_txUI_exit = -1;
    m_txUI_chose = -1;

    return 0;
}