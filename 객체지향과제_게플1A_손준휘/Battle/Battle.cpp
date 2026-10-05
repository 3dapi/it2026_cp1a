#include <iostream>
#include "MyHeader.h"
#include "Dice.h"
#include "Character.h"
#include "Battle.h"

using std::cout;

void Battle::Setup(Character* player, Character* enemy)
{
	m_playerP = player;
	m_enemyP = enemy;
}

bool Battle::BattleMain()
{
	switch (stateCurrent)
	{
	case(CHARACTERINFO):
	{
		SceneCharacterInfo();

		stateCurrent = BROADCAST;
		break;
	}
	case(BROADCAST):
	{
		SceneBroadCast(++round);

		stateCurrent = SETTURN;
		break;
	}
	case(SETTURN):
	{
		SceneSetTurn(&attackerP, &defenderP);

		stateCurrent = ATTACK;
		break;
	}
	case(ATTACK):
	{
		SceneAtk(attackerP);

		stateCurrent = DEFENCE;
		break;
	}
	case(DEFENCE):
	{
		SceneDefence(defenderP, powerAttack);

		stateCurrent = DAMAGESTEP;
		break;
	}
	case(DAMAGESTEP):
	{
		SceneDamageStep(attackerP, defenderP, inputCommand, powerAttack);

		stateCurrent = ENDPHASE;
		break;
	}
	case(ENDPHASE):
	{
		if (!isDefenderAlive)
		{
			if (0 == m_playerP->GetHpCurrent())
			{
				Messege("You lose...\n");
				return true;
			}
			else
			{
				Messege("You win!\n");
				return false;
			}
		}

		stateCurrent = BROADCAST;
		break;
	}
	default:
	{
		break;
	}
	}

	return true;
}

void Battle::SceneCharacterInfo()
{
	m_playerP->ShowName();
	m_playerP->ShowHp();
	m_playerP->ShowStatus();
	Messege("\n");
	m_enemyP->ShowName();
	m_playerP->ShowHp();
	m_enemyP->ShowStatus();
	Messege("battle start\n");
	Messege("=====\n");

}

void Battle::SceneBroadCast(const unsigned int round)
{
	std::cout << "round " << round << '\n';

	Character* ptr{ m_playerP };
	ptr->ShowName();
	ptr->ShowHp();

	ptr= m_enemyP;
	ptr->ShowName();
	ptr->ShowHp();
}

void Battle::SceneSetTurn(Character** attackerPP, Character** defenderPP)
{
	if (m_isAllayTurn)
	{
		Messege("your turn\n");
		*attackerPP = m_playerP;
		*defenderPP = m_enemyP;
	}
	else
	{
		Messege("Enemy turn\n");
		*attackerPP = m_enemyP;
		*defenderPP = m_playerP;
	}
}

int Battle::SceneAtk(Character* attackerP)
{
	int powerAttack{ attackerP->Attack() };

	if(m_isAllayTurn)
	{

		//InputString("공격하려면 확인을 눌러주세요.");
		Messege("공격하려면 확인을 눌러주세요.");
	}

	std::cout << "attack power : " << powerAttack << '('<<ToSignedNumber(attackerP->GetAtk())<<')' << '\n';

	return powerAttack;
}

COMMAND Battle::SceneDefence(Character* defenderP, int powerAtk)
{
	if (m_isAllayTurn)
	{
		if (powerAtk <= defenderP->GetDr() / 2 + defenderP->GetDex())
		{
			std::cout << defenderP->GetName() << " chosed avoid\n";
			return DEFENCE_AVOID;
		}
		else
		{
			std::cout << defenderP->GetName() << " chosed guard\n";
			return DEFENCE_GUARD;
		}
	}
	else
	{
		Messege("Chose deffence type.\n");
		std::cout << DEFENCE_GUARD << " : guard\n";
		std::cout << DEFENCE_AVOID << " : avoid\n";

		while (true)
		{
			Messege("Input : ");

			COMMAND inputCommand = static_cast<COMMAND>(InputInt());

			switch (inputCommand)
			{
			case(DEFENCE_GUARD):
			{
				return DEFENCE_GUARD;
			}
			case(DEFENCE_AVOID):
			{
				return DEFENCE_AVOID;
			}
			default:
			{
				Messege("Wrong input, please try again\n");
				continue;
			}
			}
		}
	}
}

int Battle::SceneGuard(Character* defenderP, int powerAtk)
{
	int powerGuard{ defenderP->Guard() };
	int powerFine = powerAtk - powerGuard;
	
	std::cout << "Guard power : " << powerGuard <<'(' << ToSignedNumber(defenderP->GetDef()) <<')'<< '\n';
	if (powerFine <= CHARACTER_GUARD_POWER_MIN)
	{
		Messege("Minimum damage!\n");
		powerFine = CHARACTER_GUARD_POWER_MIN;
	}

	return powerFine;
}

bool Battle::SceneAvoid(Character* defenderP, int powerAtk)
{
	int powerAvoid{ defenderP->Avoid() };

	std::cout <<"Avoid power : " << powerAvoid <<'('<< ToSignedNumber(defenderP->GetDex()) <<')'<< '\n';
	if (powerAvoid >= powerAtk)
	{
		Messege("Avoid success!\n");
		return true;
	}
	else
	{
		Messege("Avoid Failed...\n");
		return false;
	}
}

bool Battle::SceneDamageStep(Character* attackerP, Character* defenderP,COMMAND inputCommand,int powerAtk)
{
	int powerFine{powerAtk};
	switch (inputCommand)
	{
	case(DEFENCE_GUARD):
	{
		powerFine = SceneGuard(defenderP, powerAtk);
		break;
	}
	case(DEFENCE_AVOID):
	{
		bool isAvoided{ SceneAvoid(defenderP,powerAtk) };

		if (isAvoided)
		{
			m_isAllayTurn = !m_isAllayTurn;
			return true;
		}
		else
		{
			break;
		}
	}
	}

	// 여기에 만약에 피해량 증감 있다면 그거 적용.
	// 다만 아직은 그런 수준으로 만들지는 않음.
	// ...
	int damageFine{powerFine};

	std::cout << attackerP->GetName() << " injured " << damageFine << " to " << defenderP->GetName() << '\n';

	bool isAlive{ defenderP->UpdateHp(powerFine) };

	if (isAlive)
	{
		return true;
	}
	else
	{
		std::cout << defenderP->GetName() << " is dead.\n";
		return false;
	}
}
