#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Globals.h"
#include "SpriteAnimation.h"

class MapObject : public sf::RectangleShape, public SpriteAnimation
{
public:
	MapObject(void);

	~MapObject(void);

	void load(b2World* world,
			  const float sizeX,
			  const float sizeY,
			  const float posX,
			  const float posY,
			  const bool hasPhysics,
			  const std::string textureDir,
			  const int aSizeX = 0,
			  const int aSizeY = 0,
			  const int startX = 0,
			  const int startY = 0,
			  const unsigned int interval = 1,
			  const unsigned int frames = 1,
			  const float bBoxModX = 1.0f,
			  const float bBoxModY = 1.0f);

	void update(){
		stepForward();
		if (frameChanged()) setTexture(&getCurrentTexture());
	};

	unsigned int _data;

private:
	b2Body* _body;
};