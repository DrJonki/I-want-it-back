#include "Map.h"

//Map
//Public
Map::Map(void) : _window(nullptr),
				 _world(nullptr)
{}

Map::~Map(void)
{}

void Map::load(b2World* world,
			   sf::RenderWindow* window,
			   std::string campaign,
			   std::string level)
{
	_world = world;
	_window = window;

	_campaign = campaign;
	_level = level;

	_backGroundObject.reserve(100);
	_mapObjects.reserve(1000);
	
	createBackgrounds();
	createStatics();
}


void Map::draw()
{
	for (int i = 0; i < _backGroundObject.size(); i++){
		_window->draw(_backGroundObject[i]);
	}

	for (int i = 0; i < _mapObjects.size(); i++){
		_window->draw(_mapObjects[i]);
	}
}

//Private

void Map::createBackgrounds()
{
	int temp = 0;
	std::string tString;

	std::string path("Levels/");
	path += _campaign;
	path += "/";
	path += _level;
	path += "/backgrounds.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
	while (file.good()){
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


		if (file.peek() == '\n') temp++;
		else if (file.peek() == file.eof()) break;
	}
	}
	


}

void Map::createStatics()
{
	int temp = 0;
	std::string tString;
	
	std::string path("Levels/");
	path += _campaign;
	path += "/";
	path += _level;
	path += "/statics.dat";

	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
	while (file.good()){
		int t_sizeX = 0, t_sizeY = 0, t_posX = 0, t_posY = 0;
		float t_bBoxModX = 0, t_bBoxModY = 0;
		std::string t_textureDir;

		file >> t_sizeX;
		file >> t_sizeY;
		file >> t_posX;
		file >> t_posY;
		file >> t_bBoxModX;
		file >> t_bBoxModY;
		file >> t_textureDir;

		_mapObjects.emplace_back(MapObject());
		_mapObjects.back().load(_world, t_sizeX, t_sizeY, t_posX, t_posY, t_textureDir, t_bBoxModX, t_bBoxModY);

		if (file.peek() == '\n') temp++;
		else if (file.peek() == file.eof()) break;
	}
	}
}