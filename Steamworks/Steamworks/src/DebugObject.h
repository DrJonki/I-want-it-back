#pragma once

#include <SFML\Graphics.hpp>
#include <sstream>
#include <string>

#include "Globals.h"

class DebugObject : public sf::Text
{
public:
	DebugObject(void);
	~DebugObject(void);

	void assignPtr(sf::Time*, std::string);
	void assignPtr(int*, std::string);
	void assignPtr(float*, std::string);

	void update();

private:
	sf::Time* dTime;
	int* dInt;
	float* dFloat;

	std::string dTitle;
};

