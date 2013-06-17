#include "Map.h"

//Map
//Public
Map::Map(void) : _window(nullptr),
				 _world(nullptr)
{}

Map::~Map(void)
{}

void Map::load(b2World* world, sf::RenderWindow* window)
{
	_world = world;
	_window = window;

	_createStatics();
	_createBackgrounds();
}


void Map::draw()
{
	for (int i = 0; i < _backGround.size(); i++){
		
	}

	for (int i = 0; i < _mapObjects.size(); i++){
		_window->draw(_mapObjects[i]._shape);
	}
}

//Private

void Map::_createStatics()
{

}

void Map::_createBackgrounds()
{

}