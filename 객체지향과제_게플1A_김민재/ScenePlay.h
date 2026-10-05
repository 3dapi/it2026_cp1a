#pragma once

class ScenePlay
{
public:
    int Init();
    int Update();
    int Render();
    int Destroy();

protected:
    int m_txBG = -1;
    int m_txPlayer = -1;
    int m_txObstacle = -1;

    int m_font = -1;

    int m_playerX = 100;
    int m_playerY = 500;

    int m_playerSpeed = 5;

    int m_jumpSpeed = 0;
    bool m_isJumping = false;

    int m_obstacleX = 700;
    int m_obstacleY = 550;

    int m_obstacleX2 = 1050;
    int m_obstacleY2 = 550;

    int m_obstacleX3 = 1250;
    int m_obstacleY3 = 550;

    int m_hp = 3;
    int m_score = 0;
};