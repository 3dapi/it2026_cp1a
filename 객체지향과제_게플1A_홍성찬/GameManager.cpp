#include <iostream>
#include <unordered_map>
#include "GameManager.h"
#include "GameObject.h"
#include "Entity.h"

int GameManager::m_nextId = 0;

VEC2 GameManager::m_gravity = { 0, 2000.0f };

GameManager::GameManager()
{
	m_map = { 0 };
}

GameManager::~GameManager()
{
}

int GameManager::UpdateAll(float deltaTime)
{
	CheckCollision();

	for (auto& object : m_gameObjects)
	{
		GameObject* gameObject = object.second;

		if (gameObject->IsActive())
		{
			gameObject->Update(deltaTime);
		}
	}

	return 0;
}

int GameManager::RenderAll()
{
	m_backgrounds[m_currentBackgroundType]->Render();

	for (auto& object : m_gameObjects)
	{
		GameObject* gameObject = object.second;

		if (gameObject->IsActive())
		{
			gameObject->Render();
		}
	}

	return 0;
}

int GameManager::ClearAll()
{
	for (auto& object : m_gameObjects)
	{
		delete object.second;
		object.second = nullptr;
	}

	m_gameObjects.clear();

	m_nextId = 0;

	return 0;
}

void GameManager::CheckCollision()
{
	for (const auto& object : m_gameObjects)
		object.second->BeginCollisionUpdate();

	for (auto object1 = m_gameObjects.begin(); object1 != m_gameObjects.end(); ++object1)
	{
		if (object1->second == nullptr || !object1->second->IsActive())
			continue;

		auto object2 = object1;
		++object2;

		for (; object2 != m_gameObjects.end(); ++object2)
		{
			if (object2->second == nullptr || !object2->second->IsActive())
				continue;

			CheckAABBCollision(object1->second, object2->second);
		}
	}

	for (const auto& object : m_gameObjects)
	{
		if (object.second != nullptr)
			object.second->ProcessCollision();
	}
}

bool GameManager::CheckAABBCollision(GameObject* a, GameObject* b)
{
	if (a->GetRight() <= b->GetLeft() || a->GetLeft() >= b->GetRight())
		return false;

	if (a->GetBottom() <= b->GetTop() || a->GetTop() >= b->GetBottom())
		return false;

	float overlapX = GetMin(a->GetRight(), b->GetRight()) - GetMax(a->GetLeft(), b->GetLeft());
	float overlapY = GetMin(a->GetBottom(), b->GetBottom()) - GetMax(a->GetTop(), b->GetTop());

	float aCenterX = (a->GetLeft() + a->GetRight()) * 0.5f;
	float bCenterX = (b->GetLeft() + b->GetRight()) * 0.5f;
	float aCenterY = (a->GetTop() + a->GetBottom()) * 0.5f;
	float bCenterY = (b->GetTop() + b->GetBottom()) * 0.5f;

	if (overlapY < overlapX)
	{
		if (aCenterY < bCenterY)
		{
			a->AddCollider(b, CollisionDirection::Bottom);
			b->AddCollider(a, CollisionDirection::Top);
		}
		else
		{
			a->AddCollider(b, CollisionDirection::Top);
			b->AddCollider(a, CollisionDirection::Bottom);
		}
	}
	else
	{
		if (aCenterX < bCenterX)
		{
			a->AddCollider(b, CollisionDirection::Right);
			b->AddCollider(a, CollisionDirection::Left);
		}
		else
		{
			a->AddCollider(b, CollisionDirection::Left);
			b->AddCollider(a, CollisionDirection::Right);
		}
	}

	return true;
}