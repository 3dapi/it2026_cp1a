#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

// === SingleTone ===
#include "IScene.h"
#include "InputManager.h"
#include "DeltaTimer.h"

// === Datas ===
#include "Randomizer.h"
#include "GameData.h"

#include "GameObject.h"
// === GameObjs ===
#include "ProgressBar.h"
#include "Flag.h"
#include "Cat.h"

// === Scene ===
#include "JumpScareScene.h"

enum class E_Command
{
	BLUE_UP,
	BLUE_DOWN,
	WHITE_UP,
	WHITE_DOWN
};

class InGameScene : public IScene
{
private:
	//obj
	vector<GameObject*> _objs;

	Flag* _blueFlag = nullptr;
	Flag* _whiteFlag = nullptr;

	Cat* _cat = nullptr;

	//font
	vector<int> _fonts;

	//input
	InputManager _inputMgr;

	//=== Games ===

	//Timer
	  
	float _gameTime = .0f;

	//com time
	float _commandTime = 5.0f;
	float _remainCommandTime = 0.0f;
	const float _minComTime = .5f;

	//bg
	float _bgColTime = 1.0f;
	float _bgRemainColTime = 0.0f;
	DWORD _bgDefCol = 0xE1E1E1;

	//Progress
	ProgressBar* _bar = nullptr;

	//command
	E_Command _command = E_Command::BLUE_DOWN;
	string _commText = "";
	const vector<vector<string>> COMMAND_TEXT_LIST =
	{
		{"청기 올려","청기 내리지마"}, //BlueUp
		{"청기 내려","청기 올리지마"}, //BlueDown
		{"백기 올려","백기 내리지마"}, //WhiteUp
		{"백기 내려","백기 올리지마"} //WhiteDown
	};

	//Score
	float _score = .0f;
	int _combo = 0;
	float _mult = 1.0f;

	//life
	const int MAX_LIFE = 5;
	int _life = MAX_LIFE;

	Texture* _heartFull = nullptr;
	Texture* _heartBlank = nullptr;

	//over
	bool _gameOver = false;
	float _gameOverTimer = .0f;

	const float GAME_OVER_WAIT_TIME = 2.0f;



	//Audio
	int _bgm = 0;
	int _correctSFX = 0;
	int _wrongSFX = 0;
	int _gameOverSFX = 0;

private:
	void NextCommand();
	bool CheckAnswer();

	void GiveCommand();

	float GetCommandLimitTime();

public:
	InGameScene() : IScene(E_SceneType::IN_GAME)
	{
		_winName = "InGame";
		_winColor = 0xE1E1E1;
	}
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Destroy() override;
};

