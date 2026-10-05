#pragma once
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <iostream>
#include "glc2d.h"
#include "GameObject.h"
#include "Background.h"

inline float GetMax(float a, float b)
{
	return a > b ? a : b;
}

inline float GetMin(float a, float b)
{
	return a > b ? b : a;
}

inline float Clamp(float value, float min, float max)
{
	return GetMin(GetMax(value, min), max);
}

struct Map
{
	float right;
	float left;
	float bottom;
	float top;
};

class GameManager
{
private:
	std::unordered_map<BackgroundType, GameObject*> m_backgrounds;
	std::unordered_map<int, GameObject*> m_gameObjects;
	static VEC2 m_gravity;
	static int m_nextId;

	Map m_map;

public:
	GameManager();
	~GameManager();

	BackgroundType m_currentBackgroundType;
	int m_score = 0;

	int UpdateAll(float deltaTime);
	int RenderAll();
	int ClearAll();

	VEC2 GetGravity() const { return m_gravity; };

	template<typename T>
	T* CreateObject()
	{
		static_assert(std::is_base_of<GameObject, T>::value, "T must inherit GameObject");

		T* newObj = new T;
		int id = m_nextId++;

		newObj->m_id = id;
		m_gameObjects[id] = newObj;

		return newObj;
	}

	Background* CreateBackground(BackgroundType type)
	{
		Background* newObj = new Background;
		m_backgrounds[type] = newObj;

		return newObj;
	}

	void CheckCollision();

	/// <summary>
	/// AABB 알고리즘을 이용하여 충돌 여부를 점검하고 충돌체를 배열에 삽입한다.
	/// </summary>
	bool CheckAABBCollision(GameObject* a, GameObject* b);
};