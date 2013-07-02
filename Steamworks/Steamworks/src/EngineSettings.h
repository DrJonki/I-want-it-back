#pragma once

#include <SFML\Graphics.hpp>

#include <fstream>
#include <Windows.h>
#include <iostream>
#include <direct.h>

#include "Misc.h"

class EngineSettings
{
public:
	EngineSettings(void);
	~EngineSettings(void);

	void loadDefaults();
	void loadFromFile();
	void writeToFile();

	sf::Vector2i resolution;
	bool vSync;
	bool fullScreen;

	float worldGravity;
};

