#pragma once
#include "glc2d.h"
#include "ScenePlay.h"

class SceneBegin
{
public:
	int Init();
	int Destroy();
	int Render();
	int Update();
protected:
	int image01 = -1;
	int image02 = -1;
	//배경화면
	int background01 = -1;
	//시작 버튼
	bool onPlayButton = false;
	int playButton01 = -1;
	int playButton02 = -1;
protected:
	int sound01 = -1;
protected:
	VEC2 pos01 = { 80.0f, 30.0f };
	VEC2 pos02 = { 100.0f, 70.0f };
	VEC2 scale = { 1.0f, 1.0f };

	VEC2 bgPos = { 0.0f, 0.0f };
	VEC2 bgScale = { 0.7f, 0.7f };

	VEC2 playButtonPos = { 270.0f, 250.0f };
	VEC2 playButtonScale = { 1.0f, 1.0f };
protected:
	int nFont1 = -1;
	int nFont2 = -1;
	int nFont3 = -1;
};