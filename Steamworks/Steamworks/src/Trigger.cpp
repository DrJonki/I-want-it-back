#include "Trigger.h"


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
	physShape.SetAsBox(sizeX / ns::g_P2MScale, sizeY / ns::g_P2MScale);

    b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.userData = data;
    fixtureDef.shape = &physShape;

	_body->SetFixedRotation(true);
    _body->CreateFixture(&fixtureDef);

	_data = resourceData;
}