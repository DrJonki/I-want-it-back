#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include <cstdio>
#include <memory>

#include "MapObject.h"

class Map
{
public:
	Map(void);
	~Map(void);

	void load(b2World* world, sf::RenderWindow* window);
	void draw();

private:
	void _createStatics();
	void _createBackgrounds();


	std::vector<sf::RectangleShape> _backGround;
	std::vector<MapObject> _mapObjects;

	sf::RenderWindow* _window;
	b2World* _world;
};