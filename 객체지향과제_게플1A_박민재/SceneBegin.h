#pragma once
#include "CScene.h"

class SceneBegin : public CScene
{
public:
	int Init() override;
	int Update() override;
	int Render(CApplication& application) override;
	int Destroy() override;

protected:
	int m_BackGroundTexture = -1;
	
	int m_BackGroundMusic = -1;
};
