#include "ScenePlay.h"
#include "SceneBegin.h"
#include "SceneScore.h"
#include "glc2d.h"
#include "CApplication.h"

extern CApplication g_app;

int SceneScore::Init()
{
	nFont1 = g2_FontCreate("굴림", 50, 1);
	nFont2 = g2_FontCreate("굴림", 30, 0);

	return 0;
}

int SceneScore::Update()
{
	return 0;
}

int SceneScore::Render()
{
	//배경
	g2_SetClearColor(0x364369FF);

	//게임오버
	g2_FontDrawText(nFont1, { 260, 100, 540, 150 }, 0xFFFFFFFF, "게임오버");
	g2_FontDrawText(nFont2, { 260, 200, 540, 250 }, 0xFFFFFFFF, "점수 : %d", ScenePlay::score);
	g2_FontDrawText(nFont2, { 220, 300, 570, 350 }, 0xFFFFFFFF, "[R] 재시작 / [ESC]종료");

	const KEYCODE* pKey = g2_GetKeyboard();
	if (pKey['R'])
	{
		g_app.ChangeScene(Scenes::SCENEPLAY);
	}
	else if (pKey[VK_ESCAPE])
	{
		g_app.Destroy();
	}

	return 0;
}

int SceneScore::Destroy()
{
	return 0;
}