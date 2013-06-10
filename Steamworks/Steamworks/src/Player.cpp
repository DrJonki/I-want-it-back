#include "Player.h"


Player::Player(b2World *gameWorld)
{
	animations.emplace_back(SpriteAnimation());

	sf::Image playerImage;
	playerImage.loadFromFile(RES_GRAPHICS_ACTOR "Player/test.png");

	animations[IDLE].loadSheet(playerImage, 0, 0, 128, 128, 4);
	animations[IDLE].setStepInterval(60);

	setTexture(animations[IDLE].getCurrentTexture());
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	setPosition(400, 100);

	createPhysBody(gameWorld, 1.f, 1.f, 0.25f);
}


Player::~Player(void)
{

}

void Player::update()
{
	setTexture(animations[IDLE].getCurrentTexture());
	animations[IDLE].stepForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		b2Vec2 impulse(0, -20);
		body->SetLinearVelocity(impulse);
	}
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

	setPosition(body->GetPosition().x * g_P2MScale, body->GetPosition().y * g_P2MScale);
}
