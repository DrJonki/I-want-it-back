#include "Sprite.h"


Sprite::Sprite(void)
{}

Sprite::~Sprite(void)
{}

//Public
void Sprite::resetAnimations(const unsigned int exception)
{
	for (unsigned int i = 0; i < animations.size(); i++){
		if (i != exception) animations[i].setCurrentFrame(1);
	}
}


//Private

//Protected
void Sprite::createPhysBody(const float density,
							const float friction,
							const float restitution,
							const float bBoxModX,
							const float bBoxModY,
							const bool fixedAngle)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(getPosition().x / g_P2MScale, getPosition().y / g_P2MScale);
    bodyDef.type = b2_dynamicBody;

    _body = _world->CreateBody(&bodyDef);
	
	b2CircleShape physShape;
	physShape.m_radius = (getLocalBounds().width / 2) / g_P2MScale;

    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
    fixtureDef.shape = &physShape;

	_body->SetFixedRotation(fixedAngle);
    _body->CreateFixture(&fixtureDef);
}