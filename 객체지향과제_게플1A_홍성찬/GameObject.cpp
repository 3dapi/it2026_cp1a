
#include <iostream>
#include <cmath>
#include "CApplication.h"
#include "GameManager.h"
#include "TextureManager.h"
#include "GameObject.h"

extern TextureManager g_textureManager;
extern GameManager g_gameManager;

GameObject::GameObject()
{
	m_pos = { 0, 0 };
	m_collider = { 0, 0 };
	m_tag = Tag::None;
	m_isActive = true;
	m_isTrigger = false;

	m_name = "";
	m_image.scaling = { 1, 1 };
	m_image.texture = -1;
	m_image.alphaOption = 1;
}

GameObject::~GameObject()
{
}

int GameObject::Init(TextureType textureId)
{
	m_image.texture = g2_TextureLoad(g_textureManager.m_textureFiles[textureId]);

	return 0;
}

int GameObject::Destroy()
{
	g2_TextureRelease(m_image.texture);

	return 0;
}

void GameObject::SetColliderSize()
{
	int nTx = m_image.texture;

	m_collider.height = g2_TextureHeight(nTx) * m_image.scaling.y;
	m_collider.width = g2_TextureWidth(nTx) * m_image.scaling.x;
}

void GameObject::BeginCollisionUpdate()
{
	m_previousColliders = std::move(m_colliders);
	m_colliders.clear();
}

void GameObject::AddCollider(GameObject* other, CollisionDirection direction)
{
	if (m_colliders.find(other) != m_colliders.end())
		return;

	CollisionInfo info;

	info.other = other;
	info.collisionDir = direction;

	m_colliders[other] = info;
}

void GameObject::ProcessCollision()
{
	for (const auto& collider : m_colliders)
	{
		if (m_previousColliders.find(collider.first) == m_previousColliders.end())
			OnCollisionEnter(collider.second);
		else
			OnCollisionStay(collider.second);
	}

	for (const auto& previousCollider : m_previousColliders)
	{
		if (m_colliders.find(previousCollider.first) == m_colliders.end())
			OnCollisionExit(previousCollider.second);
	}
}

void GameObject::SetTexture(const TextureType textureId)
{
	m_image.texture = g2_TextureLoad(g_textureManager.m_textureFiles[textureId]);
}