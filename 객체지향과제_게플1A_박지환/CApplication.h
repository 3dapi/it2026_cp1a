#pragma once
#include <windows.h>
#include <string>
#include "SceneGameBegin.h"
#include "SceneGamePlay.h"
#include "SceneGameResult.h"


enum class Scene
{
	Begin,
	Play,
	Result
};


class CApplication
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();


public:
	SIZE GetWinSize();
	void ChangeScene(Scene nextScene);
	void RequestQuit();

protected:
	int InitSdk();

protected:
	// windows
	POINT m_winPos			{ 0, 0 };
	SIZE m_winSize			{ 1280, 720 };
	std::string m_winName	{ "Crash Out" };

	// scene
	Scene m_currentScene	{ Scene::Begin };

	SceneGameBegin	m_sceneBegin;
	SceneGamePlay	m_scenePlay;
	SceneGameResult m_sceneResult;
};

// 전역 접근
extern CApplication g_app;
