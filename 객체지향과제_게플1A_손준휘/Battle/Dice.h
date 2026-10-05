#pragma once
#include <random>

enum ENUM_DICE
{
	DICE_SEED_FIX_OFF = -7777777,
};

typedef enum DICERANK
{
	DR_4TETRAHEDRON = 4,
	DR_6HEXAHEDRON = 6,
	DR_8OCTAHEDRON = 8,
	DR_12DODECAHEDRON = 12,
	DR_20ICOSAHEDRON = 20,
}DICERANK;


class Dice
{
public:
	void DiceSetup(int seedFix = DICE_SEED_FIX_OFF);
	int DiceRoll(DICERANK dRank);
private:
	std::mt19937 m_mt{};
};
