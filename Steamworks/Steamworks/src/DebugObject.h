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

	void assignPtr(int* dValue, std::string dTitle){
		_dValuei = dValue;
		_dTitle = dTitle;
	};
	void assignPtr(float* dValue, std::string dTitle){
		_dValuef = dValue;
		_dTitle = dTitle;
	};

	void update();

private:
	float* _dValuef;
	int* _dValuei;

	std::string _dTitle;
};