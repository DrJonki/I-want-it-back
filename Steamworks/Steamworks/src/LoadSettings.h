#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

class LoadSettings
{
public:
	LoadSettings(void);
	~LoadSettings(void);
	
	void resetValues();
	void loadFromFile();

	//Level
	std::string _campaign;
	std::string _level;

	//Player
	std::string _playerPath;
};