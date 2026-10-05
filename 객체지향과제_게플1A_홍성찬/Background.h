#pragma once
#include "GameObject.h"

enum class BackgroundType
{
	SCREEN_START,
	SCREEN_PLAY
};

class Background : public GameObject
{
public:
	Background();
	~Background() override;

	int Update(float deltaTime) override;
	int Render() override;
};