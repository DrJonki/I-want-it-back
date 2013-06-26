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
		ANIM_IDLE,
		ANIM_RUNNING,
		ANIM_JUMPING,
		ANIM_FALLING,
		ETC
	};

	//Enumeration for the different sensors
	static const enum
	{
		SEN_TOP,
		SEN_LEFT,
		SEN_BOTTOM,
		SEN_RIGHT,

		SEN_TOPLEFT,
		SEN_TOPRIGHT,
		SEN_BOTTOMRIGHT,
		SEN_BOTTOMLEFT
	};

	void createSensors();
	void loadAnimations();

	ContactListener cListener;
};

