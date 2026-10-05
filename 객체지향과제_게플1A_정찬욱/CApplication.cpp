#include <stdio.h>
#include "CApplication.h"
#include "glc2d.h"

extern CApplication g_app;

int AppUpdate()
{
	return g_app.Update();
}

int AppRender()
{
	return g_app.Render();
}


int CApplication::Init()
{
	InitSdk();

	m_sceneBegin.Init();

	return 0;
}

int CApplication::Update()
{
	printf("Update ...\n\n");

	m_sceneBegin.Update();
	return 0;
}

int CApplication::Render()
{
	printf("Render ...\n\n");

	m_sceneBegin.Render();

	return 0;
}

int CApplication::Destroy()
{
	m_sceneBegin.Destroy();

	// 윈도우 해제
	g2_DestroyWin();

	return 0;
}

int CApplication::InitSdk()
{
	// SDK 초기화
	g2_InitSdk();

	printf("Starting ...\n\n");
	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);


	// 작업 표시줄을 제외한 화면 영역
	RECT workArea{};
	SystemParametersInfo(
		SPI_GETWORKAREA, 0, &workArea, 0);

	// 화면 중앙에 배치할 좌표 계산
	m_winPos.x = workArea.left
		+ ((workArea.right - workArea.left) - m_winSize.cx) / 2;

	m_winPos.y = workArea.top
		+ ((workArea.bottom - workArea.top) - m_winSize.cy) / 2
		- 40;

	// 윈도우 생성
	g2_CreateWin(m_winPos.x, m_winPos.y
		, m_winSize.cx, m_winSize.cy, m_winName.c_str());

	return 0;
}
