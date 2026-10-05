#pragma once
#include "E_SceneType.h"
#include "IScene.h"
#include "DeltaTimer.h"

class IScene;

class SceneManager
{
private:
	E_SceneType _curSceneType;
	IScene* _curScenePtr = nullptr;

	IScene* _nextScenePtr = nullptr;
	E_SceneType _nextSceneType;

	bool _changeRequested = false;
public :
	const E_SceneType& g_curSceneType;

	SceneManager() : _curSceneType(E_SceneType::TITLE),g_curSceneType(_curSceneType){}

	void InitEngine();
	void Run();
	void ChangeScene(IScene* nextScene, E_SceneType targetType);
	void ApplySceneChange();

	IScene* GetCurrentScene() const { return _curScenePtr; }
};

