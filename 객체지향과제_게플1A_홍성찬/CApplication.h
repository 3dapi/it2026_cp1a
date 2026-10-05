#pragma once
#include <windows.h>
#include <unordered_map>
#include <string>
#include "Scene.h"
#include "SceneGameStart.h"
#include "SceneGamePlay.h"
#include "SceneGameResult.h"

enum class SceneType
{
	SCENESTART,
	SCENEPLAY,
	SCENERESULT
};

class CApplication
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

	void SignChangeScene(SceneType sceneType);

	// windows
	const POINT m_winPos{ 100, 100 };
	const SIZE m_winSize{ 1024, 600 };
	std::string m_winName = "Block Runner";

protected:
	int InitSdk();
	int SetScenes();

	// scene manage
	Scene* m_currentScene = nullptr;
	SceneType m_currentSceneType;
	std::unordered_map<SceneType, Scene*> m_scenes;

	SceneGameStart m_sceneStart;
	SceneGamePlay m_scenePlay;
	SceneGameResult m_sceneResult;

	bool m_isChangeScene;
};