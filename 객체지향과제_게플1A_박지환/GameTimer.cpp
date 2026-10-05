#include "GameTimer.h"

int GameTimer::Init()
{
	m_lastTime = g2_TimeGetTime();
	m_deltaTime = 0.0f;

	return 0;
}


int GameTimer::Update()
{
	long long currentTime = g2_TimeGetTime();

	m_deltaTime = static_cast<float>(currentTime - m_lastTime) * 0.001f; 
	m_lastTime = currentTime;

	return 0;
}

float GameTimer::GetDeltaTime() const
{
	return m_deltaTime;
}