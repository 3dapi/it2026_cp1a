#pragma once
#include "glc2d.h"
class CApplication;

class SceneGameBegin
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

private:
	static constexpr int startLeft = 580;
	static constexpr int startTop = 400;
	static constexpr int startRight = 730;
	static constexpr int startBottom = 500;

	int startButton = -1;
	RECT startPos{ 580,400,700,460 };

	int exitButton = -1;
	RECT exitPos{ 580,475,700,535 };

};

