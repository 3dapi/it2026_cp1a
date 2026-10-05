#include "SceneGameBegin.h"
#include "glc2d.h"
#include "CApplication.h"

extern CApplication g_app;
//구현해야될것
//플레이화면 점수 출력
//종료화면 점수 출력

int SceneGameBegin::Init()
{
	this->m_txBG = g2_TextureLoad("resource/texture/begin/BG_Begin.png");					//시작화면 배경
	this->m_txUI_start = g2_TextureLoad("resource/texture/begin/ui_START.png");				//스타트 버튼
	this->m_txUI_exit = g2_TextureLoad("resource/texture/begin/ui_EXIT.png");				//나가기 버튼

	return 0;
}

int SceneGameBegin::Destroy()																
{
	//이미지 그림 제거
	g2_TextureRelease(m_txBG);
	g2_TextureRelease(m_txUI_start);
	g2_TextureRelease(m_txUI_exit);

	//이미지 번호 초기화
	m_txBG = -1;
	m_txUI_start = -1;
	m_txUI_exit = -1;

	return 0;
}

int SceneGameBegin::Update()
{
	//마우스 좌표
	int mouseX = g2_GetMouseX();
	int mouseY = g2_GetMouseY();															
	//마우스 클릭
	if (g2_GetMouseEvent(0) == EINPUT_DOWN)
	{
		// START 버튼 영역
		if (mouseX >= 880 && mouseX <= 1160 &&
			mouseY >= 410 && mouseY <= 490)
		{
			g_app.PlayUIClick();
			g_app.ChangeScene(SceneType::PLAY);
		}
	}
	if (g2_GetMouseEvent(0) == EINPUT_DOWN)
	{
		// EXIT 버튼 영역
		if (mouseX >= 850 && mouseX <= 1180 &&
			mouseY >= 520 && mouseY <= 640)
		{
			g_app.PlayUIClick();

			PostQuitMessage(0);
		}
	}
	return 0;
}

int SceneGameBegin::Render()
{
	//홈화면 배경 출력
	{
		VEC2 position_BG{ 0.0f, 0.0f };
		VEC2 scale{ 0.75f, 0.75f };
		g2_Draw2D(m_txBG, nullptr, &position_BG, &scale);
	}
	//홈화면 start버튼
	{
		VEC2 position_UI_start{ 840.0f, 330.0f };
		VEC2 scale_UI(0.2f, 0.2f);
		g2_Draw2D(m_txUI_start, nullptr, &position_UI_start, &scale_UI);
	}
	//홈화면 exit버튼
	{
		VEC2 position_UI_exit{ 840.0f, 470.0f };
		VEC2 scale_UI(0.17f, 0.17f);
		g2_Draw2D(m_txUI_exit, nullptr, &position_UI_exit, &scale_UI);
	}
	return 0;
}