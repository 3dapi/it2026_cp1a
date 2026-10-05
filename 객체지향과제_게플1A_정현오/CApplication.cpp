#include "CApplication.h"

CApplication g_app;

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
	ChangeScene(SCENE_BEGIN);

	m_prevTime = g2_TimeGetTime();

	return 0;
}

int CApplication::Update()
{
	long long currentTime = g2_TimeGetTime();
	float deltaTime = static_cast<float>(currentTime - m_prevTime) / 1000.0f;
	m_prevTime = currentTime;

	if (nullptr == m_scene)
	{
		return 0;
	}

	int nextScene = m_scene->Update(deltaTime);
	if (SCENE_KEEP != nextScene)
	{
		ChangeScene(nextScene);
	}

	return 0;
}

int CApplication::Destroy()
{
	if (nullptr != m_scene)
	{
		m_scene->Destroy();
		m_scene = nullptr;
	}

	g2_DestroyWin();

	return 0;
}

int CApplication::Render()
{
	if (nullptr != m_scene)
	{
		m_scene->Render();
	}

	return 0;
}

SIZE CApplication::GetWinSize()
{
	return m_winSize;
}

int CApplication::InitSdk()
{
	g2_InitSdk();
	g2_CreateWin(m_winPos.x, m_winPos.y, m_winSize.cx, m_winSize.cy, m_winName.c_str());
	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);

	return 0;
}

void CApplication::ChangeScene(int scene)
{
	Scene* nextScene{};

	switch (scene)
	{
	case SCENE_BEGIN:
		nextScene = &m_sceneBegin;
		break;

	case SCENE_PLAY:
		nextScene = &m_scenePlay;
		break;

	case SCENE_RESULT:
		m_sceneResult.SetScore(m_scenePlay.GetScore());
		nextScene = &m_sceneResult;
		break;

	case SCENE_QUIT:
		PostQuitMessage(0);
		return;

	default:
		return;
	}

	if (nullptr != m_scene)
	{
		m_scene->Destroy();
	}

	m_scene = nextScene;
	m_scene->Init();
}