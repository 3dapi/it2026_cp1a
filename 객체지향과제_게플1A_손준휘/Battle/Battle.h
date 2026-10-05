#pragma once
#include "Battle.h"
#include "Character.h"
#include "Dice.h"
typedef enum COMMAND
{
	CHARACTERINFO=0,
	BROADCAST,
	SETTURN,
	ATTACK,
	DEFENCE,
	DAMAGESTEP,
	ENDPHASE,
	DEFENCE_GUARD = DEFENCE+100000,
	DEFENCE_AVOID = DEFENCE + 200000,
}COMMAND;

class Battle
{
public:

	void Setup(Character* player, Character* enemy);
	
	bool BattleMain();

	void SceneCharacterInfo();
	void SceneBroadCast(const unsigned int round);

		void SceneSetTurn(Character** attackerPP, Character** defenderPP);
		
		int SceneAtk(Character* attackerP);
		
		COMMAND SceneDefence(Character* defenderP, int powerAtk);//isAlive return
			int SceneGuard(Character* defenderP, int powerAtk);	// 공격 위력 - 수비 위력 반환.
			bool SceneAvoid(Character* defenderP, int powerAtk);	// 회피 성공 여부 리턴.
		bool SceneDamageStep(Character* attackerP, Character* defenderP, COMMAND inputCommand, int powerAtk);
public:
	COMMAND stateCurrent{};

	Character* attackerP{};
	Character* defenderP{};
	unsigned int round{};
	int powerAttack{};
	COMMAND inputCommand{};
	bool isDefenderAlive{};

	bool m_isAllayTurn{ true };
	Character* m_playerP{};
	Character* m_enemyP{};
};
