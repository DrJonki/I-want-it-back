#pragma once

#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\System\Clock.hpp>

#include "Sprite.h"
#include "EngineSettings.h"
#include "LoadSettings.h"

class Player : public Sprite
{
public:
	Player(const unsigned short playerNo, LoadSettings& lsettings, EngineSettings& esettings);
	~Player(void);

	void loadPlayer(sf::RenderWindow* window, b2World* world, ContactListener* lis);
	void unloadPlayer();
	void createSensors();

	void update();

	void resetClocks();

	std::vector<sf::RectangleShape> sensorShape;
private:
	const unsigned short _playerNumber;
	void* _sensorData[11];

	void loadAnimations(LoadSettings& lsettings, EngineSettings& esettings);
	void loadProperties(LoadSettings& settings);

	void updateAnimation();

	sf::Clock hangTime;
	sf::Clock somersaultTime;

	//Sounds
	sf::SoundBuffer _stepSoundBuffer;
	sf::Sound _stepSound;

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
		SEN_MIDDLE,

		SEN_TOP,
		SEN_BOTTOM,
		SEN_TOPRIGHT,
		SEN_BOTTOMRIGHT,
		SEN_BOTTOMLEFT,
		SEN_TOPLEFT,

		SEN_TOPLEFT_CORNER,
		SEN_TOPRIGHT_CORNER,
		SEN_BOTTOMRIGHT_CORNER,
		SEN_BOTTOMLEFT_CORNER,

		SEN_LAST
	};

	//Enumeration for the different animation states
	static const enum
	{
		ANIM_RUNNING,
		ANIM_JUMPING,
		ANIM_SOMERSAULT,
		ANIM_LEDGEGRAB,
		ANIM_LAST
	};

	int animState;

	unsigned int animationState;
};