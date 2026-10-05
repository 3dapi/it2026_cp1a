#include <random>
#include "Dice.h"
#include "Character.h"

void Dice::DiceSetup(int seedFix)
{

	if (seedFix == DICE_SEED_FIX_OFF)
	{
		std::random_device rd;
		m_mt.seed(rd());
	}
	else
	{
		m_mt.seed(seedFix);
	}
}

int Dice::DiceRoll(DICERANK dRank)
{
	std::uniform_int_distribution<int> dice(1, dRank);
	return dice(m_mt);
}
