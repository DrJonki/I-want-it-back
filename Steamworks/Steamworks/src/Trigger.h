#pragma once

#include <Box2D\Box2D.h>

#include "Globals.h"

class Trigger
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

private:
	b2Body* _body;

	unsigned int _type;

	unsigned int _data;
};

