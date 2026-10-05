#include <iostream>
#include "Dice.h"
#include "Character.h"
#include "MyHeader.h"
void Character::SetSetupStandard(std::string name ,Dice* diceP,int level)
{
	m_name = name;
	m_diceP = diceP;

	for (int i{}; i < level; ++i)
	{
		IncreaseLevel();
	}
}

void Character::UpdateStatus(int newLevel)
{
}

bool Character::UpdateHp(int damage)
{
	m_hpCurrent -= damage;

	if (0>m_hpCurrent)
	{
		m_hpCurrent = 0;
	}
	else if (m_hpMax < m_hpCurrent)
	{
		m_hpCurrent = m_hpMax;
	}

	if (0 == m_hpCurrent)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Character::UpdateExp(int expChange)
{
}

void Character::IncreaseLevel()
{
	IncreaseStatusRandom();
	++m_level;
}

void Character::IncreaseStatusRandom()
{
	switch (m_diceP->DiceRoll(static_cast<DICERANK>(3)))
	{
	case 1:
	{
		++m_atk;
		break;
	}
	case 2:
	{
		++m_def;
		break;
	}
	case 3:
	{
		++m_dex;
		break;
	}
	}
}

void Character::ShowName()
{
	std::cout << m_name << '\n';
}

void Character::ShowHp()
{
	std::cout << "HP : " << m_hpCurrent << '/' << m_hpMax << '\n';
}

void Character::ShowStatus()
{
	ShowHp();
	std::cout << "Level : " << m_level << '\n';
	std::cout << "Exp : " << m_exp<<'/'<< m_expReqired << '\n';
	std::cout << "Atk : " << ToSignedNumber(m_atk) << '\n';
	std::cout << "Def : " << ToSignedNumber(m_def) << '\n';
	std::cout << "Dex : " << ToSignedNumber(m_dex) << '\n';
}

int Character::Attack()
{
	return m_atk + m_diceP->DiceRoll(m_dr);
}

int Character::Guard()
{
	return m_def + m_diceP->DiceRoll(m_dr);
}

int Character::Avoid()
{
	return m_dex + m_diceP->DiceRoll(m_dr);
}

std::string Character::GetName()
{
	return m_name;
}

int Character::GetHpMax()
{
	return m_hpMax;
}

int Character::GetHpCurrent()
{
	return m_hpCurrent;
}

int Character::GetAtk()
{
	return m_atk;
}

int Character::GetDef()
{
	return m_def;
}

int Character::GetDex()
{
	return m_dex;
}

int Character::GetDr()
{
	return m_dr;
}

