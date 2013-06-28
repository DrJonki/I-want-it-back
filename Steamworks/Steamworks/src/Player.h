#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <Box2D\Box2D.h>

#include "Sprite.h"
#include "ContactListener.h"

class Player : public Sprite
{
public:
	Player(const bool firstPlayer);
	~Player(void);

	void loadPlayer(sf::RenderWindow* window, b2World* world, ContactListener* lis);
	void unloadPlayer();
	void createSensors();

	void update();
private:
	std::string _sensorData[8];

	const bool _firstPlayer;

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

