#pragma once
#include <unordered_map>
#include "glc2d.h"

enum class SoundType
{
	PLAYER_MOUSE_CLICKSOUND,
	PLAYER_JUMPSOUND,
	PLAYER_DIE
};

class SoundManager
{
public:
	int SetTextureFiles();
	std::unordered_map<SoundType, CSTR> m_soundFiles;
};