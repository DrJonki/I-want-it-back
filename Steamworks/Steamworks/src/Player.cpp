#include "Player.h"


Player::Player(b2World* world)
{
	_world = world;

	loadAnimations();

	setTexture(animations[IDLE].getCurrentTexture());
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	setPosition(400, 100);

	createPhysBody(1.f, 1.f, 0.f);
	createSensors();

	_world->SetContactListener(&cListener);
}


Player::~Player(void)
{}

void Player::update()
{
	setTexture(animations[IDLE].getCurrentTexture());
	animations[IDLE].stepForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && cListener.touchingBottom()){
		b2Vec2 impulse(0, -10);
		_body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
	}

	float accel = 120.f;
	float maxSpeed = 5.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && cListener.touchingBottom()){
		//b2Vec2 force(-accel, 0);
		//_body->ApplyForceToCenter(force);
		//body->ApplyLinearImpulse(force, b2Vec2(0, 0));
		
		_body->SetLinearVelocity(b2Vec2(-maxSpeed, 0));

		//if (_body->GetLinearVelocity().x < -maxSpeed){
		//	_body->SetLinearVelocity(b2Vec2(-maxSpeed, 0));
		//}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && cListener.touchingBottom()){
		//b2Vec2 force(accel, 0);
		//_body->ApplyForceToCenter(force);
		//body->ApplyLinearImpulse(force, b2Vec2(0, 0));

		_body->SetLinearVelocity(b2Vec2(maxSpeed, 0));

		//if (_body->GetLinearVelocity().x > maxSpeed){
		//	_body->SetLinearVelocity(b2Vec2(maxSpeed, 0));
		//}
	}

	setPosition(_body->GetPosition().x * g_P2MScale, _body->GetPosition().y * g_P2MScale);
}


//Private
void Player::createSensors()
{
	b2FixtureDef t_fixtureDef;
	b2PolygonShape t_shape;
	b2Fixture* t_sensorFixture;

	//Common properties
	t_fixtureDef.isSensor = true;


	//Top sensor
	t_shape.SetAsBox(4 / g_P2MScale, (getLocalBounds().height / 6) / g_P2MScale, b2Vec2(0, (-getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_TOP;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Left sensor
	t_shape.SetAsBox((getLocalBounds().width / 6) / g_P2MScale, 4 / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_LEFT;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom sensor
	t_shape.SetAsBox(4 / g_P2MScale, (getLocalBounds().height / 6) / g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_BOTTOM;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Right sensor
	t_shape.SetAsBox((getLocalBounds().width / 6) / g_P2MScale, 4 / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_LEFT;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
}

void Player::loadAnimations()
{
	animations.emplace_back(SpriteAnimation());

	sf::Image playerImage;
	playerImage.loadFromFile("Resources/Default/1/Graphics/Actor/Player/placeolderSpriteshit.png");

	animations[IDLE].loadSheet(playerImage, 0, 0, 267, 384, 10);
	animations[IDLE].setStepInterval(6);
}