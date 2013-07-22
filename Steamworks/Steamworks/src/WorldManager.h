#pragma once

#include "Map.h"

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

