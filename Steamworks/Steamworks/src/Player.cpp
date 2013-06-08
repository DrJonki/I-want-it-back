#include "Player.h"


Player::Player(void)
{
	animations.emplace_back(SpriteAnimation());

	sf::Image playerImage;
	playerImage.loadFromFile("Resources/Graphics/Player/test.png");

	animations[IDLE].loadSheet(playerImage, 0, 0, 128, 128, 4);
	animations[IDLE].setStepInterval(60);
	//setTexture(animations[IDLE].getCurrentTexture());
}


Player::~Player(void)
{

}

void Player::update()
{
	rotate(1);
	setTexture(animations[IDLE].getCurrentTexture());

	animations[IDLE].stepForward();
}
