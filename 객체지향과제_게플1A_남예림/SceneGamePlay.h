#pragma once

#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "glc2d.h"
#include "Piece.h"

// 가위바위보 선택 값
enum class RPSChoice
{
    NONE = -1,
    SCISSORS = 0, // 가위
    ROCK = 1,     // 바위
    PAPER = 2     // 보
};

class SceneGamePlay
{
public:
    int Init();
    int Destroy();
    int Update(const KEYCODE* keys = nullptr);
    int Render();

    void ResetGame();

    // 결과 화면에 승패 전달용 (10번 도달 = 플레이어 승)
    bool GetPlayerWin() const
    {
        return m_younghee.GetPosition() >= 10;
    }
    void StartBgm()
    {
        if (m_sndBgm >= 0)
            g2_SoundPlay(m_sndBgm, true);
    }

private:
    bool IsKeyPressed(int key);
    void StartTurn(RPSChoice playerChoice);   // 카운트 시작
    void FinishTurn();                        // 승패 판정 후 말 이동

private:
    int m_txBackground = -1;

    // 가위, 바위, 보 기본 버튼
    int m_txScissors = -1;
    int m_txRock = -1;
    int m_txPaper = -1;

    // 가위, 바위, 보 눌림버튼
    int m_txScissorsHover = -1;
    int m_txRockHover = -1;
    int m_txPaperHover = -1;

    // 마우스 클릭 판정
    POINT m_mousePos{ 0, 0 };
    bool m_prevLButtonDown = false;

    RECT m_rtScissors;
    RECT m_rtRock;
    RECT m_rtPaper;

    // 카운트 숫자 이미지
    int m_txCount1 = -1;
    int m_txCount2 = -1;
    int m_txCount3 = -1;

    int m_aiChoice = -1;       // 컴퓨터가 뽑은 카드 (0: 가위, 1: 바위, 2: 보)
    int m_txComScissors = -1;
    int m_txComRock = -1;
    int m_txComPaper = -1;

    // 승패 결과 프로필 이미지 (결과 연출용)
    int m_txYoungheeWin = -1;
    int m_txCheolsooWin = -1;

    // 게임 종료 연출용
    int m_txWin = -1;
    int m_txLose = -1;
    int m_txBtnEnding = -1;
    int m_txBtnEndingHover = -1;

    // 말 이미지
    int m_txPiece = -1;

    Piece m_younghee;

    // 사운드
    int m_sndBgm = -1;       // BGM_InGame
    int m_sndCount = -1;     // SFX_Count
    int m_sndMove = -1;      // SFX_Move
    int m_sndWin = -1;       // SFX_Win
    int m_sndLose = -1;      // SFX_Lose

    int m_prevShownCount = -5;   // 카운트 사운드 중복 재생 방지용

    // 게임 진행 상태
    bool m_isEvaluating = false;
    bool m_isGameOver = false;

    int m_countdown = 0;

    ULONGLONG m_turnStartTime = 0;      // 턴 시작 시각
    ULONGLONG m_gameOverStartTime = 0;  // 게임 종료 시각

    int m_turnWinner = 0;   // 0: 무승부, 1: 영희 승, 2: 철수 승
    bool m_moved = false;   // 이번 턴 말 이동 여부

    RPSChoice m_playerChoice = RPSChoice::NONE;

    // 0번(왼쪽 아웃) ~ 10번(오른쪽 아웃) 돌 사이 X 좌표
    const int m_stoneX[11] = { 40, 110, 190, 260, 335, 405, 480, 550, 620, 690, 760 };
    const int m_stoneY = 390;
};
