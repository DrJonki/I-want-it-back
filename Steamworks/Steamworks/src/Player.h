#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <Box2D\Box2D.h>

#include "Sprite.h"
#include "ContactListener.h"

class Player : public Sprite
{
public:
	Player(const unsigned short playerNo);
	~Player(void);

	void loadPlayer(sf::RenderWindow* window, b2World* world, ContactListener* lis);
	void unloadPlayer();
	void createSensors();

	void update();
private:
	const unsigned short _playerNumber;
	unsigned int _sensorData[8];

	void loadAnimations();

	//Anumeration for the sensors
	static const enum
	{
		SEN_TOP,
		SEN_RIGHT,
		SEN_BOTTOM,
		SEN_LEFT,

		SEN_TOPLEFT,
		SEN_TOPRIGHT,
		SEN_BOTTOMRIGHT,
		SEN_BOTTOMLEFT
	};

	//Enumeration for the different animation states
	static const enum
	{
		ANIM_IDLE,
		ANIM_RUNNING,
		ANIM_JUMPING,
		ANIM_FALLING,
		ETC
	};
};

