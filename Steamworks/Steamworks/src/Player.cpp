#include "Player.h"


Player::Player(void)
{
	animations.emplace_back(SpriteAnimation());

	sf::Image playerImage;
	playerImage.loadFromFile("Resources/Graphics/Player/test.png");

	animations[IDLE].loadSheet(playerImage, 0, 0, 128, 128, 4);

	//setTexture(animations[IDLE].getCurrentTexture());
}


Player::~Player(void)
{

}

void Player::update()
{
	rotate(1);
	setTexture(animations[IDLE].getCurrentTexture());

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		animations[IDLE].stepForward();
	//}
	//while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
}
