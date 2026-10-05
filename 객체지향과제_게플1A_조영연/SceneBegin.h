#pragma once
#include "glc2d.h"
class SceneBegin
{
public:
	int Init();
	int Destroy();
	int Render();
	int Update();
protected:
	int m_txt = -1;
	int m_font = -1;

protected:
	VEC2 pos = { 80.0f, 30.0f };
	VEC2 scale = { 0.3f, 0.3f };

};

