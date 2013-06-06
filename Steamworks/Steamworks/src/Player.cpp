#include "Player.h"


Player::Player(void)
{
	sf::Image playerImage;
	playerImage.loadFromFile("Resources/Graphics/Player/test.png");

	animations[0].loadSheet(playerImage, 0, 0, 128, 128, 4);
}


Player::~Player(void)
{
}

void Player::update()
{
	setTexture(animations[0].getCurrentTexture());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) animations[0].stepForward();
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
}
