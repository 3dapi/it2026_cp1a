#include "Player.h"
#include "glc2d.h"
#include "Enemy.h"

#include "stdio.h"

void Player::TakeDamage(int damage)
{
	currentHp -= damage;
	if (currentHp <= 0)
		currentHp = 0;
}

void Player::Attack(float saveCousorX, Enemy& target)
{
	RangeCheck(saveCousorX); // 공격력 설정
	target.Damage(attack);
	printf("적에게 %d만큼 피해가함 \n", attack);
}

bool Player::Die()
{
	if (currentHp <= 0)
		return isDead = true;
	return isDead = false;
}


void Player::CursorMOve(float _dt)
{
	move = cursorSpeed * cursorDirection * _dt;
	cursorX += move; //방향과 이속만큼
	cursorPosition.x = cursorX;
	if (cursorX >= gaugeRightX)
	{
		cursorX = gaugeRightX;
		cursorPosition.x = cursorX;
		cursorDirection = -1;
	}
	else if (cursorX <= gaugeLeftX)
	{
		cursorX = gaugeLeftX;
		cursorPosition.x = cursorX;
		cursorDirection = 1;
	}
}
void Player::DeltaTime()
{
	long long now = g2_TimeGetTime();
	if (dt_lt == 0) dt_lt = now;
	long long diff = now - dt_lt;
	dt_lt = now;
	float dt = (float)diff / 1000.0f;

	deltaTime = (dt < 0) ? 0.0 : ((dt > 0.05f) ? 0.05f : dt);
}
float Player::GetDeltaTime() const
{
	return deltaTime;
}
int Player::GetHP() const
{
	return currentHp;
}

int Player::GetMaxHP() const
{
	return maxHp;
}

int Player::GetAttack() const
{
	return attack;
}
float Player::MissRange(float x) const
{
	return (x >= 295 && x < 404) || (x >= 876 && x < 985);
}

float Player::NormalRange(float x) const
{
	return (x >= 404 && x < 526) || (x >= 754 && x < 876);
}

float Player::GoodRange(float x) const
{
	return (x >= 526 && x < 610) || (x >= 670 && x < 754);
}

float Player::PerfectRange(float x) const
{
	return (x >= 610 && x < 670);
}

void Player::RangeCheck(float x)
{
	//커서 위치에 따른 공격력 수정
	if (MissRange(x))
		attack = 0;
	else if (NormalRange(x))
		attack = 1;
	else if (GoodRange(x))
		attack = 3;
	else if (PerfectRange(x))
		attack = 5;	
}
void Player::SetHP(int max)
{
	maxHp = max;
	currentHp = maxHp;
}
void Player::SetSpeed(float speed)
{
	cursorSpeed = speed;
}