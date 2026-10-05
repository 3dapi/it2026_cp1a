#pragma once
#include <unordered_map>
#include "GameObject.h"

class Entity : public GameObject
{
protected:
	VEC2 m_velocity;
	int m_hp;
	bool m_onGround;

	void ResolveCollision(const CollisionInfo& info);

public:
	Entity();
	~Entity() override;

	bool m_collisionObstacle;

	bool IsOnGround() const
	{
		for (const auto& collide : m_colliders)
		{
			if (collide.second.collisionDir == CollisionDirection::Bottom)
				return true;
		}

		return false;
	}

	int Update(float deltaTime) override;
	int Render() override;

	void OnCollisionEnter(const CollisionInfo& info) override;
	void OnCollisionStay(const CollisionInfo& info) override;
	void OnCollisionExit(const CollisionInfo& info) override;

	VEC2 GetVelocity() const { return m_velocity; };
	void SetVelocity(const VEC2& v) { m_velocity = v; };
};