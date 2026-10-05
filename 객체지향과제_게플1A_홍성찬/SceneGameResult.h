#pragma once
#include "Scene.h"
#include "Image.h"

class SceneGameResult : public Scene
{
private:
	Image* m_gameoverTitle = nullptr;
	Image* m_scoreText = nullptr;
	Image* m_guidTextImage = nullptr;

	int m_scoreFont;

public:
	int Init() override;
	int Update(float deltaTime) override;
	int Render() override;
	int Destroy() override;
};

