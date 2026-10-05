#include <iostream>
#include <Windows.h>
#include "glc2d.h"
#include "SceneGamePlay.h"
#include "CApplication.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "GameObject.h"
#include "Entity.h"
#include "Obstacle.h"
#include "TextureManager.h"

#define OBSTACLE_ONEBLOCK 0
#define OBSTACLE_TWOBLOCK 1

extern CApplication g_app;
extern SoundManager g_soundManager;
extern GameManager g_gameManager;

int& m_score = g_gameManager.m_score;

void PlayerController(Entity* player, int jumpSound)
{
	const KEYCODE* pKeyboard = g2_GetKeyboard();

	float jumpForce = 1000.0f;
	float moveSpeed = 200.0f;

	if (pKeyboard[65])
	{
		VEC2 playerV = player->GetVelocity();
		VEC2 v(-moveSpeed, playerV.y);
		player->SetVelocity(v);
		player->SetTexture(TextureType::ENTITY_PLAYER_BACK);
	}
	else if (pKeyboard[68])
	{
		VEC2 playerV = player->GetVelocity();
		VEC2 v(moveSpeed, playerV.y);
		player->SetVelocity(v);
		player->SetTexture(TextureType::ENTITY_PLAYER_FRONT);
	}
	else
	{
		VEC2 playerV = player->GetVelocity();
		VEC2 v(0, playerV.y);
		player->SetVelocity(v);
	}

	if (pKeyboard[VK_SPACE] && player->IsOnGround())
	{
		g2_SoundPlay(jumpSound);

		VEC2 playerV = player->GetVelocity();
		VEC2 v(playerV.x, -jumpForce);
		player->SetVelocity(v);
	}
}

void ClampToScreen(GameObject* obj)
{
	VEC2 pos = obj->GetPosition();

	float maxX = (float)g_app.m_winSize.cx - obj->GetCollider().width;
	pos.x = Clamp(pos.x, 0.0f, maxX);

	obj->SetPosition(pos);
}

float SceneGamePlay::GetRandom(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(m_random);
}

void SceneGamePlay::SpawnObstacle()
{
	std::uniform_int_distribution<int> dist(0, 1);
	int type = dist(m_random);

	for (int i = 0; i < m_obstacleCount; i++)
	{
		Obstacle* obstacle = m_obstacles[type][i];

		if (obstacle->IsActive())
			continue;

		VEC2 spawnPos((float)g_app.m_winSize.cx, m_ground->GetTop() - obstacle->GetCollider().height);
		obstacle->SetPosition(spawnPos);
		obstacle->SetActive(true);

		return;
	}
}

void SceneGamePlay::IncreaseObstacleSpeed()
{
	m_obstacleSpeed += m_speedIncrease;

	// 이미 움직이고 있는 장애물도 바로 새 속도 적용
	for (int type = 0; type < 2; ++type)
	{
		for (int i = 0; i < m_obstacleCount; ++i)
		{
			m_obstacles[type][i]->SetMoveSpeed(m_obstacleSpeed);
		}
	}
}

int SceneGamePlay::Init()
{
	m_score = 0;
	m_obstacleSpeed = m_startObstacleSpeed;

	g_gameManager.m_currentBackgroundType = BackgroundType::SCREEN_PLAY;

	m_player = g_gameManager.CreateObject<Entity>();

	m_player->Init(TextureType::ENTITY_PLAYER_FRONT);
	VEC2 objPos(200, 400);
	m_player->SetPosition(objPos);
	VEC2 scaling = { 0.7, 0.7 };
	m_player->SetScaling(scaling);
	m_player->SetColliderSize();
	m_player->m_name = "Player";

	m_ground = g_gameManager.CreateObject<Obstacle>();
	m_ground->Init(TextureType::GROUND);
	m_ground->SetColliderSize();
	objPos = { 0, 500 };
	m_ground->SetPosition(objPos);

	for (int type = 0; type < 2; ++type)
	{
		for (int i = 0; i < m_obstacleCount; ++i)
		{
			Obstacle* obstacle = g_gameManager.CreateObject<Obstacle>();

			if (type == 0)
				obstacle->Init(TextureType::GAMEOBJECT_OBSTACLE_BLOCK);
			else if (type == 1)
				obstacle->Init(TextureType::GAMEOBJECT_OBSTACLE_TWOBLOCK);

			VEC2 obstacleScailing = { 0.6f, 1 };
			obstacle->SetScaling(obstacleScailing);

			obstacle->SetColliderSize();
			obstacle->SetMoveSpeed(m_obstacleSpeed);
			obstacle->SetTag(Tag::Obstacle);
			obstacle->SetActive(false);

			m_obstacles[type][i] = obstacle;
		}
	}


	m_spawnTimer = 0.0f;
	m_spawnInterval = GetRandom(m_minSpawnInterval, m_maxSpawnInterval);

	m_scoreFont = g2_FontCreate("Arial", 30, 0);
	m_jumpSound = g2_SoundLoad(g_soundManager.m_soundFiles[SoundType::PLAYER_JUMPSOUND]);
	m_DeathSound = g2_SoundLoad(g_soundManager.m_soundFiles[SoundType::PLAYER_DIE]);

	return 0;
}

int SceneGamePlay::Update(float deltaTime)
{
	g_gameManager.UpdateAll(deltaTime);
	ClampToScreen(m_player);

	PlayerController(m_player, m_jumpSound);

	m_scoreTimer += deltaTime;
	if (m_scoreTimer >= m_IncreaseScoreInterval)
	{
		m_scoreTimer = 0;
		m_score += 1;
	}

	m_spawnTimer += deltaTime;
	if (m_spawnTimer >= m_spawnInterval)
	{
		m_spawnTimer = 0.0f;
		m_spawnInterval = GetRandom(m_minSpawnInterval, m_maxSpawnInterval);
		SpawnObstacle();
	}

	m_speedUpTimer += deltaTime;
	if (m_speedUpTimer >= m_speedUpInterval)
	{
		m_speedUpTimer -= m_speedUpInterval;
		IncreaseObstacleSpeed();
	}

	if (m_player->m_collisionObstacle)
	{
		g2_SoundPlay(m_DeathSound);
		g_app.SignChangeScene(SceneType::SCENERESULT);
	}

	return 0;
}

int SceneGamePlay::Render()
{
	g_gameManager.RenderAll();

	RECT scoreRect = { 20, 20, 500, 60 };
	g2_FontDrawText(m_scoreFont, scoreRect, 0xFF000000, "%d", m_score);

	return 0;
}

int SceneGamePlay::Destroy()
{
	g_gameManager.ClearAll();

	return 0;
}