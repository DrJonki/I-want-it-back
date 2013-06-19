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


	/// Simulates physics int the world by the amount of time defined by g_updateTimerValue.
	void physStep();


	/// Draws all the world objects.
	void draw();


	/// Returns a pointer to the world object.
	/// @return main world object.
	b2World* getWorldPtr() { return _world; };

private:

	/// A local pointer to the world object.
	b2World* _world;

	/// A local pointer to the main window object.
	sf::RenderWindow* _window;

	/// A map object which contains all the objects in the world.
	Map _gameMap;
};

