// link the 2d game library
#if defined(_DEBUG)
#if defined(_M_X64) // 64-bit 아키텍처
#pragma comment(lib, "glc2d_x64_debug.lib")
#elif defined(_M_IX86) // 32-bit 아키텍처
#pragma comment(lib, "glc2d_win32_debug.lib")
#endif
#else
#if defined(_M_X64)
#pragma comment(lib, "glc2d_x64_release.lib")
#elif defined(_M_IX86)
#pragma comment(lib, "glc2d_win32_release.lib")
#endif
#endif

// include the 2d game header file
#include "glc2d.h"
#include <stdio.h>

#include "SoundEffectter.h"


int SoundEffectter::SetIdx(const char* soundFile)
{
	return m_idx = g2_SoundLoad(soundFile);
}

// 소리 재생, true를 넣으면 루프.
void SoundEffectter::SoundPlay(const bool doLoop)
{
	g2_SoundPlay(m_idx, doLoop);
}

void SoundEffectter::SoundPlayFromStart()
{
	if (!g2_SoundIsPlaying(m_idx))
	{
		g2_SoundReset(m_idx);
		g2_SoundPlay(m_idx);
	}
}
