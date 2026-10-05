#include "ScenePlay.h"
#include <cstdlib>
#include <ctime>
#include <stdio.h>


enum BLOCK_TYPE
{
    BLOCK_I = 0,
    BLOCK_O,
    BLOCK_T,
    BLOCK_S,
    BLOCK_Z,
    BLOCK_J,
    BLOCK_L
};



const int CELL_SIZE = 25;

// 테트리스 보드 시작 위치
const int BOARD_X = 275;
const int BOARD_Y = 50;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;


const int BLOCK_SHAPE[7][4][4] =
{
    // I
    {
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },

    // O
    {
        { 0, 1, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },

    // T
    {
        { 0, 1, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },

    // S
    {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },

    // Z
    {
        { 1, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },

    // J
    {
        { 1, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },

    // L
    {
        { 0, 0, 1, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    }
};



const RECT BLOCK_RECT[7] =
{
    {   33, 210,  319, 498 },   
    {  336, 210,  622, 498 },   
    {  639, 210,  926, 498 },   
    {  943, 210, 1230, 498 },   
    { 1247, 210, 1534, 498 },   
    { 1552, 210, 1839, 498 },   
    { 1856, 210, 2142, 498 }    
};


int ScenePlay::Init()
{
    m_blockTexture =
        g2_TextureLoad("resouce/blocks.png");

    m_lineTexture =
        g2_TextureLoad("resouce/white.png");

    m_font = g2_FontCreate("Arial", 24);

    srand((unsigned int)time(nullptr));

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            m_board[y][x] = 0;
        }
    }

    m_score = 0;
    m_gameOver = false;

    CreateBlock();

    m_lastFallTime = g2_TimeGetTime();

    return 0;
}

void ScenePlay::DrawRect(
    int x,
    int y,
    int width,
    int height)
{
    float texWidth =
        (float)g2_TextureWidth(m_lineTexture);

    float texHeight =
        (float)g2_TextureHeight(m_lineTexture);

    VEC2 pos =
    {
        (float)x,
        (float)y
    };

    VEC2 scale =
    {
        width / texWidth,
        height / texHeight
    };

    g2_Draw2D(
        m_lineTexture,
        nullptr,
        &pos,
        &scale
    );
}

void ScenePlay::CreateBlock()
{
    m_currentType = rand() % 7;

    m_blockX = 3;
    m_blockY = 0;

    
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            m_currentShape[row][col]
                = BLOCK_SHAPE[m_currentType][row][col];
        }
    }
}

void ScenePlay::DrawBoardBorder()
{
    const int width =
        BOARD_WIDTH * CELL_SIZE;

    const int height =
        BOARD_HEIGHT * CELL_SIZE;

    const int thickness = 3;

    // 위
    DrawRect(
        BOARD_X - thickness,
        BOARD_Y - thickness,
        width + thickness * 2,
        thickness
    );

    // 아래
    DrawRect(
        BOARD_X - thickness,
        BOARD_Y + height,
        width + thickness * 2,
        thickness
    );

    // 왼쪽
    DrawRect(
        BOARD_X - thickness,
        BOARD_Y,
        thickness,
        height
    );

    // 오른쪽
    DrawRect(
        BOARD_X + width,
        BOARD_Y,
        thickness,
        height
    );
}

void ScenePlay::DrawBlock(int type, int x, int y)
{
    RECT src = BLOCK_RECT[type];

    float imageWidth =
        (float)(src.right - src.left);

    float imageHeight =
        (float)(src.bottom - src.top);


    VEC2 pos =
    {
        (float)x,
        (float)y
    };


    VEC2 scale =
    {
        CELL_SIZE / imageWidth,
        CELL_SIZE / imageHeight
    };


    g2_Draw2D(
        m_blockTexture,
        &src,
        &pos,
        &scale
    );
}


void ScenePlay::DrawCurrentBlock()
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (m_currentShape[row][col] == 1)
            {
                int screenX =
                    BOARD_X +
                    (m_blockX + col) * CELL_SIZE;

                int screenY =
                    BOARD_Y +
                    (m_blockY + row) * CELL_SIZE;


                DrawBlock(
                    m_currentType,
                    screenX,
                    screenY
                );
            }
        }
    }
}

bool ScenePlay::CanMove(int moveX, int moveY)
{
    return CanPlace(
        m_currentShape,
        m_blockX + moveX,
        m_blockY + moveY
    );
}

bool ScenePlay::CanPlace(
    const int shape[4][4],
    int x,
    int y)
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (shape[row][col] == 0)
                continue;

            int boardX = x + col;
            int boardY = y + row;

            
            if (boardX < 0 ||
                boardX >= BOARD_WIDTH)
            {
                return false;
            }

            
            if (boardY >= BOARD_HEIGHT)
            {
                return false;
            }

            
            if (boardY >= 0 &&
                m_board[boardY][boardX] != 0)
            {
                return false;
            }
        }
    }

    return true;
}

