#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <memory>

#include "Map.h"
#include "Globals.h"

class World
{
public:
	World(sf::RenderWindow* window);
	~World(void);

	void physStep();
	void draw();

	b2World* getWorldPtr() { return _world; };

private:
	b2World* _world;
	sf::RenderWindow* _window;

	Map _gameMap;
};

