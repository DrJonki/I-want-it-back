#pragma once

#include <vector>
#include <string>

class LoadSettings
{
public:
	LoadSettings(void);
	~LoadSettings(void);
	
	void resetValues();
	void loadCampaigns();
	void loadLevels();
	void loadCredits();

	//Level
	std::vector<std::string> _campaignVector;
	unsigned int _campaign;
	std::vector<std::string> _levelVector;
	unsigned int _level;

	std::string _credits;

	//Player
	std::string _playerPath;
};