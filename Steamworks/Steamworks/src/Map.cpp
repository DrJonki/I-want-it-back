#include "Map.h"


//Map
//Public
Map::Map(void) : _window(nullptr),
				 _world(nullptr),
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

	sManager.playStreams();
	sManager.playSound();
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
		if (_cListener->inContact((void*)MAINFIX_P1) && _cListener->inContact(_triggerObject[i]._body->GetUserData())){
			if (_triggerObject[i]._type == RT_SOUND){
				sManager.playSound((unsigned int)_triggerObject[i]._data);
			}
		}

		else{
			sManager.resetSounds();
		}
	}
}


void Map::draw()
{
	for (unsigned int i = 0; i < _backGroundObject.size(); i++){
		_window->draw(_backGroundObject[i]);
	}

	for (unsigned int i = 0; i < _mapObject.size(); i++){
		_window->draw(_mapObject[i]);
	}

	if (_debug){
		for (unsigned int i = 0; i < _triggerObject.size(); i++){
			_window->draw(_triggerObject[i]);
		}
	}
}

void Map::drawForeground()
{
	for (unsigned int i = 0; i < _foregroundObject.size(); i++){
		_window->draw(_foregroundObject[i]);
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
			_backGroundObject.back().load(t_bottom, t_sizeX, t_sizeY, t_posX, t_textureDir);


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
				t_interval = 1,
				t_frames = 1;

			float t_bBoxModX = 0, t_bBoxModY = 0;
			bool hasPhys = true;
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
			}

			_mapObject.emplace_back(MapObject());
			_mapObject.back().load(_world, t_sizeX, t_sizeY, t_posX, t_posY, hasPhys, t_textureDir, t_aSizeX, t_aSizeY, t_startX, t_startY, t_interval, t_frames, t_bBoxModX, t_bBoxModY);
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
				t_interval = 1,
				t_frames = 1;

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
			}

			_foregroundObject.emplace_back(ForegroundObject());
			_foregroundObject.back().load(t_sizeX, t_sizeY, t_posX, t_posY, t_textureDir, t_aSizeX, t_aSizeY, t_startX, t_startY, t_interval, t_frames);
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
		if (_triggerObject[i]._body->GetUserData() != (void*)0){
			_cListener->addData(_triggerObject[i]._body->GetUserData());
		}
	}
}