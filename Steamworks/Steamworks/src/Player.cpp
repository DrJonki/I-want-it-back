#include "Player.h"


Player::Player(b2World *gameWorld)
{
	world = gameWorld;

	animations.emplace_back(SpriteAnimation());

	sf::Image playerImage;
	playerImage.loadFromFile(RES_GRAPHICS_ACTOR "Player/test.png");

	animations[IDLE].loadSheet(playerImage, 0, 0, 128, 128, 4);
	animations[IDLE].setStepInterval(60);

	setTexture(animations[IDLE].getCurrentTexture());
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	setPosition(400, 100);

	createPhysBody(world, 1.f, 1.f, 0.f, 1.0f);
	createSensor();
}


Player::~Player(void)
{
	
}

void Player::update()
{
	setTexture(animations[IDLE].getCurrentTexture());
	animations[IDLE].stepForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		b2Vec2 force(0, -20);
		body->SetLinearVelocity(force);
	}

	float accel = 10.f;
	float maxSpeed = 10.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if (body->GetLinearVelocity().x > -maxSpeed){
			b2Vec2 force(-accel, 0);
			b2Vec2 point(0, 0);
			body->ApplyLinearImpulse(force, point);
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if (body->GetLinearVelocity().x < maxSpeed){
			b2Vec2 force(accel, 0);
			b2Vec2 point(0, 0);
			body->ApplyLinearImpulse(force, point);
		}
	}

	setPosition(body->GetPosition().x * g_P2MScale, body->GetPosition().y * g_P2MScale);
}


//Private
void Player::createSensor()
{
	b2PolygonShape shape;
	shape.SetAsBox((getLocalBounds().width / 3) / g_P2MScale, (getLocalBounds().height / 3) / g_P2MScale);

	auxFix->isSensor = true;
	auxFix->shape = &shape;
	auxFix->userData = (void*)3;

	auxBody->CreateFixture(auxFix);
}