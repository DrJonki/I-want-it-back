#include "World.h"


World::World(sf::RenderWindow* window) : _world(nullptr),
										 _window(window)
{
	b2Vec2 gravity(0.f, g_worldGravity);
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);

	_gameMap.load(_world, _window, "Default", "1");
}
World::~World(void)
{
	delete _world;
}

//Public
void World::physStep()
{
	_world->Step((float)g_updateTimerValue, 8, 3);
	_world->ClearForces();
}

void World::draw()
{
	_gameMap.draw();
}