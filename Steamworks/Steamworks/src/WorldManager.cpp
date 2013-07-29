#include "WorldManager.h"


WorldManager::WorldManager(sf::RenderWindow* window)
	: _window(window),
	  _gameWorld(nullptr),
	  _gameMap(nullptr)
{}


WorldManager::~WorldManager(void)
{}


void WorldManager::loadWorld(ContactListener* listener, LoadSettings& lsettings, EngineSettings& esettings, thor::StopWatch& gameTime)
{
	_cListener = listener;

	b2Vec2 gravity(0.f, esettings.worldGravity);
	_gameWorld = new b2World(gravity);
	_gameWorld->SetAllowSleeping(false);

	_gameMap = new Map(gameTime);
	_gameMap->load(_gameWorld, listener, _window, lsettings, esettings);
}

void WorldManager::resetWorldStates()
{
	_gameMap->resetMapStates();
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