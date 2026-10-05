#pragma once

#include <memory>
#include <utility>
#include <vector>
using std::vector;

#include <string>
using std::string;

#include "Texture.h"

class AnimationClip
{
private:
	string _clipName;
	vector<std::unique_ptr<Texture>> _textures;
	float _frameDuration;
	bool _isLoop;
public:
	AnimationClip(string name, float frameDur = 0.1f, bool loop = true)
		: _clipName(name), _frameDuration(frameDur), _isLoop(loop) {}
	~AnimationClip() = default;

	void AddTexture(std::unique_ptr<Texture>);
	Texture* GetTexture(int idx);

	int GetFrameCount() const;

	float GetFrameDuration() const;
	void SetFrameDuration(float duration);
	
	bool IsLoop() const;
	string GetName() const;

};

