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

	//Enumeration for the different animation states
	static const enum
	{
		IDLE, //IDLE2, IDLE3, etc.
		
		WALKING_LEFT,
		WALKING_RIGHT,
		RUNNING_LEFT,
		RUNNING_RIGHT,

		CROUCHING_LEFT,
		CROUCHING_RIGHT,
		JUMPING_LEFT,
		JUMPING_RIGHT,
		SHOOTING_LEFT,
		SHOOTING_RIGHT
	};

};
