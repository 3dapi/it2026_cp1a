#pragma once
#include "Window.h"
#include "WindowImage.h"
#include "Battle/Battle.h"
#include "Battle/Character.h"
#include "Battle/Dice.h"
typedef int sprite;

class SceneBattle
{
public:
	void Initialize();
	void InitializeImageLoad();
	void InitializeObject();
	//void Run();

	//void Destroy();
public:
	sprite m_background{};


	sprite m_iconNone{};
	sprite m_iconNone2{};
	sprite m_iconAttack{};
	sprite m_iconAvoid{};
	sprite m_iconGuard{};

	sprite m_playerAttack{};
	sprite m_playerAvoid{};
	sprite m_playerCorpse{};
	sprite m_playerGuard{};
	sprite m_playerIdle{};

	sprite m_enemyAttack{};
	sprite m_enemyAvoid{};
	sprite m_enemyCorpse{};
	sprite m_enemyGuard{};
	sprite m_enemyIdle{};
public:
	Dice m_dice{};
	Character m_player{};
	Character m_enemy{};
	Battle m_battle{};

	WindowImage m_backgroundObject{};
	WindowImage m_playerObject{};
	WindowImage m_enemyObject{};
	WindowImage m_playerActionObject{};
	WindowImage m_enemyActionObject{};
};

