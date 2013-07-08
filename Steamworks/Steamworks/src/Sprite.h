#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

#include "Globals.h"
#include "SpriteAnimation.h"
#include "ContactListener.h"

class Sprite : public sf::RectangleShape
{
public:
	Sprite(void);
	~Sprite(void);

	void resetAnimations(const unsigned int);

private:

protected:
	std::vector<SpriteAnimation> animations;

	//Pointers to access sprite's Box2D elements
	b2Fixture* topFixture;
	b2Fixture* bottomFixture;
	b2Body* _body;
	b2World* _world;
	sf::RenderWindow* _window;
	ContactListener* _cListener;

	void createPhysBody(const float density,
						const float friction,
						const float restitution,
						const unsigned int playerNumber,
						const float bBoxModX = 1.f,
						const float bBoxModY = 1.f,
						const bool fixedAngle = true);
};
