#pragma once
#include <windows.h>
#include <string>
#include "glc2d.h"
#include "SceneGameBegin.h"
#include "SceneGamePlay.h"
#include "SceneGameResult.h"

using std::string;

class CApplication
{
public:
	int Init();
	int Update();
	int Destroy();
	int Render();

public:
	SIZE GetWinSize();

	void ChangeScene(int scene);

protected:
	int InitSdk();

protected:
	//windows
	POINT m_winPos{ 100, 100 };
	SIZE m_winSize{ 360, 640 };

	string m_winName = "DEEPFALL";

	SceneGameBegin m_sceneBegin;
	SceneGamePlay m_scenePlay;
	SceneGameResult m_sceneResult;

	Scene* m_scene{};

	long long m_prevTime{ 0 };
};

//전역 접근
extern CApplication g_app;