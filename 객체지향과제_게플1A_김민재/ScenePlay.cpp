#include "ScenePlay.h"
#include "glc2d.h"
#include "CApplication.h"
#include <windows.h>

extern CApplication g_app;

int ScenePlay::Init()
{
    g2_SetClearColor(0xFF000000);

    m_txBG = g2_TextureLoad(
        "resource/texture/play/BG_Play.png"
    );

    m_txPlayer = g2_TextureLoad(
        "resource/texture/play/player.png"
    );

    m_txObstacle = g2_TextureLoad(
        "resource/texture/play/obstacle.png"
    );

    m_font = g2_FontCreate("Arial", 30);

    m_playerX = 100;
    m_playerY = 500;

    m_playerSpeed = 5;

    m_jumpSpeed = 0;
    m_isJumping = false;

    m_obstacleX = 700;
    m_obstacleY = 550;

    m_obstacleX2 = 1050;
    m_obstacleY2 = 550;

    m_obstacleX3 = 1250;
    m_obstacleY3 = 550;

    m_hp = 3;
    m_score = 0;

    return 0;
}

int ScenePlay::Update()
{
    const KEYCODE* keyboard = g2_GetKeyboard();

    if (keyboard['A'] != EINPUT_NONE)
    {
        m_playerX -= m_playerSpeed;
    }

    if (keyboard['D'] != EINPUT_NONE)
    {
        m_playerX += m_playerSpeed;
    }

    if (m_playerX < 0)
    {
        m_playerX = 0;
    }

    if (m_playerX > 1300)
    {
        m_playerX = 1300;
    }

    if (keyboard[VK_SPACE] == EINPUT_DOWN &&
        !m_isJumping)
    {
        m_isJumping = true;
        m_jumpSpeed = -15;
    }

    if (m_isJumping)
    {
        m_playerY += m_jumpSpeed;
        m_jumpSpeed += 1;

        if (m_playerY >= 500)
        {
            m_playerY = 500;
            m_jumpSpeed = 0;
            m_isJumping = false;
        }
    }

    m_score = m_playerX / 10;

    // hole
    if (m_playerX >= 450 &&
        m_playerX <= 550 &&
        !m_isJumping)
    {
        g_app.m_score = m_score;
        g_app.ShowResult(false);
        return 0;
    }

    // obstacle 1
    if (m_playerX + 50 >= m_obstacleX &&
        m_playerX <= m_obstacleX + 60 &&
        m_playerY + 70 >= m_obstacleY &&
        m_playerY <= m_obstacleY + 60)
    {
        m_hp--;
        m_playerX = m_obstacleX - 70;
    }

    // obstacle 2
    if (m_playerX + 50 >= m_obstacleX2 &&
        m_playerX <= m_obstacleX2 + 60 &&
        m_playerY + 70 >= m_obstacleY2 &&
        m_playerY <= m_obstacleY2 + 60)
    {
        m_hp--;
        m_playerX = m_obstacleX2 - 70;
    }

    // obstacle 3
    if (m_playerX + 50 >= m_obstacleX3 &&
        m_playerX <= m_obstacleX3 + 60 &&
        m_playerY + 70 >= m_obstacleY3 &&
        m_playerY <= m_obstacleY3 + 60)
    {
        m_hp--;
        m_playerX = m_obstacleX3 - 70;
    }

    if (m_hp <= 0)
    {
        g_app.m_score = m_score;
        g_app.ShowResult(false);
        return 0;
    }

    if (m_playerX >= 1250)
    {
        g_app.m_score = m_score;
        g_app.ShowResult(true);
        return 0;
    }

    return 0;
}

int ScenePlay::Render()
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
        VEC2 position_player{
            (float)m_playerX,
            (float)m_playerY
        };

        VEC2 scale_player{ 1.0f, 0.2f };

        g2_Draw2D(
            m_txPlayer,
            nullptr,
            &position_player,
            &scale_player
        );
    }

    {
        VEC2 position_obstacle{
            (float)m_obstacleX,
            (float)m_obstacleY
        };

        VEC2 scale_obstacle{ 1.0f, 1.0f };

        g2_Draw2D(
            m_txObstacle,
            nullptr,
            &position_obstacle,
            &scale_obstacle
        );
    }

    {
        VEC2 position_obstacle{
            (float)m_obstacleX2,
            (float)m_obstacleY2
        };

        VEC2 scale_obstacle{ 1.0f, 1.0f };

        g2_Draw2D(
            m_txObstacle,
            nullptr,
            &position_obstacle,
            &scale_obstacle
        );
    }

    {
        VEC2 position_obstacle{
            (float)m_obstacleX3,
            (float)m_obstacleY3
        };

        VEC2 scale_obstacle{ 1.0f, 1.0f };

        g2_Draw2D(
            m_txObstacle,
            nullptr,
            &position_obstacle,
            &scale_obstacle
        );
    }

    RECT rcHP{ 50, 40, 400, 90 };
    RECT rcScore{ 1450, 40, 1720, 90 };

    g2_FontDrawText(
        m_font,
        rcHP,
        0xFFFFFFFF,
        "HP : %d",
        m_hp
    );

    g2_FontDrawText(
        m_font,
        rcScore,
        0xFFFFFFFF,
        "SCORE : %d",
        m_score
    );

    return 0;
}

int ScenePlay::Destroy()
{
    g2_TextureRelease(m_txBG);
    g2_TextureRelease(m_txPlayer);
    g2_TextureRelease(m_txObstacle);

    m_txBG = -1;
    m_txPlayer = -1;
    m_txObstacle = -1;

    m_font = -1;

    return 0;
}