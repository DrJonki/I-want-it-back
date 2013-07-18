#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <memory>

#include "Map.h"
#include "Globals.h"
#include "LoadSettings.h"
#include "EngineSettings.h"
#include "Player.h"
#include "ContactListener.h"

class WorldManager
{
public:
	WorldManager(sf::RenderWindow* window);
	~WorldManager(void);

	void loadWorld(ContactListener* listener, LoadSettings&, EngineSettings&);
	void deleteWorld();

	void stepWorldPhysics();
	void draw();
	void drawForeground();

	void resetMap() {};

	b2World* getWorldPtr() { return _gameWorld; };

private:

	sf::RenderWindow* _window;
	b2World* _gameWorld;
	ContactListener* _cListener;

	/// A map object which contains all the objects in the world.
	Map* _gameMap;
};

