#include "Sprite.h"


Sprite::Sprite(void)
{

}

Sprite::~Sprite(void){}

//Protected
void Sprite::createPhysBody(b2World *gameWorld)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(getPosition().x / g_P2MScale, getPosition().y / g_P2MScale);
    bodyDef.type = b2_dynamicBody;

    body = gameWorld->CreateBody(&bodyDef);

    b2PolygonShape shape;
	shape.SetAsBox(((getLocalBounds().width) / 2) / g_P2MScale, ((getLocalBounds().height) / 2) / g_P2MScale);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.5f;
    fixtureDef.shape = &shape;

    body->CreateFixture(&fixtureDef);
}