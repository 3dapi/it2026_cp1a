#include <iostream>
#include <algorithm>
#include "Entity.h"
#include "GameManager.h"

extern GameManager g_gameManager;

void Entity::ResolveCollision(const CollisionInfo& info)
{
	const GameObject* obj = info.other;

	if (m_isTrigger || obj->IsTrigger())
		return;

	switch (info.collisionDir)
	{
	case CollisionDirection::Bottom:
		m_pos.y = obj->GetTop() - m_collider.height;
		if (m_velocity.y > 0)
			m_velocity.y = 0;
		break;

	case CollisionDirection::Top:
		m_pos.y = obj->GetBottom();
		if (m_velocity.y < 0)
			m_velocity.y = 0;
		break;

	case CollisionDirection::Right:
		m_pos.x = obj->GetLeft() - m_collider.width;
		if (m_velocity.x > 0)
			m_velocity.x = 0;
		break;

	case CollisionDirection::Left:
		m_pos.x = obj->GetRight();
		if (m_velocity.x < 0)
			m_velocity.x = 0;
		break;
	}
}

Entity::Entity()
{
	m_velocity = { 0, 0 };
	m_hp = 0;
}

Entity::~Entity()
{
}

int Entity::Update(float deltaTime)
{
	VEC2 g = g_gameManager.GetGravity();
	m_velocity = m_velocity + deltaTime * g;

	m_pos = m_pos + m_velocity * deltaTime;

	return 0;
}

int Entity::Render()
{
	//g2_DrawAlphaOption(m_image.alphaOption);
	g2_Draw2D(m_image.texture, NULL, &m_pos, &m_image.scaling);

	return 0;
}

void Entity::OnCollisionEnter(const CollisionInfo& info)
{
	if (info.other->GetTag() == Tag::Obstacle)
		m_collisionObstacle = true;

	ResolveCollision(info);
}

void Entity::OnCollisionStay(const CollisionInfo& info)
{
	ResolveCollision(info);
}

void Entity::OnCollisionExit(const CollisionInfo& info)
{

}