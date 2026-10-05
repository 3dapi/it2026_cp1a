#pragma once
#include "IScene.h"
#include "Texture.h"
#include "InputManager.h"
#include "InGameScene.h"

class HowToPlayScene : public IScene
{
private:
	Texture* _img = new Texture("rsc/imgs/HowToPlay.png", VEC2(0, 0));

	float _timer = .0f;
	const float WAIT_TIME = 2.5f;

	int _font = 0;
	bool _showText = false;
	
	InputManager _inputMgr;
public:
	HowToPlayScene() : IScene(E_SceneType::HOW_2_PLAY)
	{
		_winName = "How to Play";
	}

	void Init() override;
	void Update() override;
	void Render() override;

};

