#include "Sprite.h"


Sprite::Sprite(void)
{

}

Sprite::~Sprite(void){}

//Public

//Private

//Protected
void Sprite::createPhysBody(b2World *gameWorld,
							const float density,
							const float friction,
							const float restitution,
							const bool fixedAngle)
{
	bodyDef = new b2BodyDef;
	bodyDef->position = b2Vec2(getPosition().x / g_P2MScale, getPosition().y / g_P2MScale);
    bodyDef->type = b2_dynamicBody;

    body = gameWorld->CreateBody(bodyDef);

    physShape = new b2PolygonShape;
	physShape->SetAsBox(((getLocalBounds().width) / 2) / g_P2MScale, ((getLocalBounds().height) / 2) / g_P2MScale);

    fixtureDef = new b2FixtureDef;
    fixtureDef->density = density;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
    fixtureDef->shape = physShape;

	body->SetFixedRotation(fixedAngle);
    body->CreateFixture(fixtureDef);
}