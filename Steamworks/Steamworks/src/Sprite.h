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

	void resetAnimations(const unsigned int);

private:

protected:
	std::vector<SpriteAnimation> animations;

	//Pointers to access sprite's Box2D elements
	b2Body* body;
	b2World* world;

	void createPhysBody(b2World *gameWorld,
						const float density,
						const float friction,
						const float restitution,
						const float offset,
						const bool fixedAngle = true);
};
