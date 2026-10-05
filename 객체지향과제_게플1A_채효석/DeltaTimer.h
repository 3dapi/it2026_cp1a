#pragma once
#include <glc2d.h>
class DeltaTimer
{
private:
	long long _lastTime;
	float _deltaTime;
public:
	DeltaTimer();
	~DeltaTimer();

	void Init();
	void Update();

	float GetDeltaTime() const;

};

extern DeltaTimer g_deltaTimer;
