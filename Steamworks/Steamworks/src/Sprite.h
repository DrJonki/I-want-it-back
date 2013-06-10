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

	//Pointers to access sprite's Box2D elements
	b2BodyDef* bodyDef;
	b2PolygonShape* physShape;
	b2FixtureDef* fixtureDef;
	b2Body* body;

	void createPhysBody(b2World *gameWorld,
						const float density,
						const float friction,
						const float restitution,
						const bool fixedAngle = true);
};
