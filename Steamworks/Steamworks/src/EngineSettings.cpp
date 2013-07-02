#include "EngineSettings.h"


EngineSettings::EngineSettings(void)
{
	loadDefaults();
	loadFromFile();
}

EngineSettings::~EngineSettings(void)
{}


void EngineSettings::loadDefaults()
{
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	vSync = true;
	fullScreen = false;

	worldGravity = 25.f;
}

void EngineSettings::loadFromFile()
{
	//Create folder if doesn't exist
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	_mkdir(path.c_str());
	path += "\\uhh";
	_mkdir(path.c_str());

	//Load values
	path = (std::getenv("USERPROFILE"));
	path += "/Documents/my games/uhh/settings.txt";

	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
		std::string tempS;

		while(!file.eof()){
			file >> tempS;

			if (tempS == "ResolutionX:"){
				file >> resolution.x;
			}
			else if (tempS == "ResolutionY:"){
				file >> resolution.y;
			}
			else if (tempS == "Vertical_sync:"){
				file >> vSync;
			}
			else if (tempS == "Full_screen:"){
				file >> fullScreen;
			}
			else if (tempS == "World_gravity:"){
				file >> worldGravity;
			}
		}
	}
	else{
		writeToFile();
	}
}

void EngineSettings::writeToFile()
{
	std::string path = (std::getenv("USERPROFILE"));
	path += "/Documents/my games/uhh/settings.txt";

	std::string s;

	std::ofstream file;
	file.open(path);

	s = "ResolutionX: ";
	file << s << resolution.x << std::endl;
	s = "ResolutionY: ";
	file << s << resolution.y << std::endl;
	s = "Vertical sync: ";
	file << s << vSync << std::endl;
	s = "Full screen: ";
	file << s << fullScreen << std::endl;
	s = "World gravity: ";
	file << s << worldGravity;


	file.close();
}