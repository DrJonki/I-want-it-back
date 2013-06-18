#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>

#include "MapObject.h"
#include "BackgroundObject.h"

class Map
{
public:
	Map(void);
	~Map(void);

	void load(b2World* world,
			  sf::RenderWindow* window,
			  std::string campaign,
			  std::string level);
	void draw();

private:
	void createBackgrounds();
	void createStatics();


	std::vector<BackgroundObject> _backGroundObject;
	std::vector<MapObject> _mapObjects;

	sf::RenderWindow* _window;
	b2World* _world;

	std::string _campaign;
	std::string _level;
};