#pragma once

#include <SFML\Graphics.hpp>

#include "SpriteAnimation.h"
#include "RichText.hpp"

class GameButton : public SpriteAnimation, public sf::RectangleShape
{
public:
	GameButton(sf::RenderWindow*);
	~GameButton(void);

	void load(const float sizeX,
			  const float sizeY,
			  const float posX,
			  const float posY,
			  sf::Image& image);

	bool isPressed();
	void update();

	sf::Text _text;

private:
	bool mouseOnButton();

	bool wasPressed;

	sf::RenderWindow* _window;
};