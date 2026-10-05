#include "Character.h"

void Character::Move(Direction moveDir, float deltaTime)
{
	float moveDistance = m_moveSpeed * deltaTime;

	switch (moveDir)
	{
    case Direction::UP:
        transform.position.y -= moveDistance;
        break;

    case Direction::DOWN:
        transform.position.y += moveDistance;
        break;

    case Direction::LEFT:
        transform.position.x -= moveDistance;
        break;

    case Direction::RIGHT:
        transform.position.x += moveDistance;
        break;

    default:
        break;
	}
}