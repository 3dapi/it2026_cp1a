#include "SceneGameResult.h"

// Init(): 결과 화면 리소스 로드
int SceneGameResult::Init()
{
    m_txPlayerWin = g2_TextureLoad("Texture/Img_Win_Younghee.png");
    m_txPlayerLose = g2_TextureLoad("Texture/Img_Win_Cheolsoo.png");
    m_txBtnReturn = g2_TextureLoad("Texture/Btn_Return.png");
    m_txBtnReturnHover = g2_TextureLoad("Texture/Btn_Return_Hover.png");
    m_sndWinEnding = g2_SoundLoad("Sound/SFX_WinEnding.mp3");
    m_sndLoseEnding = g2_SoundLoad("Sound/SFX_LoseEnding.mp3");

    m_prevLButtonDown = false;

    return 0;
}

// Destroy(): 결과 화면 자원 해제
int SceneGameResult::Destroy()
{
    if (m_txPlayerWin >= 0)
    {
        g2_TextureRelease(m_txPlayerWin);
        m_txPlayerWin = -1;
    }

    if (m_txPlayerLose >= 0)
    {
        g2_TextureRelease(m_txPlayerLose);
        m_txPlayerLose = -1;
    }

    if (m_txBtnReturn >= 0)
    {
        g2_TextureRelease(m_txBtnReturn);
        m_txBtnReturn = -1;
    }
    if (m_txBtnReturnHover >= 0)
    {
        g2_TextureRelease(m_txBtnReturnHover);
        m_txBtnReturnHover = -1;
    }

    if (m_sndWinEnding >= 0)
    {
        g2_SoundRelease(m_sndWinEnding);
        m_sndWinEnding = -1;
    }

    if (m_sndLoseEnding >= 0)
    {
        g2_SoundRelease(m_sndLoseEnding);
        m_sndLoseEnding = -1;
    }

    return 0;
}

// IsKeyPressed(): 키 눌림 확인
bool SceneGameResult::IsKeyPressed(int key)
{
    SHORT state = GetAsyncKeyState(key);
    return (state & 0x8000) != 0;
}

// Update(): 버튼/키 입력 처리 (진입 1초 후부터 활성)
int SceneGameResult::Update(const KEYCODE* keys)
{
    // 마우스 좌표/클릭 갱신
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(GetActiveWindow(), &pt);
    m_mousePos = pt;

    bool isLDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    bool isLClicked = isLDown && !m_prevLButtonDown;
    m_prevLButtonDown = isLDown;

    // 결과 화면 진입 후 1초가 지났을 때만 버튼 클릭 허용
    bool oneSecondPassed = (GetTickCount64() - m_resultStartTime >= 1000);

    // 1초 뒤: 돌아가기 버튼 클릭 -> 메인 화면으로
    if (oneSecondPassed && isLClicked && PtInRect(&m_rtBtnReturn, m_mousePos))
    {
        return 0; // SCENE_BEGIN
    }

    // 키보드도 지원 (Enter: 메인으로, ESC: 게임 종료)
    if (IsKeyPressed(VK_RETURN) && oneSecondPassed)
    {
        return 0;
    }

    if (IsKeyPressed(VK_ESCAPE))
    {
        return -1; // 게임 종료
    }

    return 2; // 결과 화면 유지
}

// Render(): 승패 결과 및 돌아가기 버튼 출력
int SceneGameResult::Render()
{
    int textureKey = -1;

    if (m_playerWin)
    {
        textureKey = m_txPlayerWin;
    }
    else
    {
        textureKey = m_txPlayerLose;
    }

    RECT rFullScreen = { 0, 0, 800, 600 };

    if (textureKey >= 0)
    {
        g2_DrawAlphaOption(255);
        g2_Draw2D(textureKey, &rFullScreen);
    }

    // 결과 화면 진입 1초 뒤부터 돌아가기 버튼 표시 (마우스 올리면 Hover)
    if (GetTickCount64() - m_resultStartTime >= 1000)
    {
        bool isHover = PtInRect(&m_rtBtnReturn, m_mousePos) != FALSE;
        int btnTx = isHover ? m_txBtnReturnHover : m_txBtnReturn;

        if (btnTx >= 0)
        {
            g2_Draw2D(btnTx, &rFullScreen);
        }
    }

    return 0;
}

// SetPlayerWin(): 승패 저장 후 진입 시각/엔딩 사운드 처리
void SceneGameResult::SetPlayerWin(bool playerWin)
{
    m_playerWin = playerWin;

    // 결과 화면 진입 시각 기록 (버튼 1초 딜레이용)
    m_resultStartTime = GetTickCount64();

    // 결과 화면 진입과 동시에 엔딩 사운드
    if (playerWin && m_sndWinEnding >= 0)        g2_SoundPlay(m_sndWinEnding);
    else if (!playerWin && m_sndLoseEnding >= 0) g2_SoundPlay(m_sndLoseEnding);
}
