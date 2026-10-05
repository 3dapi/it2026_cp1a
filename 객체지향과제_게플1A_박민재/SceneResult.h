#pragma once
#include "CScene.h"
#include "glc2d.h"
#include <stdio.h>

class SceneResult : public CScene
{
public:
	SceneResult(bool isClear, int remainSecond, int killCount, int curHp);

	int Init() override;
	int Update() override;
	int Render(CApplication& application) override;
	int Destroy() override;

private:
	bool m_IsClear = false;
	int m_RemainSecond = 0;
	int m_KillCount = 0;
	int m_CurHp = 0;

	int m_BackGroundTexture = -1;


};
