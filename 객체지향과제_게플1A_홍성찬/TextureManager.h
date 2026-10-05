#pragma once
#include <iostream>
#include <unordered_map>
#include "glc2d.h"

enum class TextureType
{
	BACKGROUND,
	GROUND,
	ENTITY_PLAYER_FRONT,
	ENTITY_PLAYER_BACK,
	GAMEOBJECT_OBSTACLE_BLOCK,
	GAMEOBJECT_OBSTACLE_TWOBLOCK,
	UI_TITLE_GAMEMAINMENU,
	UI_GUIDTEXT,
	UI_TITLE_GAMEOVER,
	UI_TEXT_SCORE
};

class TextureManager
{
public:
	int SetTextureFiles();
	std::unordered_map<TextureType, CSTR> m_textureFiles;
};