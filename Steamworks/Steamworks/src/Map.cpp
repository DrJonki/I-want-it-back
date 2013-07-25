#include "Map.h"

#include <fstream>

//Map
//Public
Map::Map(void) : _window(nullptr),
				 _world(nullptr),
				 _esettings(nullptr),
				 _debug(false)
{}

Map::~Map(void)
{
	_backGroundObject.clear();
	_mapObject.clear();
	_foregroundObject.clear();
	_triggerObject.clear();
}

void Map::load(b2World* world,
			   ContactListener* listener,
			   sf::RenderWindow* window,
			   LoadSettings& lsettings,
			   EngineSettings& esettings)
{
	_world = world;
	_cListener = listener;
	_window = window;

	_campaign = lsettings._campaignVector[lsettings._campaign];
	_level = lsettings._levelVector[lsettings._level];

	_debug = esettings.debug;

	_esettings = &esettings;

	_backGroundObject.clear();
	_mapObject.clear();
	_foregroundObject.clear();
	_triggerObject.clear();
	_backGroundObject.reserve(esettings.backgroundObjectLimit);
	_mapObject.reserve(esettings.mapObjectLimit);
	_foregroundObject.reserve(esettings.foregroundObjectLimit);
	_triggerObject.reserve(esettings.triggerObjectLimit);
	

	createBackgrounds();
	createStatics();
	createForeground();
	createTriggers();

	
	sManager.loadSounds(lsettings, esettings);
	sManager.loadStreams(lsettings, esettings);

	sManager.playStream();
	sManager.playSound();
}

void Map::resetMapStates()
{
	sManager.resetSounds();

	for (unsigned int i = 0; i < _foregroundObject.size(); i++){
		_foregroundObject[i].setCurrentFrame(1);
		_foregroundObject[i]._playing = false;
	}
	for (unsigned int i = 0; i < _mapObject.size(); i++){
		_mapObject[i].setCurrentFrame(1);
		_mapObject[i]._playing = false;
	}
}


void Map::update()
{
	for (unsigned int i = 0; i < _mapObject.size(); i++){
		_mapObject[i].update();
	}

	for (unsigned int i = 0; i < _foregroundObject.size(); i++){
		_foregroundObject[i].update();
	}

	for (unsigned int i = 0; i < _triggerObject.size(); i++){
		if (_cListener->inContact(_triggerObject[i]._body->GetFixtureList()[0].GetUserData())){
			if (_triggerObject[i]._type == RT_SOUND){
				sManager.playSound(_triggerObject[i]._data);
				sManager.playStream(_triggerObject[i]._data);
			}
			if (_triggerObject[i]._type == RT_ANIMATION){
				for (unsigned int j = 0; j < _mapObject.size(); j++){
					if (_mapObject[j]._trigData == _triggerObject[i]._data){
						_mapObject[j]._playing = true;
					}
				}
				for (unsigned int j = 0; j < _foregroundObject.size(); j++){
					if (_foregroundObject[j]._trigData == _triggerObject[i]._data){
						_foregroundObject[j]._playing = true;
					}
				}
			}

			if (_triggerObject[i]._body->GetFixtureList()[0].GetUserData() == (void*)TRIG_LETHAL) ns::deathState = true;
			else if (_triggerObject[i]._body->GetFixtureList()[0].GetUserData() == (void*)TRIG_CHECKPOINT) ns::spawnPoint = _triggerObject[i].getPosition().x;
			else if (_triggerObject[i]._body->GetFixtureList()[0].GetUserData() == (void*)TRIG_ENDOFLEVEL) ns::endOfLevelState = true;
		}

		else{
			sManager.resetSounds();
			for (unsigned int i = 0; i < _mapObject.size(); i++){
				if (!_mapObject[i]._loop && !_mapObject[i].lastFrame()) _mapObject[i]._playing = false;
			}
			for (unsigned int i = 0; i < _foregroundObject.size(); i++){
				if (!_foregroundObject[i]._loop && !_foregroundObject[i].lastFrame()) _foregroundObject[i]._playing = false;
			}
		}
	}


	
	sManager.updateVolumes();
}


