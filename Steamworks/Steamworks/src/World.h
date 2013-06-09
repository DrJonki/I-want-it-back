#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <memory>

#include "Map.h"
#include "Globals.h"

class World : public Map
{
public:
	World(void);
	~World(void);

	void physStep();

	b2World* getWorldPtr() { return gameWorld; };

private:
	void createGround(const float sizeX,
					  const float sizeY,
					  const float posX = 0,
					  const float posY = 0);

protected:
	b2World *gameWorld;
	
};

