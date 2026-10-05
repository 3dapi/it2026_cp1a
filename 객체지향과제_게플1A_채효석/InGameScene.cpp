#include "InGameScene.h"

void InGameScene::Init()
{
	SetWindow(false);

	//SetData
	GameData::g_score = 0.0f;
	
	//Audio
	_bgm = g2_SoundLoad("rsc/audio/Glorious Morning.mp3");
	g2_SoundPlay(_bgm, true);

	_correctSFX = g2_SoundLoad("rsc/audio/SFX/correct.mp3");
	_wrongSFX = g2_SoundLoad("rsc/audio/SFX/wrong.mp3");
	_gameOverSFX = g2_SoundLoad("rsc/audio/SFX/GameOver.mp3");

	//font
	_fonts.push_back(g2_FontCreate("±¼¸²", 24, 0));
	_fonts.push_back(g2_FontCreate("±¼¸²", 48, 0));
	_fonts.push_back(g2_FontCreate("±¼¸²", 126, 0));
	
	//obj instance
	_cat = new Cat(VEC2{ (1280 / 2 ) - 128,350 });

	_blueFlag = new Flag(VEC2{ 440,470 }, E_FlagColorType::BLUE);
	_whiteFlag = new Flag(VEC2{ 720,470 }, E_FlagColorType::WHITE);

	_bar = new ProgressBar(VEC2{ 370,15 });

	_objs.push_back(_cat);
	_objs.push_back(_blueFlag);
	_objs.push_back(_whiteFlag);
	_objs.push_back(_bar);

	_heartFull = new Texture("rsc/imgs/Heart/Full.png",{0, 0});
	_heartFull->Load();
	_heartBlank = new Texture("rsc/imgs/Heart/Blank.png",{0, 0});
	_heartBlank->Load();


	//Register Input
	_inputMgr.RegisterAction
	(
		{ VK_LEFT,'A' }, 
		[=]()
		{
			_blueFlag->ChangeFlag();
		}
	);
	_inputMgr.RegisterAction
	(
		{ VK_RIGHT,'D' },
		[=]()
		{
			_whiteFlag->ChangeFlag();
		}
	);

	_inputMgr.RegisterAction
	(
		{ VK_ESCAPE },
		[=]()
		{
			_gameOver = true;
		}
	);

	NextCommand();

	return;
}
void InGameScene::Render()
{
	IScene::Render();
	
	//Objs
	for (auto* i : _objs)
		i->Render();


	//Font
	if (!_gameOver)
	{
		//comm
		g2_FontDrawText
		(
			_fonts[2],
			{ 250,150,1280,300 },
			0xFF000000,
			_commText.c_str());
	}
	
	//Time
	g2_FontDrawText
	(
		_fonts[0],
		{ 550,50,890,90 },
		0xFFFFFFFF,
		"Time Left : %.1f", _remainCommandTime
	);

	//Score

	g2_FontDrawText
	(
		_fonts[2],
		{ 1050,40,1260,200 },
		0xFF000000,
		"%d", (int)_score
	);

	g2_FontDrawText
	(
		_fonts[1],
		{ 1080,200,1260,400 },
		0xFF000000,
		"X %.1f", _mult
	);


	//Life
	for (int i = 0; i < MAX_LIFE; ++i)
	{
		Texture* heart = (i < _life) ? _heartFull : _heartBlank;

		heart->SetPos({ 50.0f + i * 50.0f,40.0f });
		heart->Print();
	}

	g2_FontDrawText
	(
		_fonts[0],
		{ 20, 650,500,700},
		0xFF000000,
		"ESC : Á¾·á / <- : Ã»±â / -> : ¹é±â"
	);


	//Á¾·á
	if (_gameOver)
	{
		g2_FontDrawText
		(
			_fonts[2],
			{ 300, 100, 1200, 220 },
			0xFFFFFFFF,
			"GAME OVER"
		);

		return;

	}

	return;
}
void InGameScene::Update()
{
	IScene::Update();
	float delta = g_deltaTimer.GetDeltaTime();


	if (_gameOver)
	{
		g2_SoundPlay(_gameOverSFX, false);

		_gameOverTimer += delta;

		if (_gameOverTimer >= GAME_OVER_WAIT_TIME)
		{
			JumpScareScene* nextScene = new JumpScareScene();
			g_SceneMgr.ChangeScene(nextScene, E_SceneType::JUMP_SCARE);
		}
		//g_SceneMgr.ChangeScene();
		return;
	}

	//Times


	_gameTime += delta;
	_remainCommandTime -= delta;

	//Input
	_inputMgr.GetKeyDown();

	//Obj
	for (auto* i : _objs)
		i->Update(delta);

	//Time Á¾·á
	if (_remainCommandTime < 0.0f)
	{
		if (CheckAnswer())
		{
			_combo++;
			_mult = 1.0f + (_combo / 5) * .5f;
			_score += _mult;

			if (!(_combo % 10)
				&& _life < MAX_LIFE)
				_life++;

			//Sound
			g2_SoundPlay(_correctSFX, false);

			//bg
			SetWindowColor(0xFF00FF00);

			_bgRemainColTime = _bgColTime;

			//cat
			_cat->SetState(E_StateType::CORRECT);

		}
		else
		{
			_combo = 0;
			_mult = 1.0f;
			_life--;

			g2_SoundPlay(_wrongSFX, false);

			//bg
			SetWindowColor(0xFFFF0000);

			_bgRemainColTime = _bgColTime;

			//cat
			_cat->SetState(E_StateType::WRONG);
		}
		if (_life <= 0)
		{
			_gameOver = true;
			return;
		}

		NextCommand();
	}

	if (_bgRemainColTime > 0.0f)
	{
		_bgRemainColTime -= delta;

		if (_bgRemainColTime <= 0.0f)
		{
			_bgRemainColTime = 0.0f;
			SetWindowColor(_bgDefCol);

			//cat
			_cat->SetState(E_StateType::IDLE);
		}
	}
	


	return;
}

void InGameScene::Destroy()
{
	GameData::g_score = _score;


	for (auto* i : _objs)
		delete i;
	_objs.clear();
	
	_blueFlag = nullptr;
	_whiteFlag = nullptr;
	_bar = nullptr;


	g2_SoundRelease(_bgm);
	g2_SoundRelease(_correctSFX);
	g2_SoundRelease(_wrongSFX);

	return;
}

void InGameScene::NextCommand()
{

	Randomizer randSys;

	int comm = randSys.Rand(0, 3);

	_command = static_cast<E_Command>(comm);

	_commandTime = GetCommandLimitTime();

	_remainCommandTime = _commandTime;

	_bar->SetTime(_commandTime);

	GiveCommand();
}

float InGameScene::GetCommandLimitTime()
{
	float time = 5.0f - (_gameTime * 0.01f);

	if (time < _minComTime)
		time = _minComTime;

	return time;
}

bool InGameScene::CheckAnswer()
{
	switch (_command)
	{
	case E_Command::BLUE_UP:
		return _blueFlag->IsUp();
	case E_Command::BLUE_DOWN:
		return !_blueFlag->IsUp();
	case E_Command::WHITE_UP:
		return _whiteFlag->IsUp();
	case E_Command::WHITE_DOWN:
		return !_whiteFlag->IsUp();
	}

	return false;
}

void InGameScene::GiveCommand()
{

	Randomizer randSys;
	int rand = randSys.Rand(0, 1);

	_commText = COMMAND_TEXT_LIST[static_cast<int>(_command)][rand];
}
