#pragma once
#include "glc2d.h"

class Player;

class Enemy
{
protected:
	int attack{};
	int hp{};
	int maxHp{};
	int stage{};
	const int maxStage = 4;
	VEC2 spawnPos = { 512.0f,232.0f };
	bool isDead = false;

public:
	virtual ~Enemy();
	int GetAttack() const;
	int GetHp() const;
	int GetMaxHp() const;
	VEC2 GetPos() const;
	int GetStage() const;
	int GetMaxStage() const;

	void Attack(Player& target);
	void Damage(int damage);
	bool Die();

};

class Slime : public Enemy
{
public:
	Slime();
};
class Goblin : public Enemy
{
public:
	Goblin();
};
class Orc : public Enemy
{
public:
	Orc();
};
class Dragon : public Enemy
{
public:
	Dragon();
};
