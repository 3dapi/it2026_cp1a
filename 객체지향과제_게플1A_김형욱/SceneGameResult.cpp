#include "SceneGameresult.h"
#include "glc2d.h"
#include "CApplication.h"

extern CApplication g_app;

int SceneGameResult::Init()
{
	// 폰트 생성
	m_fontTitle = g2_FontCreate("Arial", 60, 0);
	m_fontMenu = g2_FontCreate("Arial", 36, 0);

	return 0;
}

int SceneGameResult::Destroy()
{
	return 0;
}

int SceneGameResult::Update()
{
	int mouseX = g2_GetMouseX();
	int mouseY = g2_GetMouseY();


	if (g2_GetMouseEvent(0) == EINPUT_DOWN)
	{
		// RESTART 영역
		if (mouseX >= 800 && mouseX <= 970 &&
			mouseY >= 450 && mouseY <= 520)
		{
			g_app.PlayUIClick();

			// PLAY Scene 다시 시작
			g_app.ChangeScene(SceneType::PLAY);
		}

		// EXIT 영역
		else if (mouseX >= 800 && mouseX <= 920 &&
			mouseY >= 550 && mouseY <= 620)
		{
			g_app.PlayUIClick();

			PostQuitMessage(0);
		}
	}

	return 0;
}

int SceneGameResult::Render()
{
	//score출력
	RECT scoreTitleRect{400, 150, 966, 230};
	g2_FontDrawText(m_fontTitle, scoreTitleRect, 0xFFFFFFFF, "SCORE");
	// 실제 점수 출력
	RECT scoreRect{400, 250, 966, 330};

	g2_FontDrawText(m_fontTitle, scoreRect, 0xFFFFFFFF, "% d / 5", m_score);
	//RESTART 출력
	RECT restartRect{800, 450, 970, 520};

	g2_FontDrawText(m_fontMenu, restartRect, 0xFFFFFFFF, "RESTART");
	//EXIT 출력
	RECT exitRect{800, 550, 920, 620};

	g2_FontDrawText(m_fontMenu, exitRect, 0xFFFFFFFF, "EXIT");

	return 0;
}

void SceneGameResult::SetScore(int score)
{
	m_score = score;
}