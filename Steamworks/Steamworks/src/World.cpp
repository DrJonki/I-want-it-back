#include "World.h"


World::World(sf::RenderWindow* window) : _gameWorld(nullptr),
										 _window(window)
{
	b2Vec2 gravity(0.f, g_worldGravity);
	_gameWorld = new b2World(gravity);
	_gameWorld->SetAllowSleeping(true);
}
World::~World(void)
{
	delete _gameWorld;
}

//Public
void World::physStep()
{
	_gameWorld->Step((float)g_updateTimerValue, 8, 3);
	_gameWorld->ClearForces();
}

void World::draw()
{

}