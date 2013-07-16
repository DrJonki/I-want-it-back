#pragma once

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#include "Globals.h"
#include "ContactListener.h"

class Trigger : public sf::RectangleShape
{
public:
	Trigger(void);
	~Trigger(void);

	void load(b2World* world,
			  const float sizeX,
			  const float sizeY,
			  const float posX,
			  const float posY,
			  void* sensorData,
			  const unsigned int resourceType = 0,
			  const unsigned int resourceData = 0);

	//void update();


	b2Body* _body;

	unsigned int _type;

	unsigned int _data;
};