void Map::draw()
{
	for (unsigned int i = 0; i < _backGroundObject.size(); i++){
		if (_backGroundObject[i].getPosition().x <= _window->getView().getCenter().x + (_window->getView().getSize().x / 2) &&
			_backGroundObject[i].getPosition().x + _backGroundObject[i].getSize().x >= _window->getView().getCenter().x - (_window->getView().getSize().x / 2))
		{
			_window->draw(_backGroundObject[i]);
		}
	}

	for (unsigned int i = 0; i < _mapObject.size(); i++){
		if (_mapObject[i].getPosition().x - (_mapObject[i].getSize().x / 2) <= _window->getView().getCenter().x + (_window->getView().getSize().x / 2) &&
			_mapObject[i].getPosition().x + (_mapObject[i].getSize().x / 2) >= _window->getView().getCenter().x - (_window->getView().getSize().x / 2))
		{
			_window->draw(_mapObject[i]);
		}
	}

	if (_debug){
		for (unsigned int i = 0; i < _mapObject.size(); i++){
			if (_mapObject[i].hbShape.getPosition().x - (_mapObject[i].hbShape.getSize().x / 2) <= _window->getView().getCenter().x + (_window->getView().getSize().x / 2) &&
				_mapObject[i].hbShape.getPosition().x + (_mapObject[i].hbShape.getSize().x / 2) >= _window->getView().getCenter().x - (_window->getView().getSize().x / 2))
			{
				_window->draw(_mapObject[i].hbShape);
			}
		}
		for (unsigned int i = 0; i < _triggerObject.size(); i++){
			if (_triggerObject[i].getPosition().x - (_triggerObject[i].getSize().x / 2) <= _window->getView().getCenter().x + (_window->getView().getSize().x / 2) &&
				_triggerObject[i].getPosition().x + (_triggerObject[i].getSize().x / 2) >= _window->getView().getCenter().x - (_window->getView().getSize().x / 2))
			{
				_window->draw(_triggerObject[i]);
			}
		}
	}
}

void Map::drawForeground()
{
	for (unsigned int i = 0; i < _foregroundObject.size(); i++){
		if (_foregroundObject[i].getPosition().x - (_foregroundObject[i].getSize().x / 2) <= _window->getView().getCenter().x + (_window->getView().getSize().x / 2) &&
			_foregroundObject[i].getPosition().x + (_foregroundObject[i].getSize().x / 2) >= _window->getView().getCenter().x - (_window->getView().getSize().x / 2))
		{
			_window->draw(_foregroundObject[i]);
		}
	}
}

//Private

void Map::createBackgrounds()
{
	int temp = 0;

	std::string path("Levels/");
	path += _campaign;
	path += "/";
	path += _level;
	path += "/backgrounds.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good() && file.peek() != file.eof()){
		while (!file.eof()){
			bool t_bottom = 0;
			int t_sizeX = 0, t_sizeY = 0, t_posX = 0;
			std::string t_textureDir;

			file >> t_bottom;
			file >> t_sizeX;
			file >> t_sizeY;
			file >> t_textureDir;
		
			if (!t_bottom && _backGroundObject.size() > 0) t_posX = _backGroundObject[temp - 1].getPosition().x + _backGroundObject[temp - 1].getLocalBounds().width;
			else if (t_bottom && _backGroundObject.size() > 0){
				if (_backGroundObject[temp - 1].getOrigin().y == 0) t_posX = t_posX = _backGroundObject[temp - 1].getPosition().x + _backGroundObject[temp - 1].getLocalBounds().width;
			}

			_backGroundObject.emplace_back(BackgroundObject());
			_backGroundObject.back().load(t_bottom, t_sizeX, t_sizeY, t_posX, t_textureDir, _esettings->smoothTextures);


			temp++;
		}
	}
}

