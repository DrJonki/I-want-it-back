#pragma once
#include <Box2D\Box2D.h>
#include <memory>

#include "Map.h"
#include "Globals.h"

class World : public Map
{
public:
	World(void);
	~World(void);


	friend class Sprite;

private:
	void init();
	void createGround(const float sizeX,
					  const float sizeY,
					  const float posX = 0,
					  const float posY = 0);

protected:
	b2World *gameWorld;
	
};

