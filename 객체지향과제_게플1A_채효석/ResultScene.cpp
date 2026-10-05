#include "ResultScene.h"

void ResultScene::Init()
{
	SetWindow(true);

	_inputMgr.RegisterAction
	(
		{ VK_SPACE },
		[=]()
		{
			InGameScene* nextScene = new InGameScene();
			g_SceneMgr.ChangeScene(nextScene, E_SceneType::IN_GAME);
		}
	);


	_font = g2_FontCreate("굴림", 48, 0);
	_rankFont = g2_FontCreate("궁서", 100, 0);

	_rank = GetRank(GameData::g_score);

	//audio
	_bgm = g2_SoundLoad("rsc/audio/Result.mp3");
	_drumSFX = g2_SoundLoad("rsc/audio/SFX/drum.mp3");
	_fartSFX = g2_SoundLoad("rsc/audio/SFX/fart.mp3");
	_yaySFX = g2_SoundLoad("rsc/audio/SFX/yay.mp3");

	_state = E_ResultState::BEFORE_SHOW;
}

void ResultScene::Update()
{
	float dt = g_deltaTimer.GetDeltaTime();

	switch (_state)
	{
	case E_ResultState::BEFORE_SHOW:
	{
		_drumTimer += dt;
		//drum
		if (_drumTimer > DRUM_TIME)
		{
			_showRank = true;
			_state = E_ResultState::SHOW_RANK;
		}

	}break;

	case E_ResultState::SHOW_RANK:
	{

		if (static_cast<int>(_rank) < static_cast<int>(E_Rank::C))
			g2_SoundPlay(_fartSFX, false);
		else
			g2_SoundPlay(_yaySFX, false);

		_waitTimer = .0f;
		_state = E_ResultState::PLAY_SFX;

	} break;
	case E_ResultState::PLAY_SFX:
	{
		_waitTimer += dt;

		if (_waitTimer > WAIT_TIME)
		{
			_state = E_ResultState::PLAY_BGM;
		}

	} break;
	case E_ResultState::PLAY_BGM:
	{
		g2_SoundPlay(_bgm, true);

		_showInputTxt = true;
		
		_state = E_ResultState::GET_INPUT;

	}break;
	case E_ResultState::GET_INPUT:
	{
		_inputMgr.GetKeyDown();

	}break;
	}
}


void ResultScene::Render()
{
	g2_FontDrawText(_font, { 380,200,1000,400}, 0xFF000000, "당신의 랭크는...");

	if (_showRank)
	{
		g2_FontDrawText
		(
			_rankFont,
			{ 500, 300, 800, 500 },
			0xFF000000,
			RANK_TEXT_LIST[static_cast<int>(_rank)].c_str()
		);
	}

	if (_showInputTxt)
	{
		g2_FontDrawText
		(
			_font,
			{ 380, 500, 1000, 800 },
			0xFF000000,
			"SPACE를 눌러 다시 시작"
		);
	}


}

void ResultScene::Destroy()
{
	g2_SoundRelease(_bgm);
	g2_SoundRelease(_drumSFX);
	g2_SoundRelease(_fartSFX);
	g2_SoundRelease(_yaySFX);
}


E_Rank ResultScene::GetRank(float score)
{
	for (int i = static_cast<int>(E_Rank::S);
		i >= static_cast<int>(E_Rank::F); --i)
		if (score >= RANK_BY_SCORE[i])
			return static_cast<E_Rank>(i);

	return E_Rank::F;
}

