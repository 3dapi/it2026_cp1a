#include "ProgressBar.h"

ProgressBar::ProgressBar(VEC2 pos)
	: GameObject(pos)
{
	string prefix = "rsc/imgs/ProgressBar/Bar_";

	auto clip = std::make_unique<AnimationClip>(
		"Progress", 0.1f, false);

	for(int i = 0; i < 5; i++)
	{
		auto tex = std::make_unique<Texture>
			(
				prefix + std::to_string(i) + ".png", pos
			);
		tex->Load();

		clip->AddTexture(std::move(tex));
	}
	_progressClip = clip.get();

	_anim->AddClip("Progress", std::move(clip));
	_anim->ChangeClip("Progress");
}


void ProgressBar::SetTime(float time)
{
	int frameCount = _progressClip->GetFrameCount();

	if (frameCount <= 1)
		return;

	float frameDur = time / (frameCount - 1);

	_progressClip->SetFrameDuration(frameDur);

	_anim->Restart();
}