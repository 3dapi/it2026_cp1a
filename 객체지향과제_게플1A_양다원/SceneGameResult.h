#pragma once
#include "glc2d.h"

class CApplication;

enum RESULT
{
	NONE,
	LOSE,
	WIN
};

class SceneGameResult
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

	void SetOutcome(bool outcome, float playtime);

	
private:
	RESULT result = NONE;
	bool _isWin = false;
	float _time = 0.0f;

	int resultText = -1;
	RECT resultPos{ 570,230,750,300 };
	bool _isPlayed = false;

	int gameText = -1;
	RECT exitPos{ 590,405,720,455 };
	RECT replayPos{ 550,350,730,400 };
	RECT timePos{450, 50, 850, 100};
};

