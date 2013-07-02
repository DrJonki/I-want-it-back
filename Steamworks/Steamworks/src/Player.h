#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <Box2D\Box2D.h>

#include <sstream>
#include <fstream>

#include "Sprite.h"
#include "ContactListener.h"
#include "EngineSettings.h"
#include "LoadSettings.h"
#include "Globals.h"

class Player : public Sprite
{
public:
	Player(const unsigned short playerNo, LoadSettings& settings);
	~Player(void);

	void loadPlayer(sf::RenderWindow* window, b2World* world, ContactListener* lis, EngineSettings& settings);
	void unloadPlayer();
	void createSensors();

	void update();
private:
	const unsigned short _playerNumber;
	void* _sensorData[8];

	void loadAnimations(LoadSettings& settings);
	void loadProperties(LoadSettings& settings);

	void updateAnimation();

	struct
	{
		float sizeX,
			  sizeY,
			  baseSpeed,
			  catchingSpeed,
			  jumpForce,
			  airDrag;

	} _playerProps;

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
		ANIM_RUNNING,
		ANIM_JUMPING,
		ETC
	};
};

