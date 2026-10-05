#include "Animator.h"

void Animator::AddClip(const string& name,
	std::unique_ptr<AnimationClip> clip)
{
	AnimationClip* raw = clip.get();

	_clips[name] = std::move(clip);

	if (_curClip == nullptr)
		_curClip = raw;
}
void Animator::ChangeClip(const string& name)
{
	auto it = _clips.find(name);
	
	if (it == _clips.end())
		return;
	_curClip = it->second.get();
}
void Animator::Play(float delta)
{
	//카운트 0? 클립 NULL?
	if (!_curClip || !_curClip->GetFrameCount()) return;

	_accumulatedTime += delta;

	if (_accumulatedTime >= _curClip->GetFrameDuration())
	{
		_accumulatedTime = 0.0f;
		_curFrameIdx++;

		if (_curFrameIdx >= _curClip->GetFrameCount())
		{
			if (_curClip->IsLoop())
				_curFrameIdx = 0;
			else
				_curFrameIdx = _curClip->GetFrameCount() - 1;
		}
	}
}

void Animator::Restart()
{
	_curFrameIdx = 0;
	_accumulatedTime = 0.0f;
}

Texture* Animator::GetCurrentTexture()
{
	if (!_curClip) return nullptr;

	if (_curFrameIdx < 0 || _curFrameIdx >= _curClip->GetFrameCount()) return nullptr;
	return _curClip->GetTexture(_curFrameIdx);
}