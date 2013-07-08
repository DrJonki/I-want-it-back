#include "EngineSettings.h"


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
	
	soundVolume = 100;
	musicVolume = 100;
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
			else if (tempS == "Debug_mode:"){
				file >> debug;
			}
			else if (tempS == "Anti-aliasing:"){
				file >> antiAliasing;
			}
			else if (tempS == "Smooth_textures:"){
				file >> smoothTextures;
			}
			else if (tempS == "Music_volume:"){
				file >> musicVolume;
			}
			else if (tempS == "Sound_volume"){
				file >> soundVolume;
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
	path += "/Documents/my games/uhh/settings.txt";

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
	s = "Music_volume: ";
	file << s << musicVolume << std::endl;
	s = "Sound_volume: ";
	file << s << soundVolume;


	file.close();
}

void EngineSettings::updateResolution()
{
	resolution.x = sf::VideoMode::getFullscreenModes()[resVectorNumber].width;
	resolution.y = sf::VideoMode::getFullscreenModes()[resVectorNumber].height;

	usingCustomRes();
}

std::string EngineSettings::getResolutionString()
{
	if (usingCustomRes()) return "Custom";
	else{
		std::stringstream ss;

		ss << resolution.x;
		ss << " x ";
		ss << resolution.y;

		return ss.str();
	}
}

std::string EngineSettings::getAAString()
{
	std::stringstream ss;

	ss << "x";
	ss << antiAliasing;

	return ss.str();
}

std::string EngineSettings::getMVolumeString()
{
	std::stringstream ss;

	ss << musicVolume;

	return ss.str();
}

std::string EngineSettings::getSVolumeString()
{
	std::stringstream ss;

	ss << soundVolume;

	return ss.str();
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