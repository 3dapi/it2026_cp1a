#pragma once
#include "CScene.h"
#include "glc2d.h"

#include "CMap.h"
#include "CPlayer.h"
#include "CEnemy.h"

#include <stdio.h>
#include <vector>
#include <random>
#include <Windows.h>

enum {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class ScenePlay : public CScene
{
public:
	int Init() override;
	int Update() override;
	int Render(CApplication& application) override;
	int Destroy() override;

	int GetKillCount();

protected:
	CMap m_Map;
	CPlayer m_Player;

private:
	long long m_GameStartTime{};
	const long long m_SurvivalTime = 300000; // 300초

	void SpawnEnemy();
	VEC2 GetEnemySpawnPosition(); // 적 스폰 위치 결정 함수
	bool CheckCollision(const RECT& rc1, const RECT& rc2); // 충돌 여부 확인 함수
	void CheckPlayerEnemyCollision();
	void CheckEnemyEnemyCollision();
	void CheckPlayerAttack();

	// Monster Pool(적 객체 데이터 배열)
	std::vector<CEnemy> m_Enemies;
	
	// 최대 동시 소환 적 객체 수
	static const int Max_Enemy_Count = 50;
	int m_remainSecond{};

	// 스폰 조건
	long long m_SpawnTimer{};
	int m_SpawnInterval = 1000;
	float m_MinSpawnDistance = 300.0f;

	// kill count
	int m_EnemyKillCount;
	int m_CurHp;

	// 랜덤 머신
	std::random_device m_Rd;
	std::mt19937 m_Gen;
	std::uniform_int_distribution<int> m_SideDist; // 상하좌우 방향
	std::uniform_int_distribution<int> m_Width; // 넓이
	std::uniform_int_distribution<int> m_Height; // 높이

	int m_Boar_right_tx = -1;
	int m_Boar_left_tx = -1;

	int m_Attack_Sound = -1;
	int m_Hurt_Sound = -1;
};

