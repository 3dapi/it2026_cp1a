#include "SceneGamePlay.h"
#include <ctime>
#include <cstdlib>

// Init(): 게임 리소스 로드 및 초기화
int SceneGamePlay::Init()
{
    srand((unsigned int)time(nullptr));

    // 기존 텍스처 정리
    Destroy();

    // 배경
    m_txBackground = g2_TextureLoad("Texture/InGame_BG.png");

    // 가위바위보 기본 버튼
    m_txScissors = g2_TextureLoad("Texture/Btn_Scissors.png");
    m_txRock = g2_TextureLoad("Texture/Btn_Rock.png");
    m_txPaper = g2_TextureLoad("Texture/Btn_Paper.png");

    // Hover 버튼
    m_txScissorsHover = g2_TextureLoad("Texture/Btn_Scissors_Hover.png");
    m_txRockHover = g2_TextureLoad("Texture/Btn_Rock_Hover.png");
    m_txPaperHover = g2_TextureLoad("Texture/Btn_Paper_Hover.png");

    // 컴퓨터 카드
    m_txComScissors = g2_TextureLoad("Texture/Com_Scissors.png");
    m_txComRock = g2_TextureLoad("Texture/Com_Rock.png");
    m_txComPaper = g2_TextureLoad("Texture/Com_Paper.png");

    // 카운트 숫자
    m_txCount1 = g2_TextureLoad("Texture/Count_1.png");
    m_txCount2 = g2_TextureLoad("Texture/Count_2.png");
    m_txCount3 = g2_TextureLoad("Texture/Count_3.png");

    // 턴 승패 프로필
    m_txYoungheeWin = g2_TextureLoad("Texture/Profile_YoungheeWin.png");
    m_txCheolsooWin = g2_TextureLoad("Texture/Profile_CheolsooWin.png");

    // 게임 종료 화면+엔딩 버튼
    m_txWin = g2_TextureLoad("Texture/WIN.png");
    m_txLose = g2_TextureLoad("Texture/Lose.png");
    m_txBtnEnding = g2_TextureLoad("Texture/Btn_Ending.png");
    m_txBtnEndingHover = g2_TextureLoad("Texture/Btn_Ending_Hover.png");

    // 말
    m_txPiece = g2_TextureLoad("Texture/Piece.png");

    // 사운드 로드
    m_sndBgm = g2_SoundLoad("Sound/BGM_InGame.mp3");
    m_sndCount = g2_SoundLoad("Sound/SFX_Count.mp3");
    m_sndMove = g2_SoundLoad("Sound/SFX_Move.mp3");
    m_sndWin = g2_SoundLoad("Sound/SFX_Win.mp3");
    m_sndLose = g2_SoundLoad("Sound/SFX_Lose.mp3");

    m_rtScissors = { 20, 470, 260, 570 };
    m_rtRock = { 270, 470, 510, 570 };
    m_rtPaper = { 520, 470, 760, 570 };

    m_prevLButtonDown = false;

    ResetGame();

    return 0;
}

