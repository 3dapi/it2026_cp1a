#include "SceneGameBegin.h"

// Init(): 배경/버튼/사운드 리소스 로드 및 상태 초기화
int SceneGameBegin::Init()
{
    Destroy();

    //배경이미지
    m_txMain = g2_TextureLoad("Texture/Main_BG.png");
    m_txHowTo = g2_TextureLoad("Texture/Img_HowTo.png");

    //버튼 이미지 로드
    m_txBtnStartNormal = g2_TextureLoad("Texture/Btn_Start_Normal.png");
    m_txBtnStartHover = g2_TextureLoad("Texture/Btn_Start_Hover.png");

    m_txBtnHowToNormal = g2_TextureLoad("Texture/Btn_HowTo_Normal.png");
    m_txBtnHowToHover = g2_TextureLoad("Texture/Btn_HowTo_Hover.png");

    m_txBtnExitNormal = g2_TextureLoad("Texture/Btn_Exit_Normal.png");
    m_txBtnExitHover = g2_TextureLoad("Texture/Btn_Exit_Hover.png");

    //사운드 로드
    m_sndBgm = g2_SoundLoad("Sound/BGM_Main.mp3");
    m_sndButtonClick = g2_SoundLoad("Sound/SFX_ButtonClick.mp3");
    m_sndStartClick = g2_SoundLoad("Sound/SFX_StartClick.mp3");

    // 메인 배경음악 반복 재생
    if (m_sndBgm >= 0) g2_SoundPlay(m_sndBgm, true);

    m_showHowTo = false;
    m_prevEnter = false;
    m_prevMouse = false;

    return 0;
}

// Destroy(): 로드한 텍스처/사운드 자원 해제
int SceneGameBegin::Destroy()
{
    if (m_txMain >= 0)
    {
        g2_TextureRelease(m_txMain);
        m_txMain = -1;
    }
    if (m_txHowTo >= 0)
    {
        g2_TextureRelease(m_txHowTo);
        m_txHowTo = -1;
    }

    if (m_txBtnStartNormal >= 0)
    {
        g2_TextureRelease(m_txBtnStartNormal);
        m_txBtnStartNormal = -1;
    }
    if (m_txBtnStartHover >= 0)
    {
        g2_TextureRelease(m_txBtnStartHover);
        m_txBtnStartHover = -1;
    }

    if (m_txBtnHowToNormal >= 0)
    {
        g2_TextureRelease(m_txBtnHowToNormal);
        m_txBtnHowToNormal = -1;
    }
    if (m_txBtnHowToHover >= 0)
    {
        g2_TextureRelease(m_txBtnHowToHover);
        m_txBtnHowToHover = -1;
    }

    if (m_txBtnExitNormal >= 0)
    {
        g2_TextureRelease(m_txBtnExitNormal);
        m_txBtnExitNormal = -1;
    }

    if (m_txBtnExitHover >= 0)
    {
        g2_TextureRelease(m_txBtnExitHover);
        m_txBtnExitHover = -1;
    }
    if (m_sndBgm >= 0)
    {
        g2_SoundStop(m_sndBgm);
        g2_SoundRelease(m_sndBgm);
        m_sndBgm = -1;
    }
    if (m_sndButtonClick >= 0)
    {
        g2_SoundRelease(m_sndButtonClick);
        m_sndButtonClick = -1;
    }
    if (m_sndStartClick >= 0)
    {
        g2_SoundRelease(m_sndStartClick);
        m_sndStartClick = -1;
    }

    return 0;
}

// IsKeyPressed(): 키 눌림 상태 확인
bool SceneGameBegin::IsKeyPressed(int key)
{
    SHORT state = GetAsyncKeyState(key);
    return (state & 0x8000) != 0;
}

// IsMouseClicked(): 이번 프레임에 새로 눌린 마우스 좌클릭 여부
bool SceneGameBegin::IsMouseClicked()
{
    bool currentMouse = IsKeyPressed(VK_LBUTTON);
    bool clicked = currentMouse && !m_prevMouse;
    m_prevMouse = currentMouse;

    return clicked;
}

// Update(): 마우스&키 입력에 따른 버튼 처리
int SceneGameBegin::Update(const KEYCODE* keys)
{
    bool enterPressed = IsKeyPressed(VK_RETURN);
    bool enterDown = enterPressed && !m_prevEnter;
    m_prevEnter = enterPressed;

    // 마우스 좌표 구하기 
    POINT cursorPosition{ 0, 0 };
    GetCursorPos(&cursorPosition);

    HWND foregroundWindow = GetForegroundWindow();
    if (foregroundWindow != nullptr)
    {
        ScreenToClient(foregroundWindow, &cursorPosition);
    }

    m_mouseX = cursorPosition.x;
    m_mouseY = cursorPosition.y;

    bool mouseClicked = IsMouseClicked();

    // 게임 방법 팝업 출력 중 처리
    if (m_showHowTo)
    {
        if (mouseClicked || enterDown || IsKeyPressed(VK_ESCAPE))
        {
            m_showHowTo = false;
        }
        return 0;
    }

    // 버튼 클릭 이벤트
    if (mouseClicked)
    {
        if (m_btnStart.Contains(m_mouseX, m_mouseY))
        {
            if (m_sndBgm >= 0)
                g2_SoundStop(m_sndBgm); // 메인 BGM 정지
            if (m_sndStartClick >= 0)
                g2_SoundPlay(m_sndStartClick);
            return 1; // 게임 시작
        }

        if (m_btnHowTo.Contains(m_mouseX, m_mouseY))
        {
            if (m_sndButtonClick >= 0)
                g2_SoundPlay(m_sndButtonClick);
            m_showHowTo = true;
            return 0;
        }

        if (m_btnExit.Contains(m_mouseX, m_mouseY))
        {
            if (m_sndBgm >= 0)
                g2_SoundStop(m_sndBgm);
            return -1; // 게임 종료
        }
    }

    return 0;
}

// Render(): 배경 및 버튼/팝업 출력
int SceneGameBegin::Render()
{
    g2_DrawAlphaOption(255);

    // 메인 배경 이미지 출력
    if (m_txMain >= 0)
    {
        g2_Draw2D(m_txMain, nullptr);
    }

    // 버튼 텍스처 출력
    if (!m_showHowTo)
    {
        // [게임시작] 버튼
        bool isStartHover = m_btnStart.Contains(m_mouseX, m_mouseY);
        int txStart = isStartHover ? m_txBtnStartHover : m_txBtnStartNormal;
        if (txStart >= 0)
        {
            g2_Draw2D(txStart, nullptr);
        }

        // [게임 방법] 버튼
        bool isHowToHover = m_btnHowTo.Contains(m_mouseX, m_mouseY);
        int txHowTo = isHowToHover ? m_txBtnHowToHover : m_txBtnHowToNormal;
        if (txHowTo >= 0)
        {
            g2_Draw2D(txHowTo, nullptr);
        }

        // [나가기] 버튼
        bool isExitHover = m_btnExit.Contains(m_mouseX, m_mouseY);
        int txExit = isExitHover ? m_txBtnExitHover : m_txBtnExitNormal;
        if (txExit >= 0)
        {
            g2_Draw2D(txExit, nullptr);
        }
    }

    // 게임 방법 팝업창 출력
    if (m_showHowTo && m_txHowTo >= 0)
    {
        g2_Draw2D(m_txHowTo, nullptr);
    }

    return 0;
}
