#pragma once
class SoundEffectter
{
public:
	int SetIdx(const char* soundFile);
	void SoundPlay(const bool doLoop = false);
	void SoundPlayFromStart();

private:
	int m_idx{};
};

