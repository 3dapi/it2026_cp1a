#pragma once
#include <string>
#include "SceneGameBegin.h"
#include "SceneGamePlay.h"
#include "SceneGameResult.h"

enum class SceneType
{
	BEGIN,
	PLAY,
	RESULT
};


class CApplication
{
public:
	bool Init();
	int Update();
	int Render();
	int Destroy();

	void ChangeScene(SceneType scene);
	void PlayUIClick();

public:
	SIZE GetWinSize();
	void ShowResult(int score);
	void PlayPaddleHit();

protected:
	int InitSdk();

protected:
	// windows
	POINT m_winPos{ 250, 100 };						//창 열리는 위치
	SIZE m_winSize{ 1366, 768 };					//창 크기
	std::string m_winName = "Ping Pong";

	// 현재 Scene
	SceneType m_scene = SceneType::BEGIN;

	// Scene 객체
	SceneGameBegin m_sceneBegin;
	SceneGamePlay m_scenePlay;
	SceneGameResult m_sceneResult;

protected://사운드 
	int BG_sound = -1;
	int UI_click_sound = -1;
	int Paddle_hit_sound = -1;
};


// 전역 접근
extern CApplication g_app;