#include "Sprite.h"

#include "Globals.h"


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
							const unsigned int playerNumber,
							const bool fixedAngle)
{
	b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(getPosition().x / ns::g_P2MScale, getPosition().y / ns::g_P2MScale);

	_body = _world->CreateBody(&bodyDef);

	b2CircleShape physShape;
	physShape.m_radius = (getLocalBounds().height / 4) / ns::g_P2MScale;
	
	b2FixtureDef fixtureDef;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.shape = &physShape;

	//Bottom
	if (playerNumber == 1){
		fixtureDef.filter.categoryBits = FIL_PLAYERBOTTOM_TOP;
		fixtureDef.filter.maskBits = FIL_LEVEL_TOP;
	}
	else if (playerNumber == 2){
		fixtureDef.filter.categoryBits = FIL_PLAYERBOTTOM_BOTTOM;
		fixtureDef.filter.maskBits = FIL_LEVEL_BOTTOM;
	}
	physShape.m_p = b2Vec2(0, (getLocalBounds().height * 0.25) / ns::g_P2MScale);
	bottomFixture = _body->CreateFixture(&fixtureDef);
    
	//Top
	if (playerNumber == 1){
		fixtureDef.filter.categoryBits = FIL_PLAYERTOP_TOP;
		fixtureDef.filter.maskBits = FIL_LEVEL_TOP;
	}
	else if (playerNumber == 2){
		fixtureDef.filter.categoryBits = FIL_PLAYERTOP_BOTTOM;
		fixtureDef.filter.maskBits = FIL_LEVEL_BOTTOM;
	}
	physShape.m_p = b2Vec2(0, -(getLocalBounds().height * 0.25) / ns::g_P2MScale);
	topFixture = _body->CreateFixture(&fixtureDef);
	

	_body->SetFixedRotation(fixedAngle);
}