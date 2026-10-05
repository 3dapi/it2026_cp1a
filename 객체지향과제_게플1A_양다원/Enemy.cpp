#include "Enemy.h"
#include "glc2d.h"
#include "Player.h"

#include "stdio.h";

Enemy::~Enemy()
{
}

int Enemy::GetAttack() const
{
	return attack;
}

int Enemy::GetHp() const
{
	return hp;
}

int Enemy::GetMaxHp() const
{
	return maxHp;
}

VEC2 Enemy::GetPos() const
{
	return spawnPos;
}

int Enemy::GetStage() const
{
	return stage;
}
int Enemy::GetMaxStage() const
{
	return maxStage;
}
void Enemy::Attack(Player& target)
{
	target.TakeDamage(attack);
	printf("플레이어에게 %d만큼 피해가함 \n", attack);
}

void Enemy::Damage(int damage)
{
	hp -= damage;
	if (hp <= 0)
		hp = 0;
}

bool Enemy::Die()
{
	if (hp <= 0)
		return isDead = true;
	return isDead = false;
}

Slime::Slime()
{
	hp = 7;
	maxHp = 7;
	attack = 1;
	stage = 1;
	printf("슬라임 소환");
}

Goblin::Goblin()
{
	hp = 12;
	maxHp = 12;
	attack = 1;
	stage = 2;
	printf("고블린 소환");
}

Orc::Orc()
{
	hp = 17;
	maxHp = 17;
	attack = 1;
	stage = 3;
	printf("오크 소환");
}
Dragon::Dragon()
{
	hp = 35;
	maxHp = 35;
	attack = 2;
	stage = 4;
	printf("드래곤 소환");

	spawnPos = {448.0f, 130.0f};
}