#include "TitleScene.h"


void TitleScene::Init()
{
	IScene::Init();

	//audio
	_bgm = g2_SoundLoad("rsc/audio/Jumper.mp3");
	g2_SoundPlay(_bgm, true);


	//font
	nFont = g2_FontCreate("굴림", 48, 0);

	//input 등록
	_inputMgr.RegisterAction
	(
		{VK_SPACE},
		[=]() 
		{
			HowToPlayScene* nextScene = new HowToPlayScene();
			g_SceneMgr.ChangeScene(nextScene, E_SceneType::HOW_2_PLAY);
		}
	);

	VEC2 zero = { 0,0 };

	string prefix = "rsc/imgs/cats/";
	vector<Texture*>texes(10);

	for (int i = 0; i < texes.size(); ++i)
	{
		texes[i] = new Texture(prefix + std::to_string(i) + ".png",zero);
		texes[i]->Load();

		_textures.push_back(texes[i]);
	}

	_background->Load();

	return;
}

void TitleScene::Update()
{
	_inputMgr.GetKeyDown();



	_blinkTimer += 0.016f;

	if (_blinkTimer >= 10.0f)
	{
		_blinkTimer = 0.0f;
		_showText = !_showText;
	}

	_colTime += 0.016f;

	if (_colTime >= 0.1f)
	{
		_colTime = 0;

		switch (_colorDir)
		{
		case 0:
			_g++;
			if (_g >= 255) _colorDir++;
			break;

		case 1:
			_r--;
			if (_r <= 0) _colorDir++;
			break;

		case 2:
			_b++;
			if (_b >= 255) _colorDir++;
			break;

		case 3:
			_g--;
			if (_g <= 0) _colorDir++;
			break;

		case 4:
			_r++;
			if (_r >= 255) _colorDir++;
			break;

		case 5:
			_b--;
			if (_b <= 0) _colorDir = 0;
			break;
		}

		_color = 0xFF000000 | (_r << 16) | (_g << 8) | _b;
	}

	//텍스쳐 랜덤 이동
	Randomizer randSys;

	_texTimer += 0.016f;
	if (_texTimer >= TEXTURE_WAIT_TIME)
	{
		_texTimer = 0.0f;

		for (auto* texture : _textures)
		{
			VEC2 rnPos;
			rnPos.x = randSys.Rand(0, _winSize.cx);
			rnPos.y = randSys.Rand(0, _winSize.cy);
			texture->SetPos(rnPos);
		}
	}


	return;
}

void TitleScene::Render()
{
	IScene::Render();

	Randomizer randSys;

	_background->Print();

	for (auto* texture : _textures) texture->Print();



	if(_showText)
		g2_FontDrawText(nFont, { 380,500,1000,800 }, _color, "SPACE 를 눌러 게임시작");

	return;
}

void TitleScene::Destroy()
{
	delete _background;
	_background = nullptr;

	for (auto& texture : _textures)
	{
		delete texture;
		texture = nullptr;
	}

	_textures.clear();

	g2_SoundRelease(_bgm);
	_bgm = 0;

	return;
}