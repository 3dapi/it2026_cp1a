#include "Time.h"

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_periodFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);

	m_timeScale = 1.0 / (double)m_periodFrequency;
}

float Time::GetDeltaTime()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentTime);
	deltaTime = (double)(m_currentTime - m_lastTime) * m_timeScale;
	m_lastTime = m_currentTime;

	return (float)deltaTime;
}