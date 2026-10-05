#pragma once
#include <random>
#include "Scene.h"
#include "Entity.h"
#include "Obstacle.h"
#include "GameObject.h"

class SceneGamePlay : public Scene
{
private:
	static const int m_obstacleCount = 5;

	Entity* m_player = nullptr;
	Obstacle* m_ground = nullptr;
	Obstacle* m_obstacles[2][m_obstacleCount] = {};

	const float m_startObstacleSpeed = 300.0f;
	const float m_speedIncrease = 10.0f;
	const float m_speedUpInterval = 10.0f;

	float m_obstacleSpeed = 300.0f;
	float m_minSpawnInterval = 1.0f;
	float m_maxSpawnInterval = 3.0f;
	float m_spawnInterval = 0.0f;

	float m_IncreaseScoreInterval = 1.0f;

	float m_spawnTimer = 0.0f;
	float m_speedUpTimer = 0.0f;
	float m_scoreTimer = 0.0f;

	std::mt19937 m_random{ std::random_device{}() };

	float GetRandom(float min, float max);
	void SpawnObstacle();
	void IncreaseObstacleSpeed();

	bool m_gameProcess;
	int m_jumpSound;
	int m_DeathSound;

	int m_scoreFont;

public:
	int Init() override;
	int Update(float deltaTime) override;
	int Render() override;
	int Destroy() override;
};