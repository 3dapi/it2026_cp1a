#pragma once
#include <memory>
#include <unordered_map>
using std::unordered_map;

#include <string>
using std::string;

#include "AnimationClip.h"

class Animator
{
private:
	unordered_map<string,std::unique_ptr<AnimationClip>> _clips;
	AnimationClip* _curClip = nullptr;

	float _accumulatedTime = 0.0f;
	int _curFrameIdx = 0;

public:
	Animator() = default;
	~Animator() = default;

	void AddClip(const string& name,
		std::unique_ptr<AnimationClip> clip);
	void ChangeClip(const string& name);

	void Play(float delta);
	void Restart();

	Texture* GetCurrentTexture();
};

