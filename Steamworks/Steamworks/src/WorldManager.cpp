#include "WorldManager.h"


WorldManager::WorldManager(sf::RenderWindow* window) : _window(window),
													   _gameWorld(nullptr),
													   _gameMap(nullptr)
{}


WorldManager::~WorldManager(void)
{}


void WorldManager::loadWorld(LoadSettings& settings)
{
	b2Vec2 gravity(0.f, g_worldGravity);
	_gameWorld = new b2World(gravity);
	_gameWorld->SetAllowSleeping(true);

	_gameMap = new Map;
	_gameMap->load(_gameWorld, _window, settings._campaign, settings._level);
}

void WorldManager::deleteWorld()
{
	if (_gameWorld != 0){
		delete _gameWorld;
		_gameWorld = nullptr;
	}
	if (_gameMap != 0){
		delete _gameMap;
		_gameMap = nullptr;
	}
}


void WorldManager::stepWorldPhysics()
{
	if (_gameWorld != 0){
		_gameWorld->Step((float)g_updateTimerValue, 8, 3);
		_gameWorld->ClearForces();
	}
}

void WorldManager::draw()
{
	if (_gameMap != 0){
		_gameMap->draw();
	}
}

void WorldManager::drawForeground()
{
	_gameMap->drawForeground();
}