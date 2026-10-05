#include <stdio.h>
#include "glc2d.h"
#include "CApplication.h"
#include "GameManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Time.h"

#include "GameObject.h"
#include "Entity.h"
#include "Background.h"

extern CApplication g_app;
GameManager g_gameManager;
TextureManager g_textureManager;
SoundManager g_soundManager;

Time g_time;

Background* entity;

int AddUpdate()
{
	return g_app.Update();
}

int AddRender()
{
	return g_app.Render();
}

int CApplication::Init()
{
	InitSdk();
	SetScenes();
	g_textureManager.SetTextureFiles();
	g_soundManager.SetTextureFiles();

	m_currentScene = &m_sceneStart;
	m_currentScene->Init();

	return 0;
}

int CApplication::Update()
{
	m_currentScene->Update(g_time.GetDeltaTime());

	if (m_isChangeScene)
	{
		m_currentScene->Destroy();
		m_currentScene = m_scenes[m_currentSceneType];
		m_currentScene->Init();

		m_isChangeScene = false;
	}

	return 0;
}

int CApplication::Render()
{
	m_currentScene->Render();

	return 0;
}

int CApplication::Destroy()
{
	m_currentScene->Destroy();

	g2_DestroyWin();

	return 0;
}

void CApplication::SignChangeScene(SceneType sceneType)
{
	m_isChangeScene = true;
	m_currentSceneType = sceneType;
}

int CApplication::InitSdk()
{
	g2_InitSdk();

	g2_SetFrameMove(AddUpdate);
	g2_SetRender(AddRender);

	g2_CreateWin(m_winPos.x, m_winPos.y, m_winSize.cx, m_winSize.cy, m_winName.c_str());
	
	return 0;
}

int CApplication::SetScenes()
{
	m_scenes[SceneType::SCENESTART] = &m_sceneStart;
	m_scenes[SceneType::SCENEPLAY] = &m_scenePlay;
	m_scenes[SceneType::SCENERESULT] = &m_sceneResult;

	return 0;
}
