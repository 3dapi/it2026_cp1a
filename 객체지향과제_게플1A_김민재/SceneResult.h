#pragma once

class SceneResult
{
public:
    int Init();
    int Update();
    int Render();
    int Destroy();

    void SetResult(bool clear);

protected:
    int m_font = -1;

    bool m_clear = false;
    int m_select = 0;
};