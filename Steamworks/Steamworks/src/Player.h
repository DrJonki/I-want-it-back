#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>

#include "Sprite.h"

class Player : public Sprite
{
public:
	Player(void);
	~Player(void);


	void update();
private:

};

