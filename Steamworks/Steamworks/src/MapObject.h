#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Globals.h"

class MapObject : public sf::RectangleShape
{
public:
	MapObject(void);

	~MapObject(void);

	void load(b2World* world,
			  const float sizeX,
			  const float sizeY,
			  const float posX,
			  const float posY,
			  const std::string textureDir,
			  const float bBoxModX = 1.0f,
			  const float bBoxModY = 1.0f);

private:
	b2Body* _body;
	
	sf::Texture _texture;
};