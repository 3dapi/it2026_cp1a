#include "glc2d.h"
#include "CApplication.h"
#include <stdio.h>

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
	InitSDK();
	m_scenebegin.Init();
	return 0;
}

int CApplication::Update()
{
	if (m_scene == Scenes::SCENEBEGIN)
	{
		m_scenebegin.Update();
	}
	else if (m_scene == Scenes::SCENEPLAY)
	{
		m_sceneplay.Update();
	}
	else if (m_scene == Scenes::SCENESCORE)
	{
		m_scenescore.Update();
	}
	return 0;
}

int CApplication::Render()
{
	if (m_scene == Scenes::SCENEBEGIN)
	{
		m_scenebegin.Render();
	}
	else if (m_scene == Scenes::SCENEPLAY)
	{
		m_sceneplay.Render();
	}
	else if (m_scene == Scenes::SCENESCORE)
	{
		m_scenescore.Render();
	}
	return 0;
}

int CApplication::Destroy()
{
	m_scenebegin.Destroy();
	g2_DestroyWin();
	return 0;
}

int CApplication::InitSDK()
{
	//SDK�ʱ�ȭ
	g2_InitSdk();

	printf("Starting... \n\n");
	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);

	g2_CreateWin(m_winPos.x, m_winPos.y, m_winSize.cx, m_winSize.cy, m_winName.c_str());

	g2_SetClearColor(0xFF000000);

	return 0;
}

void CApplication::ChangeScene(Scenes scene)
{
	if (m_scene == Scenes::SCENEBEGIN)
	{
		m_scenebegin.Destroy();
	}
	else if (m_scene == Scenes::SCENEPLAY)
	{
		m_sceneplay.Destroy();
	}
	else if (m_scene == Scenes::SCENESCORE)
	{
		m_scenescore.Destroy();
	}
	m_scene = scene;

	if (m_scene == Scenes::SCENEBEGIN)
	{
		m_scenebegin.Init();
	}
	else if (m_scene == Scenes::SCENEPLAY)
	{
		m_sceneplay.Init();
	}
	else if (m_scene == Scenes::SCENESCORE)
	{
		m_scenescore.Init();
	}
}