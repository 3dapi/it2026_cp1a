#pragma once

class SceneBegin
{
public:
    int Init();
    int Update();
    int Render();
    int Destroy();

protected:
    int m_txBG = -1;
    int m_txUI_start = -1;
    int m_txUI_exit = -1;
    int m_txUI_chose = -1;

    int m_select = 0;
};