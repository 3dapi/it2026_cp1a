#pragma once
#include "glc2d.h"

class ScenePlay
{
public:
    int Init();
    int Destroy();
    int Render();
    int Update();

private:
    int m_lineTexture = -1;
    int m_blockTexture = -1;
    int m_font = -1;

    int m_currentType = 0;

    int m_blockX = 3;
    int m_blockY = 0;

    
    int m_currentShape[4][4] = {};

    int m_board[20][10] = {};

    long long m_lastFallTime = 0;
    int m_fallInterval = 500;

    int m_score = 0;

    bool m_gameOver = false;

private:
    void CreateBlock();

    void DrawRect(int x, int y, int width, int height);
    void DrawBoardBorder();
    void DrawBlock(int type, int x, int y);
    void DrawCurrentBlock();
    void DrawBoard();

    bool CanMove(int moveX, int moveY);

    
    bool CanPlace(
        const int shape[4][4],
        int x,
        int y
    );

    void RotateBlock();

    void LockBlock();

    int ClearLines();
};
