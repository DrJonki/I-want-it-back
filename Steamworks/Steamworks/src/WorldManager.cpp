#include "WorldManager.h"


WorldManager::WorldManager(sf::RenderWindow* window) : _window(window),
													   _gameWorld(nullptr),
													   _gameMap(nullptr)
{}


WorldManager::~WorldManager(void)
{}


void WorldManager::loadWorld(LoadSettings& lsettings, EngineSettings& esettings)
{
	b2Vec2 gravity(0.f, esettings.worldGravity);
	_gameWorld = new b2World(gravity);
	_gameWorld->SetAllowSleeping(true);

	_gameMap = new Map;
	_gameMap->load(_gameWorld, _window, lsettings._campaign, lsettings._level);
}

void WorldManager::deleteWorld()
{
	if (_gameWorld != nullptr){
		delete _gameWorld;
		_gameWorld = nullptr;
	}
	if (_gameMap != nullptr){
		delete _gameMap;
		_gameMap = nullptr;
	}
}


void WorldManager::stepWorldPhysics()
{
	if (_gameMap != nullptr){
		_gameMap->update();
	}

	if (_gameWorld != nullptr){
		_gameWorld->Step((float)ns::g_updateTimerValue, 8, 3);
		_gameWorld->ClearForces();
	}
}

void WorldManager::draw()
{
	if (_gameMap != nullptr){
		_gameMap->draw();
	}
}

void WorldManager::drawForeground()
{
	_gameMap->drawForeground();
}