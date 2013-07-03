#include "GameButton.h"


GameButton::GameButton(sf::RenderWindow* window)
	: _window(window),
	  wasPressed(false)
{}

GameButton::~GameButton(void)
{}


void GameButton::load(const float sizeX,
					  const float sizeY,
					  const float posX,
					  const float posY,
					  sf::Image& image)
{
	setSize(sf::Vector2f(sizeX, sizeY));
	setPosition(posX, posY);

	loadSheet(image, 0, 0, 200, 100, 3);

	setCurrentFrame(1);
	setTexture(&getCurrentTexture());
}

bool GameButton::isPressed()
{
	update();

	if (wasPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		wasPressed = false;
		return true;
	}
	return false;
}


//Private
void GameButton::update()
{
	if (mouseOnButton() && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		setCurrentFrame(3);
		wasPressed = true;
	}

	else if (mouseOnButton()){
		setCurrentFrame(2);
	}

	else{
		setCurrentFrame(1);
		wasPressed = false;
	}
	
	if (frameChanged()) setTexture(&getCurrentTexture());
	_text.setPosition(getPosition().x + 10, getPosition().y + 10);
}

bool GameButton::mouseOnButton()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*_window);
	sf::Vector2f worldPos = _window->mapPixelToCoords(pixelPos);

	if (worldPos.x > getPosition().x &&
		worldPos.y > getPosition().y &&
		worldPos.x < getPosition().x + getSize().x &&
		worldPos.y < getPosition().y + getSize().y)
	{
		return true;
	}
	return false;
}