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
	std::ifstream file("temp.dat", std::ifstream::in);

	if (file.good()){
		file >> _campaign;
		file >> _level;
	}
}