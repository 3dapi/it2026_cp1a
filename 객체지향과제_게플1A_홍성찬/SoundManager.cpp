#include <unordered_map>
#include "SoundManager.h"
#include "glc2d.h"

int SoundManager::SetTextureFiles()
{
	printf("..... Set SoundFiles");

	m_soundFiles[SoundType::PLAYER_JUMPSOUND] = "resource/Sound/jump.wav";
	m_soundFiles[SoundType::PLAYER_DIE] = "resource/Sound/die.wav";

	return 0;
}