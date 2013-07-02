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
			  void* data);

private:
	b2Body* _body;
};

