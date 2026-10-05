#include "AnimationClip.h"
void AnimationClip::AddTexture(std::unique_ptr<Texture> tex) { _textures.push_back(std::move(tex)); }

Texture* AnimationClip::GetTexture(int idx)
{
	if (_textures.empty() || idx < 0 || idx >= static_cast<int>(_textures.size())) return nullptr;
	return _textures[idx].get();
}

int AnimationClip::GetFrameCount() const { return (int)_textures.size(); }

float AnimationClip::GetFrameDuration() const { return _frameDuration; }
void AnimationClip::SetFrameDuration(float duration) { _frameDuration = duration; }


bool AnimationClip::IsLoop() const { return _isLoop; }
string AnimationClip::GetName() const { return _clipName; }
