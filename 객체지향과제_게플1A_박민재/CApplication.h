#pragma once
#include <Windows.h>
#include <string>
#include "CScene.h"

struct GameResource
{
	int fontTitle = -1;
	int fontMenu = -1;
	int fontNormal = -1;
};

class CApplication
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();
	
	int ChangeScene(CScene* pScene);

	const GameResource& GetResource() const;

protected:
	int InitSdk();

private:
	CScene* m_pScene = nullptr;
	GameResource m_Resource;

	// windows
	POINT m_winPos { 100, 100 };
	SIZE m_winSize { 1024, 680 };

	std::string m_winName = "StoneAge"; // 윈도우 창 제목

};