void Map::createStatics()
{
	std::string path("Levels/");
	path += _campaign;
	path += "/";
	path += _level;
	path += "/statics.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good() && file.peek() != file.eof()){
		while (!file.eof()){
			int t_sizeX = 0,
				t_sizeY = 0,
				t_posX = 0,
				t_posY = 0,
				t_aSizeX = 0,
				t_aSizeY = 0,
				t_startX = 0,
				t_startY = 0,
				t_interval = 60,
				t_frames = 1;
			unsigned int t_data = 0;

			float t_bBoxModX = 0, t_bBoxModY = 0;
			bool hasPhys = true, t_loop = false;
			std::string t_textureDir;

			file >> t_sizeX;
			file >> t_sizeY;
			file >> t_posX;
			file >> t_posY;
			file >> t_bBoxModX;
			file >> t_bBoxModY;
			file >> t_textureDir;
			file >> hasPhys;

			if (file.peek() != '\n'){
				file >> t_aSizeX;
				file >> t_aSizeY;
				file >> t_startX;
				file >> t_startY;
				file >> t_interval;
				file >> t_frames;
				if (file.peek() != '\n'){
					file >> t_data;
					file >> t_loop;
				}
			}

			_mapObject.emplace_back(MapObject());
			_mapObject.back().load(_world, t_sizeX, t_sizeY, t_posX, t_posY, hasPhys, t_textureDir, _esettings->smoothTextures, t_aSizeX, t_aSizeY, t_startX, t_startY, t_interval, t_frames, t_bBoxModX, t_bBoxModY);
			_mapObject.back()._trigData = t_data;
			_mapObject.back()._loop = t_loop;
		}
	}
}

void Map::createForeground()
{
	std::string path("Levels/");
	path += _campaign;
	path += "/";
	path += _level;
	path += "/foreground.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good() && file.peek() != file.eof()){
		while (!file.eof()){
			int t_sizeX = 0,
				t_sizeY = 0,
				t_posX = 0,
				t_posY = 0,
				t_aSizeX = 0,
				t_aSizeY = 0,
				t_startX = 0,
				t_startY = 0,
				t_interval = 60,
				t_frames = 1;
			unsigned int t_data = 0;

			bool t_loop = false;
			std::string t_textureDir;

			file >> t_sizeX;
			file >> t_sizeY;
			file >> t_posX;
			file >> t_posY;
			file >> t_textureDir;

			if (file.peek() != '\n'){
				file >> t_aSizeX;
				file >> t_aSizeY;
				file >> t_startX;
				file >> t_startY;
				file >> t_interval;
				file >> t_frames;
				if (file.peek() != '\n'){
					file >> t_data;
					file >> t_loop;
				}
			}

			_foregroundObject.emplace_back(ForegroundObject());
			_foregroundObject.back().load(t_sizeX, t_sizeY, t_posX, t_posY, t_textureDir, _esettings->smoothTextures, t_aSizeX, t_aSizeY, t_startX, t_startY, t_interval, t_frames);
			_foregroundObject.back()._trigData = t_data;
			_foregroundObject.back()._loop = t_loop;
		}
	}
}

void Map::createTriggers()
{
	std::string path("Levels/");
	path += _campaign;
	path += "/";
	path += _level;
	path += "/triggers.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good() && file.peek() != file.eof()){
		while (!file.eof()){
			float t_sizeX = 0, t_sizeY = 0, t_posX = 0, t_posY = 0;
			unsigned int t_data = 0, t_rType = 0, t_rData = 0;

			file >> t_sizeX;
			file >> t_sizeY;
			file >> t_posX;
			file >> t_posY;
			file >> t_data;
			if (file.peek() != '\n'){
				file >> t_rType;
				file >> t_rData;
			}

			_triggerObject.emplace_back(Trigger());
			_triggerObject.back().load(_world, t_sizeX, t_sizeY, t_posX, t_posY, (void*)t_data, t_rType, t_rData);
		}
	}

	for (unsigned int i = 0; i < _triggerObject.size(); i++){
		if (_triggerObject[i]._body->GetFixtureList()[0].GetUserData() != (void*)0){
			_cListener->addData(_triggerObject[i]._body->GetFixtureList()[0].GetUserData());
		}
	}
}