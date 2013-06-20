#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <Box2D\Box2D.h>

#include "Sprite.h"
#include "ContactListener.h"

class Player : public Sprite
{
public:
	Player();
	~Player(void);

	void loadPlayer(b2World* _world);
	void unloadPlayer();

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

	//Enumeration for the different sensors
	static const enum
	{
		SEN_TOP = 0x11,
		SEN_LEFT = 0x12,
		SEN_BOTTOM = 0x13,
		SEN_RIGHT = 0x14
	};

	void createSensors();
	void loadAnimations();

	ContactListener cListener;
};

