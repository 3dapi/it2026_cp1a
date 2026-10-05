#pragma once
#include "glc2d.h"

class Enemy;


class Player
{
public:
	void TakeDamage(int damage);
	void Attack(float saveCousorX, Enemy& target);

	int GetHP() const;
	int GetMaxHP() const;
	int GetAttack() const;
	bool Die();
	void SetHP(int max);
	void SetSpeed(float speed);

	float MissRange(float x) const;

	const VEC2 gaugePosition{ 290.0f,640.0f };
	VEC2 cursorPosition{ 290.0f,606.0f };

	// 커서 이동 함수
	void CursorMOve(float _dt);

	void DeltaTime();
	float GetDeltaTime() const;

private:
	int currentHp = 3;
	int maxHp = 3;
	int attack{};
	bool isDead = false;

	float gaugeRightX = 985.0f;
	float gaugeLeftX = 295.0f;

	//게이지 색상별 범위
	float NormalRange(float x) const;
	float GoodRange(float x) const;
	float PerfectRange(float x) const;
	void RangeCheck(float x);

	float cursorX = 290.0f;
	int cursorDirection = 1;
	float cursorSpeed = 800.0f;
	float move{};

	long long dt_lt = 0;
	float deltaTime = 0.0f;
};

