#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <memory>

#include "GameText.h"

class GameButton
{
public:
	GameButton(void);
	~GameButton(void);

	void setTexture(const unsigned short forState, sf::Texture texture);
	void setText(std::string &text);
	void setPosition(const float posX, const float posY);
	void setSize(const float sizeX, const float sizeY);

	bool isActivateable() { return _activateable; };
	void setActivateable(const bool activateable) { _activateable = activateable; };

	void assignButton(sf::Keyboard::Key &key);

	bool isPressed();

	void draw(sf::RenderWindow &window);
	
private:
	bool mouseOnButton();

	std::unique_ptr<sf::Keyboard::Key> _assignedButton; //A keyboard button assigned to the button
	std::unique_ptr<sf::Texture> _buttonTexture[3]; //0. Button not highlighted or pressed
													//1. Button highlighted but not pressed
													//2. Button pressed

	GameText _buttonText;
	bool _activateable;
};