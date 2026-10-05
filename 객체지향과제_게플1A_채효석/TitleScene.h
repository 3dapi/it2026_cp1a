#pragma once
#include <glc2d.h>
#include "IScene.h"
#include "HowToPlayScene.h"
#include "Texture.h"
#include "Randomizer.h"
#include "InputManager.h"

#include <vector>
using std::vector;

class TitleScene : public IScene
{
private:
	int _bgm = 0;

	vector<Texture*> _textures;
	float _texTimer = 0.0f;
	const float TEXTURE_WAIT_TIME = 1.5f;

	Texture* _background = new Texture("rsc/imgs/MainMenu.png", VEC2(0, 0));

	//text
	int nFont = 0;
	float _blinkTimer = .0f;
	bool _showText = true;

	//text-col

	float _colTime = 0.0f;
	DWORD _color = 0xFFFFFFFF;

	int _r = 255;
	int _g = 0;
	int _b = 0;
	int _colorDir = 0;


	//Input
	InputManager _inputMgr;
public :
	TitleScene() : IScene(E_SceneType::TITLE)
	{
		_winName = "Title 창";
		_winColor = 0x000000; // 검은색
	}
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Destroy() override;

};

