#include "GameStateLoader.h"

#include <sstream>
#include <fstream>
#include <direct.h>

#include "dirent.h"


GameStateLoader::GameStateLoader(void)
{}


GameStateLoader::~GameStateLoader(void)
{}


bool GameStateLoader::campaignSaved(std::string campaign)
{
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	path += "\\I want it back";
	path += "\\Saves";

	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(path.c_str())) != NULL){
		while ((ent = readdir(dir)) != NULL){
			if (ent->d_name == campaign.c_str())
				return true;
		}
		closedir(dir);
	}

	return false;
}

bool GameStateLoader::levelSaved(std::string campaign, std::string level)
{
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	path += "\\I want it back";
	path += "\\Saves\\";
	path += campaign;
	path += "\\";
	path += level;
	path += ".save";

	std::ifstream file(path, std::ifstream::in);

	if (file.good())
		return true;

	return false;
}

bool GameStateLoader::levelUnlocked(std::string campaign, std::string level)
{
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	path += "\\I want it back";
	path += "\\Saves\\";
	path += campaign;
	path += "\\";
	path += level;
	path += ".save";

	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
		while (!file.eof()){
			std::string s;
			file >> s;

			if (s == "Unlocked:"){
				bool b;
				file >> b;

				return b;
			}
		}
	}

	return false;
}


void GameStateLoader::saveCampaignData(std::string campaign)
{
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	path += "\\I want it back";
	path += "\\Saves\\";
	path += campaign;
	_mkdir(path.c_str());
}

void GameStateLoader::saveLevelData(std::string campaign, std::string level, bool unlocked, float time)
{
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	path += "\\I want it back";
	path += "\\Saves\\";
	path += campaign;
	path += "\\";
	path += level;
	path += ".save";

	std::ofstream file;
	file.open(path);

	file << "Unlocked: " << unlocked << std::endl;
	file << "Time: " << time;

	file.close();
}

float GameStateLoader::getLevelTime(std::string campaign, std::string level)
{
	std::string path(std::getenv("USERPROFILE"));
	path += "\\Documents\\my games";
	path += "\\I want it back";
	path += "\\Saves\\";
	path += campaign;
	path += "\\";
	path += level;
	path += ".save";

	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
		while (!file.eof()){
			std::string s;
			file >> s;

			if (s == "Time:"){
				float f;
				file >> f;

				return f;
			}
		}
	}

	return 0.0f;
}