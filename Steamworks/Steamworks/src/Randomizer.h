#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>



class Randomizer
{
public:
	Randomizer(void);
	~Randomizer(void);


	//Random numbers
	float fGetRandom(const float min, const float max);
	int iGetRandom(const int min, const int max);

	//Random chance
	bool randomChance(const int chance);

private:
	void setSeed();
};