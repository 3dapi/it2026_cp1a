#pragma once
#include "Windows.h"

class Time
{
private:
	double deltaTime;
	double m_timeScale;
	__int64 m_periodFrequency;
	__int64 m_lastTime;
	__int64 m_currentTime;

public:
	Time();
	float GetDeltaTime();
};