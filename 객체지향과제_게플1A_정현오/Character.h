#pragma once
#include "GameObject.h"

enum class Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
};

class Character : public GameObject
{
protected:
	void Move(Direction moveDir, float deltaTime);

protected:
	Direction m_direction{ Direction::DOWN };
	float m_moveSpeed{ 200.0f };
};