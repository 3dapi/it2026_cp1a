#pragma once

#include "GameObject.h"
#include <memory>
#include <string>
using std::string;

class ProgressBar : public GameObject
{
private:
	AnimationClip* _progressClip;

	float _maxTime;
	float _remainTime;
public :
	ProgressBar(VEC2 Pos);

	void SetTime(float time);
};

