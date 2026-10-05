#pragma once

#include <Windows.h>
#include "glc2d.h"

class SceneGameResult
{
public:
    int Init();
    int Destroy();
    int Update(const KEYCODE* keys = nullptr);
    int Render();

    void SetPlayerWin(bool playerWin);

private:
    bool IsKeyPressed(int key);

private:
    // 승패 결과 화면
    int m_txPlayerWin = -1;
    int m_txPlayerLose = -1;

    // 돌아가기 버튼
    int m_txBtnReturn = -1;
    int m_txBtnReturnHover = -1;

    // 돌아가기 버튼 클릭 영역
    RECT m_rtBtnReturn{ 300, 508, 520, 558 };

    // 사운드
    int m_sndWinEnding = -1;
    int m_sndLoseEnding = -1;

    bool m_playerWin = false;

    ULONGLONG m_resultStartTime = 0;   // 결과 화면 진입 시각
    POINT m_mousePos{ 0, 0 };
    bool m_prevLButtonDown = false;
};
