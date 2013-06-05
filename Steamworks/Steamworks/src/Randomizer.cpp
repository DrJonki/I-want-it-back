#include "Randomizer.h"


Randomizer::Randomizer(void)
{
	setSeed();
}
Randomizer::~Randomizer(void){}


//Public
float Randomizer::fGetRandom(const float min, const float max)
{
	return min + (float)rand()/((float)RAND_MAX/(max-min));
}

int Randomizer::iGetRandom(const int min, const int max)
{
	int iRandom = rand() % (max + abs(min));

	return iRandom - abs(min);
}

bool Randomizer::randomChance(const int chance)
{
	if (chance > 100 || chance < 0) return false;

	int randNumber = rand() & 101;

	if (chance <= randNumber) return true;
	return false;
}

//Private
void Randomizer::setSeed()
{
	srand(time(NULL));
}
