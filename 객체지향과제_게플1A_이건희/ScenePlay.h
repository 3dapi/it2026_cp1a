#pragma once
#include "glc2d.h"
#include "SceneBegin.h"
#include <vector>

class ScenePlay
{
public:
	int Init();
	int Destroy();
	int Render();
	int Update();
protected:
	int player = -1;
	int apple = -1;

	int hit = -1;
protected:
	// 충돌처리용 플레이어 크기
	float playerWidth = 60.0f;
	float playerHeight = 100.0f;

	// 충돌처리용 사과 크기
	float appleWidth = 40.0f;
	float appleHeight = 60.0f;
protected:
	// 플레이어	위치 / 크기 / 속도
	VEC2 playerPos = { 350.0f, 530.0f };
	VEC2 playerScale = { 0.5f, 0.5f };
	float playerSpeed = 0.3;
	// 벽 이동제한
	float minX = -10.0f;
	float maxX = 750.0f;
protected:
	// 사과 이미지 크기
	VEC2 appleScale = { 0.4f, 0.4f };
	// 사과	리스트 / 속도 / 쿨타임 타이머 / 스폰 쿨타임
	std::vector<VEC2> applePositions;
	float appleSpeed = 0.2f;
	int spawnCounter = 0;
	int spawnCooldown = 1500;
public:
	// 점수	(피한 사과의 개수)
	static int score;
};