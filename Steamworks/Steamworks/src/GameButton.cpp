#include "GameButton.h"

#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>


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

	loadSheet(image, 0, 0, image.getSize().x / 3, image.getSize().y, 3, true);

	setCurrentFrame(1);
	setTexture(&getCurrentTexture());
}

bool GameButton::isPressed()
{
	if (wasPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		wasPressed = false;
		return true;
	}
	return false;
}


//Private
void GameButton::update(const bool selected)
{
	if (selected && ((mouseOnButton() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))){
		setCurrentFrame(3);
		wasPressed = true;
	}

	else if (selected){
		setCurrentFrame(2);
	}

	else{
		setCurrentFrame(1);
	}
	
	if (frameChanged()) setTexture(&getCurrentTexture());
	_text.setPosition(getPosition().x + 10, getPosition().y + 10);
}

bool GameButton::mouseOnButton()
{
	sf::Vector2f worldPos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));

	if (worldPos.x > getPosition().x - getOrigin().x &&
		worldPos.y > getPosition().y - getOrigin().y &&
		worldPos.x < getPosition().x + getSize().x - getOrigin().x &&
		worldPos.y < getPosition().y + getSize().y - getOrigin().y)
	{
		return true;
	}
	return false;
}