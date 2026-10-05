#include "SceneResult.h"
#include "glc2d.h"
#include "ScenePlay.h"
#include "CApplication.h"

#define GAME_RESTART_BUTTON_RECT mouseX >= 420 && mouseX <=585 && mouseY >= 420 && mouseY <= 470
#define EXIT_BUTTON_RECT mouseX >= 445 && mouseX <= 555 && mouseY >= 490 && mouseY <= 540

extern CApplication g_App;

SceneResult::SceneResult(bool isClear, int remainSecond, int killCount, int curHp)
	: m_IsClear(isClear),
	m_RemainSecond(remainSecond),
	m_KillCount(killCount),
	m_CurHp(curHp)
{
}

int SceneResult::Init()
{
	m_BackGroundTexture = g2_TextureLoad("Texture/TitleBackGround.png");



	return 0;
}

int SceneResult::Update()
{
	int mouseX = g2_GetMouseX();
	int mouseY = g2_GetMouseY();

	if (g2_GetMouseEvent(0) == EINPUT_DOWN) // 마우스 왼쪽 버튼 클릭
	{
		if (GAME_RESTART_BUTTON_RECT) // "GAME START" 버튼 영역
		{
			g_App.ChangeScene(new ScenePlay()); // 게임 플레이 씬으로 전환
		}
		else if (EXIT_BUTTON_RECT) // "EXIT" 버튼 영역
		{
			PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0); // 게임 종료
		}
	}
	return 0;
}

int SceneResult::Render(CApplication& application)
{
	const GameResource& Resource = application.GetResource();

	g2_Draw2D(m_BackGroundTexture, {});

    char resultText[32];
    char timeText[32];
    char killText[32];
    char hpText[32];

    if (m_IsClear)
        g2_FontDrawText(
            Resource.fontTitle,
            { 370, 160, 800, 260 },
            0xFFFFE08A,
            "CLEAR"
        );
    else
        g2_FontDrawText(
            Resource.fontTitle,
            { 420, 160, 800, 260 },
            0xFFFFE08A,
            "FAIL"
        );

    sprintf_s(timeText, "남은 시간 : %d", m_RemainSecond);
    sprintf_s(killText, "처리한 적 : %d", m_KillCount);
    sprintf_s(hpText, "남은 체력 : %d", m_CurHp);

    // 결과
    

    // 남은 시간
    g2_FontDrawText(
        Resource.fontNormal,
        { 420, 290, 800, 310 },
        0xffffffff,
        timeText
    );

    // 처리한 적
    g2_FontDrawText(
        Resource.fontNormal,
        { 420, 320, 800, 340 },
        0xffffffff,
        killText
    );

    // 남은 체력
    g2_FontDrawText(
        Resource.fontNormal,
        { 420, 350, 800, 370 },
        0xffffffff,
        hpText
    );

    // RETRY
    g2_FontDrawText(
        Resource.fontMenu,
        { 420, 420, 800, 470 },
        0xffffffff,
        "RETRY"
    );

    // EXIT
    g2_FontDrawText(
        Resource.fontMenu,
        { 445, 490, 800, 540 },
        0xffffffff,
        "EXIT"
    );

	return 0;
}

int SceneResult::Destroy()
{
	if (m_BackGroundTexture >= 0)
	{
		g2_TextureRelease(m_BackGroundTexture);
		m_BackGroundTexture = -1;
	}

	return 0;
}
