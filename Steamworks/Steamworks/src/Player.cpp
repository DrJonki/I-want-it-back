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

	world->SetContactListener(&cListener);
}


Player::~Player(void)
{
	
}

void Player::update()
{
	setTexture(animations[IDLE].getCurrentTexture());
	animations[IDLE].stepForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && cListener.canJump()){
		b2Vec2 impulse(0, -10);
		body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
	}

	float accel = 100.f;
	float maxSpeed = 5.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && cListener.canJump()){
		if (body->GetLinearVelocity().x > -maxSpeed){
			b2Vec2 force(-accel, 0);
			body->ApplyForceToCenter(force);
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && cListener.canJump()){
		if (body->GetLinearVelocity().x < maxSpeed){
			b2Vec2 force(accel, 0);
			body->ApplyForceToCenter(force);
			
		}
	}

	setPosition(body->GetPosition().x * g_P2MScale, body->GetPosition().y * g_P2MScale);
}


//Private
void Player::createSensor()
{
	b2FixtureDef auxFix;
	b2PolygonShape shape;
	shape.SetAsBox((getLocalBounds().width / 2) / g_P2MScale, (getLocalBounds().height / 6) / g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / g_P2MScale), 0);

	auxFix.isSensor = true;
	auxFix.shape = &shape;
	auxFix.userData = (void*)3;

	b2Fixture* footSensorFixture = body->CreateFixture(&auxFix);
}