#include "MapObject.h"


MapObject::MapObject(void)
{}


MapObject::~MapObject(void)
{}


void MapObject::load(b2World* world,
					 const float sizeX,
					 const float sizeY,
					 const float posX,
					 const float posY,
					 const std::string textureDir,
					 const bool hasPhysics,
					 const float bBoxModX,
					 const float bBoxModY)
{
	setSize(sf::Vector2f(sizeX, sizeY));
	setOrigin(sizeX / 2, sizeY / 2);
	setPosition(posX, posY);

	_texture.loadFromFile(textureDir);
	setTexture(&_texture);

	//Phys body
	if (hasPhysics){
		b2BodyDef bodyDef;
		bodyDef.position = b2Vec2(posX/g_P2MScale, posY/g_P2MScale);
		bodyDef.type = b2_staticBody;

		_body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(((sizeX / 2) * bBoxModX) / g_P2MScale, ((sizeY / 2) * bBoxModY) / g_P2MScale);

		b2FixtureDef fixtureDef;
		fixtureDef.density = 0.f;
		fixtureDef.shape = &shape;

		_body->CreateFixture(&fixtureDef);
	}
}