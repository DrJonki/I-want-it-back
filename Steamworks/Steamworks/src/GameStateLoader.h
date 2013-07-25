#pragma once

#include <string>

class GameStateLoader
{
public:
	GameStateLoader(void);
	~GameStateLoader(void);

	bool campaignSaved(std::string campaign);
	bool levelSaved(std::string campaign, std::string level);

	bool levelUnlocked(std::string campaign, std::string level);

	void saveCampaignData(std::string campaign);
	void saveLevelData(std::string campaign, std::string level, bool unlocked = false, float time = 0.0f);

	float getLevelTime(std::string campaign, std::string level);
};

