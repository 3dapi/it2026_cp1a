#pragma once
#include "Player.h"
#include "Enemy.h"

class CApplication;

class SceneGamePlay
{
public:
	int Init();
	int Update(CApplication& cApp);
	int Render();
	int Destroy();

	bool InputSpace();

private:	
	void Battle(Enemy* _enemy);
	void ChangeStage(Enemy* _enemy);
	void ChangeEnemy(Enemy* _enemy);
	void BossCombat(Enemy* _enemy);
	void CombatManager(Enemy* _enemy);
	void BossClear();
	void EnemyTakeDamage(Enemy* _enemy);
	void TextureLoad();
	void TextureRelease();


	Player* player = nullptr;
	Enemy* enemy = nullptr;
	float s_cursorX{}; //플레이어가 공격 시 커서 위치 저장
	VEC2 enemyPos{};
	int stage{};
	int nextStage{};

	bool _isWin = false;
	int combatFont = -1;
	RECT playerHp{10,10,230,60};
	RECT enemyHp{ 580,230,780,330 };
	RECT bossHp{580,102,780,162};
	RECT stagePos{530,10,820,60};

	///받은데미지, 가한 데미지 판정 표시 (안쓰면 삭제)
	int attackFont = -1;
	RECT attackPos{ 440,540,840,590 };
	RECT damagePos{ 720,320,820,365 };
	///

	int escButton = -1;
	VEC2 escScreenPos{ 290.0f,180.0f };
	const KEYCODE* pKeyboard = nullptr;
	//게임종료, 다시시작, 마저하기
	RECT gameExitPos{ 540,350,760,400 };
	RECT gameReplayPos{ 540,290,760,340 };
	bool _isInputEsc = false;

	float count = 0.0f;
	float _playTime{};
};
