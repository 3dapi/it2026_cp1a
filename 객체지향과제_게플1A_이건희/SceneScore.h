#pragma once
#include "glc2d.h"
#include "ScenePlay.h"

class SceneScore
{
public:
	int Init();
	int Destroy();
	int Render();
	int Update();
protected:
	int nFont1 = -1;
	int nFont2 = -1;
};
#pragma once
