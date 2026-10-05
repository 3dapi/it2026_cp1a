#pragma once
#include <random>
class Randomizer
{
public:
	Randomizer() : _gen(_rd()) {}
	int Rand(int min,int max);
private:
	std::random_device _rd;
	std::mt19937 _gen;
	std::uniform_int_distribution<int> _dis;
};