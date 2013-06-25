#include "LoadSettings.h"


LoadSettings::LoadSettings(void)
{
	resetValues();
	loadFromFile();
}


LoadSettings::~LoadSettings(void)
{}


void LoadSettings::resetValues()
{
	_campaign = "Default";
	_level = "1";

	_playerPath = "Levels/Common/playerdata.dat";
}

void LoadSettings::loadFromFile()
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir ("Levels")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (std::string(ent->d_name) != "Common" &&
				std::string(ent->d_name) != "." &&
				std::string(ent->d_name) != "..")
			{
				_campaignVector.emplace_back(std::string());
				_campaignVector.back() = ent->d_name;
			}
		}
		closedir (dir);
		}
		else{
			MessageBox(NULL, L"Couldn't find the Levels folder!", L"ERROR", MB_OK);
		}

	_campaign = _campaignVector[0];

	/*std::ifstream file("temp.dat", std::ifstream::in);

	_campaign.emplace_back(std::string());

	if (file.good()){
		file >> _campaign[0];
		file >> _level;
	}*/
}