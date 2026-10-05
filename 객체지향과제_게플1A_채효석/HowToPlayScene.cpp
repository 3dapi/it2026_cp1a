#include "HowToPlayScene.h"

void HowToPlayScene::Init()
{
	SetWindow(false);

	_img->Load();

	_font = g2_FontCreate("굴림", 48, 0);

	_inputMgr.RegisterAction
	(
		{ VK_SPACE },
		[=]()
		{
			InGameScene* nextScene = new InGameScene();
			g_SceneMgr.ChangeScene(nextScene, E_SceneType::IN_GAME);
		}
	);

	return;
}

void HowToPlayScene::Update()
{
	float dt = g_deltaTimer.GetDeltaTime();
	_timer += dt;

	if (_timer >= WAIT_TIME)
	{
		_showText = true;
		_inputMgr.GetKeyDown();
	}

	return;
}

void HowToPlayScene::Render()
{
	_img->Print();

	if(_showText)
		g2_FontDrawText(_font, { 380,500,1000,800 }, 0xFF000000, "SPACE 를 눌러 계속");

	return;
}