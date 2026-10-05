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
	switch (m_scene)
	{
	case SCENE::BEGIN:

		if (m_scenebegin.Update() == 1)
		{
			m_scenebegin.Destroy();

			m_sceneplay.Init();

			m_scene = SCENE::PLAY;
		}

		break;


	case SCENE::PLAY:

		m_sceneplay.Update();

		break;
	}

	return 0;
}

int CApplication::Render()
{
	switch (m_scene)
	{
	case SCENE::BEGIN:

		m_scenebegin.Render();

		break;


	case SCENE::PLAY:

		m_sceneplay.Render();

		break;
	}

	return 0;
}

int CApplication::Destroy()
{
	switch (m_scene)
	{
	case SCENE::BEGIN:
		m_scenebegin.Destroy();
		break;

	case SCENE::PLAY:
		m_sceneplay.Destroy();
		break;
	}

	g2_DestroyWin();

	return 0;
}

int CApplication::InitSDK()
{
	//SDK√ ±‚»≠
	g2_InitSdk();

	printf("Starting... \n\n");
	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);

	g2_CreateWin(m_winPos.x,m_winPos.y,m_winSize.cx,m_winSize.cy, m_winName.c_str());

	g2_SetClearColor(0xFF000000);

	return 0;
}
