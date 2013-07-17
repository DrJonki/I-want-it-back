#include "SoundManager.h"


SoundManager::SoundManager(void)
{}

SoundManager::~SoundManager(void)
{
	_sound.clear();
	_stream.clear();
}


void SoundManager::loadSounds(LoadSettings& lsettings, EngineSettings& esettings)
{
	_esettings = esettings;

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
			unsigned int t_level = 0, t_type = 0;
			file >> t_level;
			file >> t_type;

			
			std::string t_soundDir;
			float t_posX = 0, t_posY = 0, t_minDistance = 1.f, t_attenuation = 1.f;
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
			_sound.back()._type = t_type;
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
			unsigned int t_level = 0, t_type = 0;
			file >> t_level;
			file >> t_type;

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
			_stream.back()._type = t_type;
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

void SoundManager::playStream(const unsigned int data)
{
	for (unsigned int i = 0; i < _stream.size(); i++){
		if (_stream[i]._data == data && !_stream[i].played){
			_stream[i]._stream.get()->play();
			_stream[i].played = true;
		}
	}
}


void SoundManager::resetSounds()
{
	for (unsigned int i = 0; i < _sound.size(); i++){
		_sound[i].played = false;
	}
	for (unsigned int i = 0; i < _stream.size(); i++){
		_stream[i].played = false;
	}
}

void SoundManager::updateVolumes()
{
	const float increment = 1;
	const float minVolume = 1;

	//Top level playing
	if (ns::soundState == 1){

		//Streams
		for (unsigned int i = 0; i < _stream.size(); i++){
			if (_stream[i]._level == 1 || _stream[i]._level == 0){
				//Basic sound
				if (_stream[i]._stream.get()->getVolume() < _esettings.soundVolume && _stream[i]._type == ST_SOUND)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
				else if (_stream[i]._stream.get()->getVolume() > _esettings.soundVolume && _stream[i]._type == ST_SOUND)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);

				//Music
				if (_stream[i]._stream.get()->getVolume() < _esettings.musicVolume && _stream[i]._type == ST_MUSIC)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
				else if (_stream[i]._stream.get()->getVolume() > _esettings.soundVolume && _stream[i]._type == ST_MUSIC)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);

				//Anbient sound
				if (_stream[i]._stream.get()->getVolume() < _esettings.anbientVolume && _stream[i]._type == ST_ANBIENT)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
				else if (_stream[i]._stream.get()->getVolume() > _esettings.soundVolume && _stream[i]._type == ST_ANBIENT)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);
				}

			else if (_stream[i]._stream.get()->getVolume() > minVolume)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);
		}

		//Sounds
		for (unsigned int i = 0; i < _sound.size(); i++){
			if (_sound[i]._level == 1 || _sound[i]._level == 0){
				//Basic sound
				if (_sound[i].getVolume() < _esettings.soundVolume && _sound[i]._type == ST_SOUND)
					_sound[i].setVolume(_sound[i].getVolume() + increment);
				else if (_sound[i].getVolume() > _esettings.soundVolume && _sound[i]._type == ST_SOUND)
					_sound[i].setVolume(_sound[i].getVolume() - increment);

				//Music
				if (_sound[i].getVolume() < _esettings.musicVolume && _sound[i]._type == ST_MUSIC)
					_sound[i].setVolume(_sound[i].getVolume() + increment);
				else if (_sound[i].getVolume() > _esettings.musicVolume && _sound[i]._type == ST_MUSIC)
					_sound[i].setVolume(_sound[i].getVolume() - increment);

				//Anbient sound
				if (_sound[i].getVolume() < _esettings.anbientVolume && _sound[i]._type == ST_ANBIENT)
					_sound[i].setVolume(_sound[i].getVolume() + increment);
				else if (_sound[i].getVolume() > _esettings.anbientVolume && _sound[i]._type == ST_ANBIENT)
					_sound[i].setVolume(_sound[i].getVolume() - increment);
			}

			else if (_sound[i].getVolume() > minVolume)
				_sound[i].setVolume(_sound[i].getVolume() - increment);
		}
	}

	//Bottom level playing
	else if (ns::soundState == 2){
		for (unsigned int i = 0; i < _stream.size(); i++){
			if (_stream[i]._level == 2 || _stream[i]._level == 0){
				//Basic sound
				if (_stream[i]._stream.get()->getVolume() < _esettings.soundVolume && _stream[i]._type == ST_SOUND)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
				else if (_stream[i]._stream.get()->getVolume() > _esettings.soundVolume && _stream[i]._type == ST_SOUND)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);

				//Music
				if (_stream[i]._stream.get()->getVolume() < _esettings.musicVolume && _stream[i]._type == ST_MUSIC)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
				else if (_stream[i]._stream.get()->getVolume() > _esettings.musicVolume && _stream[i]._type == ST_MUSIC)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);

				//Anbient sound
				if (_stream[i]._stream.get()->getVolume() < _esettings.anbientVolume && _stream[i]._type == ST_ANBIENT)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
				else if (_stream[i]._stream.get()->getVolume() > _esettings.anbientVolume && _stream[i]._type == ST_ANBIENT)
					_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);
				}

			else if (_stream[i]._stream.get()->getVolume() > minVolume)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);
		}

		//Sounds
		for (unsigned int i = 0; i < _sound.size(); i++){
			if (_sound[i]._level == 2 || _sound[i]._level == 0){
				//Basic sound
				if (_sound[i].getVolume() < _esettings.soundVolume && _sound[i]._type == ST_SOUND)
					_sound[i].setVolume(_sound[i].getVolume() + increment);
				else if (_sound[i].getVolume() > _esettings.soundVolume && _sound[i]._type == ST_SOUND)
					_sound[i].setVolume(_sound[i].getVolume() - increment);

				//Music
				if (_sound[i].getVolume() < _esettings.musicVolume && _sound[i]._type == ST_MUSIC)
					_sound[i].setVolume(_sound[i].getVolume() + increment);
				else if (_sound[i].getVolume() > _esettings.musicVolume && _sound[i]._type == ST_MUSIC)
					_sound[i].setVolume(_sound[i].getVolume() - increment);

				//Anbient sound
				if (_sound[i].getVolume() < _esettings.anbientVolume && _sound[i]._type == ST_ANBIENT)
					_sound[i].setVolume(_sound[i].getVolume() + increment);
				else if (_sound[i].getVolume() > _esettings.anbientVolume && _sound[i]._type == ST_ANBIENT)
					_sound[i].setVolume(_sound[i].getVolume() - increment);
			}

			else if (_sound[i].getVolume() > minVolume)
				_sound[i].setVolume(_sound[i].getVolume() - increment);
		}
	}

	//Both levels playing
	else{
		//Streams
		for (unsigned int i = 0; i < _stream.size(); i++){
			//Basic sound
			if (_stream[i]._stream.get()->getVolume() < _esettings.soundVolume && _stream[i]._type == ST_SOUND)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
			else if (_stream[i]._stream.get()->getVolume() > _esettings.soundVolume && _stream[i]._type == ST_SOUND)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);

			//Music
			if (_stream[i]._stream.get()->getVolume() < _esettings.musicVolume && _stream[i]._type == ST_MUSIC)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
			else if (_stream[i]._stream.get()->getVolume() > _esettings.musicVolume && _stream[i]._type == ST_MUSIC)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);

			//Anbient sound
			if (_stream[i]._stream.get()->getVolume() < _esettings.anbientVolume && _stream[i]._type == ST_ANBIENT)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() + increment);
			else if (_stream[i]._stream.get()->getVolume() > _esettings.anbientVolume && _stream[i]._type == ST_ANBIENT)
				_stream[i]._stream.get()->setVolume(_stream[i]._stream.get()->getVolume() - increment);
		}

		//Sounds
		for (unsigned int i = 0; i < _sound.size(); i++){
			//Basic sound
			if (_sound[i].getVolume() < _esettings.soundVolume && _sound[i]._type == ST_SOUND)
				_sound[i].setVolume(_sound[i].getVolume() + increment);
			else if (_sound[i].getVolume() > _esettings.soundVolume && _sound[i]._type == ST_SOUND)
				_sound[i].setVolume(_sound[i].getVolume() - increment);

			//Music
			if (_sound[i].getVolume() < _esettings.musicVolume && _sound[i]._type == ST_MUSIC)
				_sound[i].setVolume(_sound[i].getVolume() + increment);
			else if (_sound[i].getVolume() > _esettings.musicVolume && _sound[i]._type == ST_MUSIC)
				_sound[i].setVolume(_sound[i].getVolume() - increment);

			//Anbient sound
			if (_sound[i].getVolume() < _esettings.anbientVolume && _sound[i]._type == ST_ANBIENT)
				_sound[i].setVolume(_sound[i].getVolume() + increment);
			else if (_sound[i].getVolume() > _esettings.anbientVolume && _sound[i]._type == ST_ANBIENT)
				_sound[i].setVolume(_sound[i].getVolume() - increment);
		}
	}
}