// Destroy(): 텍스처/사운드 해제
int SceneGamePlay::Destroy()
{
    if (m_txBackground >= 0)
    {
        g2_TextureRelease(m_txBackground);
        m_txBackground = -1;
    }
    if (m_txScissors >= 0)
    {
        g2_TextureRelease(m_txScissors);
        m_txScissors = -1;
    }
    if (m_txRock >= 0)
    {
        g2_TextureRelease(m_txRock);
        m_txRock = -1;
    }
    if (m_txPaper >= 0)
    {
        g2_TextureRelease(m_txPaper);
        m_txPaper = -1;
    }
    if (m_txScissorsHover >= 0)
    {
        g2_TextureRelease(m_txScissorsHover);
        m_txScissorsHover = -1;
    }
    if (m_txRockHover >= 0)
    {
        g2_TextureRelease(m_txRockHover);
        m_txRockHover = -1;
    }
    if (m_txPaperHover >= 0)
    {
        g2_TextureRelease(m_txPaperHover);
        m_txPaperHover = -1;
    }
    if (m_txComScissors >= 0)
    {
        g2_TextureRelease(m_txComScissors);
        m_txComScissors = -1;
    }
    if (m_txComRock >= 0)
    {
        g2_TextureRelease(m_txComRock);
        m_txComRock = -1;
    }
    if (m_txComPaper >= 0)
    {
        g2_TextureRelease(m_txComPaper);
        m_txComPaper = -1;
    }
    if (m_txCount1 >= 0)
    {
        g2_TextureRelease(m_txCount1);
        m_txCount1 = -1;
    }
    if (m_txCount2 >= 0)
    {
        g2_TextureRelease(m_txCount2);
        m_txCount2 = -1;
    }
    if (m_txCount3 >= 0)
    {
        g2_TextureRelease(m_txCount3);
        m_txCount3 = -1;
    }
    if (m_txYoungheeWin >= 0)
    {
        g2_TextureRelease(m_txYoungheeWin);
        m_txYoungheeWin = -1;
    }
    if (m_txCheolsooWin >= 0)
    {
        g2_TextureRelease(m_txCheolsooWin);
        m_txCheolsooWin = -1;
    }
    if (m_txWin >= 0)
    {
        g2_TextureRelease(m_txWin);
        m_txWin = -1;
    }
    if (m_txLose >= 0)
    {
        g2_TextureRelease(m_txLose);
        m_txLose = -1;
    }
    if (m_txBtnEnding >= 0)
    {
        g2_TextureRelease(m_txBtnEnding);
        m_txBtnEnding = -1;
    }
    if (m_txBtnEndingHover >= 0)
    {
        g2_TextureRelease(m_txBtnEndingHover);
        m_txBtnEndingHover = -1;
    }
    if (m_txPiece >= 0)
    {
        g2_TextureRelease(m_txPiece);
        m_txPiece = -1;
    }
    if (m_sndBgm >= 0)
    {
        g2_SoundStop(m_sndBgm);
        g2_SoundRelease(m_sndBgm);
        m_sndBgm = -1;
    }
    if (m_sndCount >= 0)
    {
        g2_SoundRelease(m_sndCount);
        m_sndCount = -1;
    }
    if (m_sndMove >= 0)
    {
        g2_SoundRelease(m_sndMove);
        m_sndMove = -1;
    }
    if (m_sndWin >= 0)
    {
        g2_SoundRelease(m_sndWin);
        m_sndWin = -1;
    }
    if (m_sndLose >= 0)
    {
        g2_SoundRelease(m_sndLose);
        m_sndLose = -1;
    }

    return 0;
}

// ResetGame(): 게임 시작 상태로 리셋
void SceneGamePlay::ResetGame()
{
    m_younghee.Init(5); // 중앙에서 시작

    m_prevShownCount = -5;
    m_isEvaluating = false;
    m_isGameOver = false;

    m_countdown = 0;
    m_aiChoice = -1;

    m_playerChoice = RPSChoice::NONE;

    m_turnStartTime = 0;
    m_gameOverStartTime = 0;
    m_turnWinner = 0;
    m_moved = false;
}

// IsKeyPressed(): 키 눌림 확인
bool SceneGamePlay::IsKeyPressed(int key)
{
    SHORT state = GetAsyncKeyState(key);
    return (state & 0x8000) != 0;
}

// StartTurn(): 카운트다운 시작
void SceneGamePlay::StartTurn(RPSChoice playerChoice)
{
    if (m_isEvaluating || m_isGameOver) return;

    m_playerChoice = playerChoice;
    m_isEvaluating = true;
    m_countdown = 3;
    m_aiChoice = -1;

    m_turnWinner = 0;
    m_moved = false;

    m_turnStartTime = GetTickCount64();
    m_prevShownCount = -5;
}

