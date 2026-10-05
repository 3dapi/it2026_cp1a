#pragma once
#include "glc2d.h"

struct Transform
{
	VEC2 position{};
	VEC2 scale{ 1.0f, 1.0f };
	VEC2 center{};
	float rotation{};
};

struct BoxCollider
{
	VEC2 size{};
};

class GameObject
{
public:
	virtual int Init() { return 0; }
	virtual int Update(float deltaTime) { return 0; }
	virtual int Destroy() { return 0; }
	virtual int Render() { return 0; }

public:
	VEC2 GetCenter() const;
	float GetRotation() const;
	RECT GetCollider() const;

public:
	Transform transform;

protected:
	BoxCollider boxCollider;

};

