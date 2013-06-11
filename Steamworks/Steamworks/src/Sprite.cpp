#include "Sprite.h"


Sprite::Sprite(void)
{
	world->SetContactListener(&cListener);
}

Sprite::~Sprite(void)
{
	world->DestroyBody(body);
}

//Public
void Sprite::resetAnimations(const unsigned int exception)
{
	for (int i = 0; i < animations.size(); i++){
		if (i != exception) animations[i].setCurrentFrame(1);
	}
}


//Private

//Protected
void Sprite::createPhysBody(b2World *gameWorld,
							const float density,
							const float friction,
							const float restitution,
							const float offset,
							const bool fixedAngle)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(getPosition().x / g_P2MScale, getPosition().y / g_P2MScale);
    bodyDef.type = b2_dynamicBody;

    body = gameWorld->CreateBody(&bodyDef);
	
    b2PolygonShape physShape;
	physShape.SetAsBox((((getLocalBounds().width) / 2) * offset) / g_P2MScale, (((getLocalBounds().height) / 2) * offset) / g_P2MScale);

    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
    fixtureDef.shape = &physShape;

	body->SetFixedRotation(fixedAngle);
    body->CreateFixture(&fixtureDef);
}