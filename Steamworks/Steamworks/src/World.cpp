#include "World.h"


World::World(void)
{
	init();
}
World::~World(void)
{
	delete gameWorld;
}

//Public


//Private
void World::init()
{
	b2Vec2 gravity(0.f, g_worldGravity);
	gameWorld = new b2World(gravity);
	
	createGround(0.f, 500.f, (float)g_windowWidth, 10.f);
	
}

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
    shape.SetAsBox((800.f/2)/g_P2MScale, (16.f/2)/g_P2MScale);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;
    fixtureDef.shape = &shape;

    body->CreateFixture(&fixtureDef);
}