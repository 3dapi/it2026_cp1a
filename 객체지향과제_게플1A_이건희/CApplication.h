#pragma once
#include <windows.h>
#include <string>
#include "SceneBegin.h"
#include "ScenePlay.h"
#include "SceneScore.h"

enum class Scenes
{
	SCENEBEGIN,
	SCENEPLAY,
	SCENESCORE,
};

class CApplication
{
public:
	int Init();
	int Destroy();
	int Render();
	int Update();
public:
	void ChangeScene(Scenes scene);
protected:
	int InitSDK();

protected:
	// windows
	POINT m_winPos{ 100, 100 };
	SIZE m_winSize{ 800, 600 };

	std::string m_winName = "C++ Shooting Game";

	Scenes m_scene = Scenes::SCENEBEGIN;

	SceneBegin m_scenebegin;
	ScenePlay m_sceneplay;
	SceneScore m_scenescore;
};
#pragma once