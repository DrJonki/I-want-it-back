#include "SoundManager.h"


namespace ns
{
	unsigned int soundState;
}

SoundManager::SoundManager(void)
	: managerNumber(0)
{}

SoundManager::~SoundManager(void)
{
	_sound.clear();
	_stream.clear();
}


void SoundManager::loadSounds(LoadSettings& lsettings, EngineSettings& esettings)
{
	_sound.clear();
	_sound.reserve(esettings.soundSourceLimit);

	std::string path("Levels/");
	path += lsettings._campaignVector[lsettings._campaign];
	path += "/";
	path += lsettings._levelVector[lsettings._level];
	path += "/loadedsounds.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good() && file.peek() != file.eof()){
		while (!file.eof()){
			unsigned int t_level = 0;
			file >> t_level;

			
			std::string t_soundDir;
			float t_posX = 0, t_posY = 0, t_minDistance = 1.f, t_attenuation = 0;
			bool t_loop = false;
			unsigned int t_data = 0;

			file >> t_soundDir;
			file >> t_posX;
			file >> t_posY;
			file >> t_minDistance;
			file >> t_attenuation;
			file >> t_loop;
			if (file.peek() != '\n') file >> t_data;


			_sound.emplace_back(SoundSource());
			_sound.back().load(t_soundDir, t_posX, t_posY, t_minDistance, t_attenuation, t_loop);
			_sound.back()._data = t_data;
			_sound.back()._level = t_level;
		}	
	}
}

void SoundManager::loadStreams(LoadSettings& lsettings, EngineSettings& esettings)
{
	_stream.clear();
	_stream.reserve(esettings.soundStreamLimit);

	std::string path("Levels/");
	path += lsettings._campaignVector[lsettings._campaign];
	path += "/";
	path += lsettings._levelVector[lsettings._level];
	path += "/streamedsounds.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good() && file.peek() != file.eof()){
		while (!file.eof()){
			unsigned int t_level = 0;
			file >> t_level;

			std::string t_soundDir;
			float t_posX = 0, t_posY = 0, t_minDistance = 1.f, t_attenuation = 0;
			bool t_loop = true;
			unsigned int t_data = 0;

			file >> t_soundDir;
			if (file.peek() != '\n'){
				file >> t_posX;
				file >> t_posY;
				file >> t_minDistance;
				file >> t_attenuation;
				file >> t_loop;
				if (file.peek() != '\n') file >> t_data;
			}


			_stream.emplace_back(SoundStream());
			_stream.back().load(t_soundDir, t_posX, t_posY, t_minDistance, t_attenuation, t_loop);
			_stream.back()._data = t_data;
			_stream.back()._level = t_level;
		}
	}
}


void SoundManager::playSound(const unsigned int data)
{
	for (unsigned int i = 0; i < _sound.size(); i++){
		if (_sound[i]._data == data && !_sound[i].played){
			_sound[i].play();
			_sound[i].played = true;
		}
	}
}

void SoundManager::playStreams()
{
	for (unsigned int i = 0; i < _stream.size(); i++){
		_stream[i]._stream.get()->play();
	}
}


void SoundManager::resetSounds()
{
	for (unsigned int i = 0; i < _sound.size(); i++){
		_sound[i].played = false;
	}
}