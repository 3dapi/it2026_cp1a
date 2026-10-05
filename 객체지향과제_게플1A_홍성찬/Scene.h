#pragma once
#include <string>
class Scene
{
public:
	virtual int Init();
	virtual int Update(float deltaTime);
	virtual int Render();
	virtual int Destroy();
	virtual ~Scene() {}

	std::string m_sceneName;
};