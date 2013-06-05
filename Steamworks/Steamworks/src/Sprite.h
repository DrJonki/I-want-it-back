#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Box2D/Box2D.h>
#include <vector>

#include "SpriteAnimation.h"

class Sprite : public sf::Sprite
{
public:
	Sprite(void);
	~Sprite(void);

	void draw(sf::RenderWindow &window);
private:

};

