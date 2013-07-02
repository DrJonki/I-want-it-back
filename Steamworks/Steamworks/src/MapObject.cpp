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
					 const bool hasPhysics,
					 const std::string textureDir,
					 const int aSizeX,
					 const int aSizeY,
					 const int startX,
					 const int startY,
					 const unsigned int interval,
					 const unsigned int frames,
					 const float bBoxModX,
					 const float bBoxModY)
{
	setSize(sf::Vector2f(sizeX, sizeY));
	setOrigin(sizeX / 2, sizeY / 2);
	setPosition(posX, posY);

	sf::Image image;
	if (image.loadFromFile(textureDir)){
		if (aSizeX <= 0 || aSizeY <= 0) loadSheet(image, startX, startY, sizeX, sizeY, frames);
		else loadSheet(image, startX, startY, aSizeX, aSizeY, frames);
		setStepInterval(interval);
		setTexture(&getCurrentTexture());
	}
	else setFillColor(sf::Color::Transparent);

	//Phys body
	if (hasPhysics){
		b2BodyDef bodyDef;
		bodyDef.position = b2Vec2(posX / ns::g_P2MScale, posY / ns::g_P2MScale);
		bodyDef.type = b2_staticBody;

		_body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(((sizeX / 2) * bBoxModX) / ns::g_P2MScale, ((sizeY / 2) * bBoxModY) / ns::g_P2MScale);

		b2FixtureDef fixtureDef;
		fixtureDef.density = 0.f;
		fixtureDef.friction = 0.f;
		fixtureDef.shape = &shape;

		_body->CreateFixture(&fixtureDef);
	}
}