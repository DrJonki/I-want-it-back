#pragma once

#include <SFML\Graphics.hpp>

#include <fstream>
#include <sstream>
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

	void updateResolution();

	std::string getResolutionString();
	std::string getAAString();
	bool usingCustomRes();

	int resVectorNumber;
	sf::Vector2i resolution;
	unsigned int antiAliasing;
	bool smoothTextures;
	bool vSync;
	bool fullScreen;

	float worldGravity;

	bool debug;

	int soundVolume;
	int musicVolume;
};

