#pragma once

#include <SFML\Graphics.hpp>

#include "SpriteAnimation.h"

class ForegroundObject : public sf::RectangleShape, public SpriteAnimation
{
public:
	ForegroundObject(void);
	~ForegroundObject(void);

	void load(const float sizeX,
			  const float sizeY,
			  const float posX,
			  const float posY,
			  const std::string textureDir,
			  const int aSizeX = 0,
			  const int aSizeY = 0,
			  const int startX = 0,
			  const int startY = 0,
			  const unsigned int interval = 1,
			  const unsigned int frames = 1);

	void update(){
		stepForward();
		if (frameChanged()) setTexture(&getCurrentTexture());
	};

	unsigned int _data;
};