#pragma once
#include "E_SceneType.h"
#include "SceneManager.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <glc2d.h>

class SceneManager;
extern SceneManager g_SceneMgr;

class IScene
{
protected:
	E_SceneType _sceneType;

	//windows Setting
	std::string _winName = "None";
	POINT _winPos{ 0,0 };
	SIZE  _winSize {1280,720};
	unsigned int _winColor = 0x000000;

public:
	IScene(E_SceneType type) : _sceneType(type){}
	virtual ~IScene() {}

	//Windows
	void SetWindow(bool setWinPos = true);
	void SetWindowColor(unsigned int col);
	void SetFullScreen();


	//Birth
	virtual void Init();
	virtual void InitSDK();

	//Life-Cycle
	virtual void Update();
	virtual void Render();

	//Death
	virtual void Destroy();

	bool CheckAndProcess(E_SceneType curType);
};

