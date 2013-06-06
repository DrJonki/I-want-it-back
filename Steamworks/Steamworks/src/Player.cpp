#include "Player.h"


Player::Player(void)
{

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
