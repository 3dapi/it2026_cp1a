#include <unordered_map>
#include "TextureManager.h"

int TextureManager::SetTextureFiles()
{
	printf("..... Set TextureFiles");

	m_textureFiles[TextureType::ENTITY_PLAYER_FRONT] = "resource/Texture/Player_Front.png";
	m_textureFiles[TextureType::ENTITY_PLAYER_BACK] = "resource/Texture/Player_Back.png";
	m_textureFiles[TextureType::BACKGROUND] = "resource/Texture/Background/desert.png";
	m_textureFiles[TextureType::GROUND] = "resource/Texture/Ground.png";
	m_textureFiles[TextureType::GAMEOBJECT_OBSTACLE_BLOCK] = "resource/Texture/Obstacle.png";
	m_textureFiles[TextureType::GAMEOBJECT_OBSTACLE_TWOBLOCK] = "resource/Texture/Obstacle2.png";
	m_textureFiles[TextureType::UI_TITLE_GAMEMAINMENU] = "resource/Texture/ImageText/Title_GameMainMenu.png";
	m_textureFiles[TextureType::UI_GUIDTEXT] = "resource/Texture/ImageText/Button_Start.png";
	m_textureFiles[TextureType::UI_TITLE_GAMEOVER] = "resource/Texture/ImageText/TItle_GameOver.png";
	m_textureFiles[TextureType::UI_TEXT_SCORE] = "resource/Texture/ImageText/Text_Score.png";

	return 0;
}