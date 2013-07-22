#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include <Box2D\Dynamics\b2Body.h>

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


	b2Body* _body;

	unsigned int _type;

	unsigned int _data;
};

