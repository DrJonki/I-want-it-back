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

protected:
	std::vector<SpriteAnimation> animations;

};
