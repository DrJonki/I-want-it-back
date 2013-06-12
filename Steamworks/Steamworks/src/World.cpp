#include "World.h"


World::World(void)
{
	b2Vec2 gravity(0.f, g_worldGravity);
	gameWorld = new b2World(gravity);
	gameWorld->SetAllowSleeping(true);
	
	
	createGround(400.f, 500.f, (float)g_windowWidth, 10.f);
}
World::~World(void)
{
	delete gameWorld;
}

//Public
void World::physStep()
{
	gameWorld->Step(g_updateTimerValue, 8.f, 3.f);
}

//Private

void World::createGround(const float posX,
						 const float posY,
						 const float sizeX,
						 const float sizeY)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(posX/g_P2MScale, posY/g_P2MScale);
    bodyDef.type = b2_staticBody;

    b2Body* body = gameWorld->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox((sizeX / 2) / g_P2MScale, (sizeY / 2) / g_P2MScale);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;
    fixtureDef.shape = &shape;

    body->CreateFixture(&fixtureDef);

	s.setSize(sf::Vector2f(sizeX, sizeY));
	s.setOrigin(sizeX / 2, sizeY / 2);
	s.setPosition(posX, posY);
}