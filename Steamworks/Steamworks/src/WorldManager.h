#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <memory>

#include "Map.h"
#include "Globals.h"
#include "LoadSettings.h"
#include "Player.h"

class WorldManager
{
public:
	WorldManager(sf::RenderWindow* window);
	~WorldManager(void);

	void loadWorld(LoadSettings&);
	void deleteWorld();

	void stepWorldPhysics();
	void draw();

	b2World* getWorldPtr() { return _gameWorld; };

private:

	sf::RenderWindow* _window;
	b2World* _gameWorld;

	/// A map object which contains all the objects in the world.
	Map* _gameMap;
};

