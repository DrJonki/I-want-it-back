#include "MapObject.h"

#include <Box2D\Dynamics\b2Fixture.h>
#include <Box2D\Collision\Shapes\b2PolygonShape.h>

#include "Globals.h"

MapObject::MapObject(void)
	: _trigData(0),
	  _loop(false),
	  _playing(false)
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
					 const bool smooth,
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
		if (aSizeX <= 0 || aSizeY <= 0) loadSheet(image, startX, startY, sizeX, sizeY, frames, smooth);
		else loadSheet(image, startX, startY, aSizeX, aSizeY, frames, smooth);
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
		if (posY < 600){
			fixtureDef.filter.categoryBits = FIL_LEVEL_TOP;
		}
		else{
			fixtureDef.filter.categoryBits = FIL_LEVEL_BOTTOM;
		}

		_body->CreateFixture(&fixtureDef);

		hbShape.setSize(sf::Vector2f(sizeX * bBoxModX, sizeY * bBoxModY));
		hbShape.setOrigin(hbShape.getSize().x / 2, hbShape.getSize().y / 2);
		hbShape.setPosition(posX, posY);
		hbShape.setFillColor(sf::Color::Color(255, 255, 255, 128));
	}
}