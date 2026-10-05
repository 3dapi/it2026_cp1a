#pragma once
#include <vector>
#include "GameObject.h"

class Obstacle : public GameObject
{
private:
	VEC2 m_localPos;
	float m_moveSpeed;

public:
	Obstacle();
	~Obstacle() override;

	int Update(float deltaTime) override;
	int Render() override;

	float GetMoveSpeed() const { return m_moveSpeed; };
	void SetMoveSpeed(const float& moveSpeed) { m_moveSpeed = moveSpeed; };
};