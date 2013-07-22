#include "Trigger.h"

#include <Box2D\Dynamics\b2Fixture.h>
#include <Box2D\Collision\Shapes\b2PolygonShape.h>
#include <Box2D\Dynamics\b2World.h>

#include "Globals.h"


Trigger::Trigger(void)
	: _type(0),
	  _data(0)
{}

Trigger::~Trigger(void)
{}


void Trigger::load(b2World* world,
				   const float sizeX,
				   const float sizeY,
				   const float posX,
				   const float posY,
				   void* data,
				   const unsigned int resourceType,
				   const unsigned int resourceData)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(posX / ns::g_P2MScale, posY / ns::g_P2MScale);
	bodyDef.type = b2_staticBody;

    _body = world->CreateBody(&bodyDef);
	
	b2PolygonShape physShape;
	physShape.SetAsBox((sizeX / 2) / ns::g_P2MScale, (sizeY / 2) / ns::g_P2MScale);

    b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.userData = data;
    fixtureDef.shape = &physShape;

	if (posY < 600){
		fixtureDef.filter.categoryBits = FIL_TRIGGERS_TOP;
		fixtureDef.filter.maskBits = FIL_PLAYERMAINFIX_TOP;
	}
	else{
		fixtureDef.filter.categoryBits = FIL_TRIGGERS_BOTTOM;
		fixtureDef.filter.maskBits = FIL_PLAYERMAINFIX_BOTTOM;
	}
	
	_body->SetFixedRotation(true);
    _body->CreateFixture(&fixtureDef);

	_type = resourceType;
	_data = resourceData;

	setSize(sf::Vector2f(sizeX, sizeY));
	setOrigin(sizeX / 2, sizeY / 2);
	setPosition(posX, posY);
	if (data == (void*)TRIG_LETHAL) setFillColor(sf::Color::Color(255, 0, 0, 150));
	else if (data == (void*)TRIG_CHECKPOINT) setFillColor(sf::Color::Color(255, 255, 0, 150));
	else if (data == (void*)TRIG_ENDOFLEVEL) setFillColor(sf::Color::Color(255, 0, 255, 150));
	else if (resourceType == RT_ANIMATION) setFillColor(sf::Color::Color(0, 0, 255, 150));
	else if (resourceType == RT_SOUND) setFillColor(sf::Color::Color(0, 255, 0, 150));
	else setFillColor(sf::Color::Color(0, 0, 0, 255));
}