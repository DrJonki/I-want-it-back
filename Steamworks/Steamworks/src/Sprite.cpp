#include "Sprite.h"


Sprite::Sprite(void){}

Sprite::~Sprite(void){}


void Sprite::loadAnimation(sf::Image &spriteSheet,
						   const int startX,
				           const int startY,
				           const int frameSizeX,
				           const int frameSizeY,
					       const int frameCount)
{
	animations.push_back(SpriteAnimation());

	animations.back().loadSheet(spriteSheet, startX, startY, frameSizeX, frameSizeY, frameCount);
}