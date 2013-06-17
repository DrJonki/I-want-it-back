#include "MapObject.h"


MapObject::MapObject(const float sizeX,
					 const float sizeY,
					 const float posX,
					 const float posY,
					 const std::string textureDir,
					 const float bBoxModX,
					 const float bBoxModY)
{
	_shape.setSize(sf::Vector2f(sizeX, sizeY));
	_shape.setOrigin(sizeX / 2, sizeY / 2);
	_shape.setPosition(posX, posY);

	_texture.loadFromFile(textureDir);
	_shape.setTexture(&_texture);

	//Phys body
	b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(posX/g_P2MScale, posY/g_P2MScale);
    bodyDef.type = b2_staticBody;

	_body = _world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(((sizeX / 2) * bBoxModX) / g_P2MScale, ((sizeY / 2) * bBoxModY) / g_P2MScale);

	b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;
    fixtureDef.shape = &shape;

	_body->CreateFixture(&fixtureDef);
}


MapObject::~MapObject(void)
{
}