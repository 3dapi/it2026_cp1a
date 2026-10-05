#pragma once
#include "IScene.h"
#include "InputManager.h"
#include "GameData.h"
#include "InGameScene.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

enum class E_Rank
{
	F,
	E,
	D,
	C,
	B,
	A,
	S
};
//6개

enum class E_ResultState
{
	BEFORE_SHOW, //드럼 재생 대기
	SHOW_RANK, // 랭크 표시 + SFX start
	PLAY_SFX, // SFX 종료 대기
	PLAY_BGM,// BGM 시작
	GET_INPUT // 입력 대기
};


class ResultScene : public IScene
{
private:
	E_ResultState _state = E_ResultState::BEFORE_SHOW;

	//Rank 
	const vector<int> RANK_BY_SCORE
	{
		0,
		50,
		100,
		200,
		500,
		750,
		1000,
	};

	const vector<string> RANK_TEXT_LIST
	{
		"설사",
		"똥",
		"오줌",
		"일반",
		"짱",
		"왕",
		"신"
	};

	E_Rank _rank = E_Rank::F;

	int _font = 0;
	int _rankFont = 0;

	//rank visible
	bool _showRank = false;
	float _drumTimer = .0f;
	const float DRUM_TIME = 4.5f;

	float _waitTimer = .0f;
	const float WAIT_TIME = 2.0f;

	//Input text
	bool _showInputTxt = false;

	//Audio
	//-bgm
	int _bgm = 0;

	//-SFX
	int _drumSFX = 0;
	int _fartSFX = 0;
	int _yaySFX = 0;

	InputManager _inputMgr;
public:
	ResultScene() : IScene(E_SceneType::RESULT)
	{
		_winName = "Result";

		_winPos = 
		{
			(GetSystemMetrics(SM_CXSCREEN) - _winSize.cx) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - _winSize.cy) / 2,
		};

		_winColor = 0xFFFFFFFF;
	}

	void Init() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

private:
	E_Rank GetRank(float score);
};

