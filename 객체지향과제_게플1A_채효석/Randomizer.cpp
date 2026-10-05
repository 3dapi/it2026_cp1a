#include "Randomizer.h"
int Randomizer::Rand(int min, int max)
{
	if (min > max)
	{
		printf("INVALID RANDOM RANGE");
		return min;
	}

	_dis.param(std::uniform_int_distribution<int>::param_type(min, max));
	return _dis(_gen);
}
