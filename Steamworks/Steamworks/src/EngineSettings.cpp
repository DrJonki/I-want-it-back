#include "EngineSettings.h"

#include <SFML\Window\VideoMode.hpp>

#include <direct.h>
#include <fstream>
#include <sstream>

#include "Globals.h"


EngineSettings::EngineSettings(void)
{
	loadDefaults();
	loadFromFile();

	usingCustomRes();
}

EngineSettings::~EngineSettings(void)
{}


void EngineSettings::loadDefaults()
{
	resVectorNumber = sf::VideoMode::getFullscreenModes().size() / 3 - 2;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
	antiAliasing = 0;
	smoothTextures = false;
	vSync = true;
	fullScreen = false;

	worldGravity = 25.f;

	debug = false;
	
	globalVolume = 100;
	soundVolume = 100;
	musicVolume = 100;
	anbientVolume = 100;

	backgroundObjectLimit = 50;
	mapObjectLimit = 100;
	foregroundObjectLimit = 50;
	triggerObjectLimit = 50;
	soundSourceLimit = 50;
	soundStreamLimit = 50;
}

void EngineSettings::loadFromFile()
{
	//Create folder if doesn't exist
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	_mkdir(path.c_str());
	path += "\\I want it back";
	_mkdir(path.c_str());

	//Load values
	path = (std::getenv("USERPROFILE"));
	path += "/Documents/my games/I want it back/settings.txt";

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
			else if (tempS == "Debug_mode:"){
				file >> debug;
			}
			else if (tempS == "Anti-aliasing:"){
				file >> antiAliasing;
			}
			else if (tempS == "Smooth_textures:"){
				file >> smoothTextures;
			}
			else if (tempS == "Global_volume:"){
				file >> globalVolume;
			}
			else if (tempS == "Music_volume:"){
				file >> musicVolume;
			}
			else if (tempS == "Sound_volume:"){
				file >> soundVolume;
			}
			else if (tempS == "Anbient_volume:"){
				file >> anbientVolume;
			}
			else if (tempS == "Background_object_limit:"){
				file >> backgroundObjectLimit;
			}
			else if (tempS == "Map_object_limit:"){
				file >> mapObjectLimit;
			}
			else if (tempS == "Foreground_object_limit:"){
				file >> foregroundObjectLimit;
			}
			else if (tempS == "Trigger_object_limit:"){
				file >> triggerObjectLimit;
			}
			else if (tempS == "Sound_source_limit:"){
				file >> soundSourceLimit;
			}
			else if (tempS == "Sound_stream_limit:"){
				file >> soundStreamLimit;
			}
			else if (tempS == "Default_sound_preference:"){
				file >> ns::soundState;
			}
		}
		writeToFile();
	}
	else{
		writeToFile();
	}
}

void EngineSettings::writeToFile()
{
	std::string path = (std::getenv("USERPROFILE"));
	path += "/Documents/my games/I want it back/settings.txt";

	std::string s;

	std::ofstream file;
	file.open(path);

	s = "ResolutionX: ";
	file << s << resolution.x << std::endl;
	s = "ResolutionY: ";
	file << s << resolution.y << std::endl;
	s = "Vertical_sync: ";
	file << s << vSync << std::endl;
	s = "Full_screen: ";
	file << s << fullScreen << std::endl;
	s = "World_gravity: ";
	file << s << worldGravity << std::endl;
	s = "Debug_mode: ";
	file << s << debug << std::endl;
	s = "Anti-aliasing: ";
	file << s << antiAliasing << std::endl;
	s = "Smooth_textures: ";
	file << s << smoothTextures << std::endl;
	s = "Global_volume: ";
	file << s << globalVolume << std::endl;
	s = "Music_volume: ";
	file << s << musicVolume << std::endl;
	s = "Sound_volume: ";
	file << s << soundVolume << std::endl;
	s = "Anbient_volume: ";
	file << s << anbientVolume << std::endl;
	s = "Background_object_limit: ";
	file << s << backgroundObjectLimit << std::endl;
	s = "Map_object_limit: ";
	file << s << mapObjectLimit << std::endl;
	s = "Foreground_object_limit: ";
	file << s << foregroundObjectLimit << std::endl;
	s = "Trigger_object_limit: ";
	file << s << triggerObjectLimit << std::endl;
	s = "Sound_source_limit: ";
	file << s << soundSourceLimit << std::endl;
	s = "Sound_stream_limit: ";
	file << s << soundStreamLimit << std::endl;
	s = "Default_sound_preference: ";
	file << s << ns::soundState;



	file.close();
}

void EngineSettings::updateResolution()
{
	resolution.x = sf::VideoMode::getFullscreenModes()[resVectorNumber].width;
	resolution.y = sf::VideoMode::getFullscreenModes()[resVectorNumber].height;

	/*if (resolution.x > sf::VideoMode::getDesktopMode().width) resolution.x = sf::VideoMode::getDesktopMode().width;
	if (resolution.y > sf::VideoMode::getDesktopMode().height) resolution.y = sf::VideoMode::getDesktopMode().height;*/

	usingCustomRes();
}

bool EngineSettings::usingCustomRes()
{
	for (unsigned int i = 0; i < sf::VideoMode::getFullscreenModes().size(); i++){
		if (sf::VideoMode::getFullscreenModes()[i].width == resolution.x && sf::VideoMode::getFullscreenModes()[i].height == resolution.y){
			resVectorNumber = i;
			return false;
		}
	}
	return true;
}