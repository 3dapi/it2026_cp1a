#include "DeltaTimer.h"

DeltaTimer g_deltaTimer;

DeltaTimer::DeltaTimer() : _lastTime(0), _deltaTime(0.0f) {}

DeltaTimer::~DeltaTimer(){}

void DeltaTimer::Init()
{
	_lastTime = g2_TimeGetTime();
}

void DeltaTimer::Update()
{
	long long curTime = g2_TimeGetTime();

	_deltaTime = static_cast<float>(curTime - _lastTime) / 1000.0f;

	_lastTime = curTime;
}

float DeltaTimer::GetDeltaTime() const { return _deltaTime; }
