#include "GameObject.h"

VEC2 GameObject::GetCenter() const
{
	return { transform.position.x + transform.center.x * transform.scale.x,
			 transform.position.y + transform.center.y * transform.scale.y };
}

float GameObject::GetRotation() const
{
	return transform.rotation * 3.141592f / 180.0f;
}

RECT GameObject::GetCollider() const
{
	VEC2 center = GetCenter();

	float halfWidth = boxCollider.size.x * transform.scale.x / 2.0f;
	float halfHeight = boxCollider.size.y * transform.scale.y / 2.0f;

	return RECT(static_cast<LONG>(center.x - halfWidth),
				static_cast<LONG>(center.y - halfHeight),
				static_cast<LONG>(center.x + halfWidth),
				static_cast<LONG>(center.y + halfHeight));
}