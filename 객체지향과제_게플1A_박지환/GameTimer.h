#pragma once
#include "glc2d.h"

class GameTimer
{
public:
	int Init();
	int Update();

public:
	float GetDeltaTime() const;

private:
	long long	m_lastTime	{0};
	float		m_deltaTime {0.0f};

};

