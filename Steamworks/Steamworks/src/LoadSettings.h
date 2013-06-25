#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <Windows.h>

#include "dirent.h"

class LoadSettings
{
public:
	LoadSettings(void);
	~LoadSettings(void);
	
	void resetValues();
	void loadFromFile();

	//Level
	std::vector<std::string> _campaignVector;
	std::string _campaign;
	std::string _level;

	//Player
	std::string _playerPath;
};