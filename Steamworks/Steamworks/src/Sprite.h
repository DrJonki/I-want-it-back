#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

#include "Globals.h"
#include "SpriteAnimation.h"

class Sprite : public sf::Sprite
{
public:
	Sprite(void);
	~Sprite(void);

private:

protected:
	std::vector<SpriteAnimation> animations;
	b2Body *body;

	void createPhysBody(b2World *gameWorld);
};