void ScenePlay::LockBlock()
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (m_currentShape[row][col] == 0)
                continue;

            int boardX =
                m_blockX + col;

            int boardY =
                m_blockY + row;

            if (boardY >= 0 &&
                boardY < BOARD_HEIGHT &&
                boardX >= 0 &&
                boardX < BOARD_WIDTH)
            {
                m_board[boardY][boardX]
                    = m_currentType + 1;
            }
        }
    }
}

void ScenePlay::RotateBlock()
{
    int rotated[4][4] = {};

    
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            rotated[col][3 - row]
                = m_currentShape[row][col];
        }
    }


    

    int minRow = 4;
    int minCol = 4;

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (rotated[row][col] == 1)
            {
                if (row < minRow)
                    minRow = row;

                if (col < minCol)
                    minCol = col;
            }
        }
    }


    int normalized[4][4] = {};

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (rotated[row][col] == 1)
            {
                normalized
                    [row - minRow]
                    [col - minCol] = 1;
            }
        }
    }


    
    if (CanPlace(
        normalized,
        m_blockX,
        m_blockY))
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                m_currentShape[row][col]
                    = normalized[row][col];
            }
        }
    }
}

void ScenePlay::DrawBoard()
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            if (m_board[row][col] != 0)
            {
                int type =
                    m_board[row][col] - 1;

                int screenX =
                    BOARD_X +
                    col * CELL_SIZE;

                int screenY =
                    BOARD_Y +
                    row * CELL_SIZE;

                DrawBlock(
                    type,
                    screenX,
                    screenY
                );
            }
        }
    }
}

int ScenePlay::ClearLines()
{
    int clearCount = 0;

    
    for (int row = BOARD_HEIGHT - 1;
        row >= 0;
        row--)
    {
        bool full = true;

        
        for (int col = 0;
            col < BOARD_WIDTH;
            col++)
        {
            if (m_board[row][col] == 0)
            {
                full = false;
                break;
            }
        }

        if (full)
        {
            clearCount++;

            
            for (int y = row; y > 0; y--)
            {
                for (int x = 0;
                    x < BOARD_WIDTH;
                    x++)
                {
                    m_board[y][x] =
                        m_board[y - 1][x];
                }
            }

            
            for (int x = 0;
                x < BOARD_WIDTH;
                x++)
            {
                m_board[0][x] = 0;
            }

            
            row++;
        }
    }

    return clearCount;
}


int ScenePlay::Update()
{
    if (m_gameOver)
        return 0;

    const KEYCODE* key =
        g2_GetKeyboard();


    // 왼쪽
    if (key[VK_LEFT] == EINPUT_DOWN)
    {
        if (CanMove(-1, 0))
        {
            m_blockX--;
        }
    }


    // 오른쪽
    if (key[VK_RIGHT] == EINPUT_DOWN)
    {
        if (CanMove(1, 0))
        {
            m_blockX++;
        }
    }


    // 아래
    if (key[VK_DOWN] == EINPUT_DOWN)
    {
        if (CanMove(0, 1))
        {
            m_blockY++;
        }
    }


    // 위 방향키 = 회전
    if (key[VK_UP] == EINPUT_DOWN)
    {
        RotateBlock();
    }


    
    long long currentTime =
        g2_TimeGetTime();

    if (currentTime - m_lastFallTime
        >= m_fallInterval)
    {
        if (CanMove(0, 1))
        {
            m_blockY++;
        }
        else
        {
            LockBlock();

            int clearCount =
                ClearLines();

            switch (clearCount)
            {
            case 1:
                m_score += 100;
                break;

            case 2:
                m_score += 300;
                break;

            case 3:
                m_score += 500;
                break;

            case 4:
                m_score += 800;
                break;
            }

            CreateBlock();

            if (!CanMove(0, 0))
            {
                m_gameOver = true;
            }
        }

        m_lastFallTime = currentTime;
    }

    return 0;
}


int ScenePlay::Render()
{
    DrawBoardBorder();

    DrawBoard();

    if (!m_gameOver)
    {
        DrawCurrentBlock();
    }

    // SCORE
    RECT scoreRect =
    {
        560,
        80,
        780,
        120
    };

    g2_FontDrawText(
        m_font,
        scoreRect,
        0xFFFFFFFF,
        "SCORE : %d",
        m_score
    );

    return 0;
}


int ScenePlay::Destroy()
{
    if (m_blockTexture != -1)
    {
        g2_TextureRelease(m_blockTexture);
        m_blockTexture = -1;
    }

    return 0;
}