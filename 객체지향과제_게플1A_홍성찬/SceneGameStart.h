#pragma once
#include "Scene.h"
#include "Image.h"
#include "Background.h"

class SceneGameStart : public Scene
{
private:
	Background* m_background = nullptr;
	Image* m_gameTitle = nullptr;
	Image* m_guidTextImage = nullptr;

public:
	int Init() override;
	int Update(float deltaTime) override;
	int Render() override;
	int Destroy() override;
};

