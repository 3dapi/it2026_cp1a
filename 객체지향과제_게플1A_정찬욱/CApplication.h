#pragma once
#include <windows.h>
#include <string>
#include "SceneGameBegin.h"

class CApplication
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	int InitSdk();

protected:
	// 게임 창 설정
	POINT m_winPos{ 100, 100 };
	SIZE m_winSize{ 1280, 720 };
	std::string m_winName = "Hell Shooting";

	SceneGameBegin m_sceneBegin;
};