// FinishTurn(): 승패 판정 후 말 이동 +프로필 표시 구간에서 딱 한 번 호출
void SceneGamePlay::FinishTurn()
{
    int pChoice = static_cast<int>(m_playerChoice);

    if (pChoice == m_aiChoice)
    {
        m_turnWinner = 0; // 무승부
    }
    else if ((pChoice == 0 && m_aiChoice == 2) ||
        (pChoice == 1 && m_aiChoice == 0) ||
        (pChoice == 2 && m_aiChoice == 1))
    {
        m_turnWinner = 1;       // 플레이어(영희) 승 -> 오른쪽
        m_younghee.Move(1);
    }
    else
    {
        m_turnWinner = 2;       // 컴퓨터(철수) 승 -> 왼쪽
        m_younghee.Move(-1);
    }

    // 양쪽 끝 도달 시 게임 오버
    int curPos = m_younghee.GetPosition();
    if (curPos <= 0 || curPos >= 10)
    {
        m_isGameOver = true;
        m_gameOverStartTime = GetTickCount64(); // 종료 연출 기준 시각
    }

    // 턴 결과 사운드
    if (m_turnWinner == 1)
    {
        if (m_sndWin >= 0) g2_SoundPlay(m_sndWin);
        if (m_sndMove >= 0) g2_SoundPlay(m_sndMove);
    }
    else if (m_turnWinner == 2)
    {
        if (m_sndLose >= 0) g2_SoundPlay(m_sndLose);
        if (m_sndMove >= 0) g2_SoundPlay(m_sndMove);
    }
}

// Update(): 입력 및 실시간 타임라인 처리
int SceneGamePlay::Update(const KEYCODE* keys)
{
    if (IsKeyPressed(VK_ESCAPE))
    {
        // 메인 화면으로 돌아가기 전에 인게임 BGM을 정지해야 메인 BGM과 소리가 겹치지 않d음
        if (m_sndBgm >= 0) g2_SoundStop(m_sndBgm);
        return 0; // 메인 화면으로
    }

    // 마우스 좌표/클릭 갱신
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(GetActiveWindow(), &pt);
    m_mousePos = pt;

    bool isLDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    bool isLClicked = isLDown && !m_prevLButtonDown;
    m_prevLButtonDown = isLDown;

    // 게임 오버 상태: 1초 뒤 아무 곳이나 클릭하면 결과씬으로
    if (m_isGameOver)
    {
        if (GetTickCount64() - m_gameOverStartTime >= 1000)
        {
            if (isLClicked)
            {
                if (m_sndBgm >= 0) g2_SoundStop(m_sndBgm);   // 인게임 BGM 정지
                return 2; // SCENE_RESULT
            }
        }
        return 1;
    }

    // 평소: 가위바위보 입력 받기
    if (!m_isEvaluating)
    {
        if (IsKeyPressed('1') || (isLClicked && PtInRect(&m_rtScissors, m_mousePos)))
            StartTurn(RPSChoice::SCISSORS);
        else if (IsKeyPressed('2') || (isLClicked && PtInRect(&m_rtRock, m_mousePos)))
            StartTurn(RPSChoice::ROCK);
        else if (IsKeyPressed('3') || (isLClicked && PtInRect(&m_rtPaper, m_mousePos)))
            StartTurn(RPSChoice::PAPER);
    }
    else
    {
        // 실제 경과 시간 기준 타임라인  --> 이렇게 해야 컴퓨터 사양(?) 상관없이 기준 시간 내에 작동 됨
        ULONGLONG elapsed = GetTickCount64() - m_turnStartTime;

        if (elapsed < 1000)       m_countdown = 3;
        else if (elapsed < 2000)  m_countdown = 2;
        else if (elapsed < 3000)  m_countdown = 1;
        else if (elapsed < 4200)  // 3.0~4.2초: 컴퓨터 카드 공개
        {
            if (m_aiChoice < 0)
            {
                m_countdown = 0;
                m_aiChoice = rand() % 3;
            }
        }
        else if (elapsed < 5400)  // 4.2~5.4초: 승자 프로필 + 말 이동
        {
            m_countdown = -2;

            if (!m_moved)
            {
                m_moved = true;
                FinishTurn();
            }
        }
        else // 턴 종료
        {
            m_isEvaluating = false;
        }

        // 숫자가 바뀐 순간에만 카운트 사운드 재생 (3 -> 2 -> 1)
        if (m_countdown != m_prevShownCount)
        {
            m_prevShownCount = m_countdown;

            if (m_countdown >= 1 && m_countdown <= 3 && m_sndCount >= 0)
            {
                g2_SoundPlay(m_sndCount);
            }
        }
    }

    return 1;
}

