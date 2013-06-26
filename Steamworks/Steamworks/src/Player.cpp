#include "Player.h"


namespace
{

}


Player::Player()
{
	_world = nullptr;
	_body = nullptr;
}


Player::~Player(void)
{}

void Player::loadPlayer(b2World* world)
{
	_world = world;

	loadAnimations();

	setTexture(animations[ANIM_IDLE].getCurrentTexture());
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	setPosition(g_windowWidth / 1.5, 250);

	createPhysBody(1.f, 0.f, 0.f);
	createSensors();

	_world->SetContactListener(&cListener);
}

void Player::unloadPlayer()
{
	_world = nullptr;
	_body = nullptr;
}


void Player::update()
{
	setTexture(animations[ANIM_IDLE].getCurrentTexture());
	animations[ANIM_IDLE].stepForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (cListener.touchingBottom() || cListener.touchingRight())){
		b2Vec2 impulse(0, -200);
		_body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
	}

	b2Vec2 vel = _body->GetLinearVelocity();
    float desiredVel = 0, maxSpeed = 5.2f;

	if (cListener.touchingBottom()){
		//desiredVel = maxSpeed;
		desiredVel = b2Max(vel.x + 0.1f, maxSpeed);
	}
	else{
		desiredVel = vel.x * 0.99f;
	}
	
    float velChange = desiredVel - vel.x;
    float impulse = _body->GetMass() * velChange; //disregard time factor
    _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());

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
	t_shape.SetAsBox((getLocalBounds().width / 8) / g_P2MScale, 6 / g_P2MScale, b2Vec2(0, (-getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_TOP;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Left sensor
	t_shape.SetAsBox(6 / g_P2MScale, (getLocalBounds().height / 8) / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_LEFT;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom sensor
	t_shape.SetAsBox((getLocalBounds().width / 8) / g_P2MScale, 6 / g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_BOTTOM;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Right sensor
	t_shape.SetAsBox(6 / g_P2MScale, (getLocalBounds().height / 8) / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)SEN_LEFT;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
}

void Player::loadAnimations()
{
	animations.emplace_back(SpriteAnimation());

	sf::Image playerImage;
	playerImage.loadFromFile("Resources/Common/Graphics/Actor/Player/player1.png");

	animations[ANIM_IDLE].loadSheet(playerImage, 0, 0, 256, 256, 10);
	animations[ANIM_IDLE].setStepInterval(5);
}