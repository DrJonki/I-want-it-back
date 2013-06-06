#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

#include "SpriteAnimation.h"

class Sprite : public sf::Sprite
{
public:
	Sprite(void);
	~Sprite(void);

	void loadAnimation(sf::Image &sheet,
					   const int startX,
					   const int startY,
				       const int frameSizeX,
					   const int frameSizeY,
					   const int frameCount);

protected:
	std::vector<SpriteAnimation> animations;

};
