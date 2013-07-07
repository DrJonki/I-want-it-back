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
	void loadCampaigns();
	void loadLevels();

	//Level
	std::vector<std::string> _campaignVector;
	unsigned int _campaign;
	std::vector<std::string> _levelVector;
	unsigned int _level;

	//Player
	std::string _playerPath;
};