// Render(): 화면 출력
int SceneGamePlay::Render()
{
    g2_DrawAlphaOption(255);
    RECT rFullScreen = { 0, 0, 800, 600 };

    // 배경
    if (m_txBackground >= 0)
    {
        g2_Draw2D(m_txBackground, &rFullScreen);
    }

    // 가위/바위/보 버튼
    bool isScissorsHover = PtInRect(&m_rtScissors, m_mousePos) || IsKeyPressed('1');
    bool isRockHover = PtInRect(&m_rtRock, m_mousePos) || IsKeyPressed('2');
    bool isPaperHover = PtInRect(&m_rtPaper, m_mousePos) || IsKeyPressed('3');

    if (isScissorsHover && m_txScissorsHover >= 0)
        g2_Draw2D(m_txScissorsHover, &rFullScreen);
    else if (m_txScissors >= 0)
        g2_Draw2D(m_txScissors, &rFullScreen);

    if (isRockHover && m_txRockHover >= 0)
        g2_Draw2D(m_txRockHover, &rFullScreen);
    else if (m_txRock >= 0)
        g2_Draw2D(m_txRock, &rFullScreen);

    if (isPaperHover && m_txPaperHover >= 0)
        g2_Draw2D(m_txPaperHover, &rFullScreen);
    else if (m_txPaper >= 0)
        g2_Draw2D(m_txPaper, &rFullScreen);

    // 카운트다운 / 컴퓨터 카드 / 승자 프로필
    if (m_isEvaluating)
    {
        if (m_countdown == 3 && m_txCount3 >= 0)
            g2_Draw2D(m_txCount3, &rFullScreen);
        else if (m_countdown == 2 && m_txCount2 >= 0)
            g2_Draw2D(m_txCount2, &rFullScreen);
        else if (m_countdown == 1 && m_txCount1 >= 0)
            g2_Draw2D(m_txCount1, &rFullScreen);

        else if (m_countdown == 0 && m_aiChoice >= 0)
        {
            if (m_aiChoice == 0 && m_txComScissors >= 0)
                g2_Draw2D(m_txComScissors, &rFullScreen);
            else if (m_aiChoice == 1 && m_txComRock >= 0)
                g2_Draw2D(m_txComRock, &rFullScreen);
            else if (m_aiChoice == 2 && m_txComPaper >= 0)
                g2_Draw2D(m_txComPaper, &rFullScreen);
        }
        else if (m_countdown == -2)
        {
            if (m_turnWinner == 1 && m_txYoungheeWin >= 0)
                g2_Draw2D(m_txYoungheeWin, &rFullScreen);
            else if (m_turnWinner == 2 && m_txCheolsooWin >= 0)
                g2_Draw2D(m_txCheolsooWin, &rFullScreen);
        }
    }

    // 말은 전체화면 이미지에 가려지지 않도록 나중에
    if (m_txPiece >= 0)
    {
        int posIndex = m_younghee.GetPosition();

        if (posIndex < 0 || posIndex > 10)
        {
            posIndex = 5;
        }

        VEC2 piecePos = { (float)(*(m_stoneX + posIndex) - 80), (float)(m_stoneY - 48) };
        g2_Draw2D(m_txPiece, nullptr, &piecePos);
    }

    // 게임 종료 화면
    if (m_isGameOver)
    {
        int endTx = GetPlayerWin() ? m_txWin : m_txLose;
        if (endTx >= 0)
        {
            g2_Draw2D(endTx, &rFullScreen);
        }

        // 1초 뒤부터 엔딩 버튼 표시
        if (GetTickCount64() - m_gameOverStartTime >= 1000)
        {
            if (m_txBtnEnding >= 0)
            {
                g2_Draw2D(m_txBtnEnding, &rFullScreen);
            }
        }
    }
    return 0;
}
