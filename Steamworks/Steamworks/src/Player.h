#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <Box2D\Box2D.h>

#include "Sprite.h"
#include "ContactListener.h"

class Player : public Sprite
{
public:
	Player(b2World *gameWorld);
	~Player(void);


	void update();
private:
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

	void createSensor(const int);
	void loadAnimations();


	ContactListener cListener;
};

