#pragma once
#include <vector>
#include "Scene.h"
#include "Player.h"
#include "Rock.h"

using std::vector;

class SceneGamePlay : public Scene
{
public:
	int Init() override;
	int Update(float deltaTime) override;
	int Destroy() override;
	int Render() override;

public:
	int GetScore() const;

protected:
	int m_txBg{ -1 };
	int m_bgm{ -1 };
	int m_hitSound{ -1 };
	int m_scoreFont{ -1 };
	int m_font{ -1 };

	int score{};
	float timer{};
	float rockSpawnTimer{};

	Player player;
	vector<Rock*> rocks;

	bool isGameOver{};
	float gameOverTimer{};

	void SpawnRock();
};