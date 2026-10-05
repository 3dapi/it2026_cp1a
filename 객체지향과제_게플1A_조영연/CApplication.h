#pragma once
#include <windows.h>
#include <string>
#include "SceneBegin.h"
#include "ScenePlay.h"

enum class SCENE
{
	BEGIN,
	PLAY
};

class CApplication
{
public:
	int Init();
	int Destroy();
	int Render();
	int Update();

protected:
	int InitSDK();

protected:
	// windows
	POINT m_winPos{ 100, 100 };
	SIZE m_winSize{ 800, 600 };
	
	std::string m_winName = "Tetris++";

	SCENE m_scene = SCENE::BEGIN;
	
	SceneBegin m_scenebegin;
	ScenePlay m_sceneplay;
};
