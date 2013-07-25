#include "LoadSettings.h"

#include <fstream>

#include "dirent.h"
#include "Globals.h"


LoadSettings::LoadSettings(void)
{
	resetValues();
	loadCampaigns();
	loadLevels();
	loadCredits();
}

LoadSettings::~LoadSettings(void)
{}


void LoadSettings::resetValues()
{
	_campaign = 0;
	_level = 0;

	_playerPath = "Levels/Common/playerdata.dat";

	_credits = "No credits file found!\nWhy would you delete it? :(";
}

void LoadSettings::loadCampaigns()
{
	_campaignVector.clear();

	DIR *dir;
	struct dirent *ent;

	//Campaigns
	if ((dir = opendir("Levels")) != NULL){
		while ((ent = readdir(dir)) != NULL){
			if (std::string(ent->d_name) != "Common" &&
				std::string(ent->d_name) != "." &&
				std::string(ent->d_name) != "..")
			{
				_campaignVector.emplace_back(std::string());
				_campaignVector.back() = ent->d_name;
			}
		}
		closedir(dir);
	}

	for (unsigned int i = 0; i < _campaignVector.size(); i++){
		if (!ns::gameStateLoader->campaignSaved(_campaignVector[i]))
			ns::gameStateLoader->saveCampaignData(_campaignVector[i]);
	}

	if (_campaignVector.size() == 0){
		_campaignVector.emplace_back(std::string());
		_campaignVector.back() = "No campaigns :(";
	}
}

void LoadSettings::loadLevels()
{
	_levelVector.clear();

	DIR *dir;
	struct dirent *ent;

	std::string s = "Levels/";
	s += _campaignVector[_campaign];

	if ((dir = opendir(s.c_str())) != NULL){
		while ((ent = readdir(dir)) != NULL){
			if (std::string(ent->d_name) != "0" &&
				std::string(ent->d_name) != "." &&
				std::string(ent->d_name) != "..")
			{
				_levelVector.emplace_back(std::string());
				_levelVector.back() = ent->d_name;
			}
		}
		closedir(dir);
	}

	for (unsigned int i = 0; i < _levelVector.size(); i++){
		if (!ns::gameStateLoader->levelSaved(_campaignVector[_campaign], _levelVector[i]) && _campaignVector[0] != "No levels :("){
			if (i == 0)
				ns::gameStateLoader->saveLevelData(_campaignVector[_campaign], _levelVector[i], true);
			else
				ns::gameStateLoader->saveLevelData(_campaignVector[_campaign], _levelVector[i], false);
		}
	}

	if (_levelVector.size() == 0){
		_levelVector.emplace_back(std::string());
		_levelVector.back() = "No levels :(";
	}
}

void LoadSettings::loadCredits()
{
	std::string path = "Resources/Common/credits.txt";

	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
		_credits = "";

		while (!file.eof()){
			std::string s;

			file >> s;

			if (s == "#") _credits += "\n";
			else{
				_credits += s;
				_credits += " ";
			}
		}
	}
}