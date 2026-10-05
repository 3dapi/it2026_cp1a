#pragma once
#include "IScene.h"
#include "Texture.h"
#include "ResultScene.h"

class JumpScareScene : public IScene
{
private:
	float _timer = .0f;

	bool _trigger = false;

	const float JUMP_SCARE_TIME = 2.0f;
	const float SCENE_CHANGE_TIME = .2f;

	Texture* _img = new Texture("rsc/imgs/Cats/UnCanny.png", VEC2(300, 0));

	int _sfx = 0;

public:
	JumpScareScene() : IScene(E_SceneType::JUMP_SCARE)
	{
		_winSize = 
		{
			GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN)
		};

	}

	void Init() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

};

