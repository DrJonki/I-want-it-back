#include "Player.h"


Player::Player(b2World* world)
{
	_world = world;
}


Player::~Player(void)
{}

void Player::update()
{
	//setTexture(animations[IDLE].getCurrentTexture());
	//animations[IDLE].stepForward();

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && cListener.canJump()){
	//	b2Vec2 impulse(0, -10);
	//	_body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
	//}

	//float accel = 120.f;
	//float maxSpeed = 3.f;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && cListener.canJump()){
	//	b2Vec2 force(-accel, 0);
	//	_body->ApplyForceToCenter(force);
	//	//body->ApplyLinearImpulse(force, b2Vec2(0, 0));

	//	if (_body->GetLinearVelocity().x < -maxSpeed){
	//		_body->SetLinearVelocity(b2Vec2(-maxSpeed, 0));
	//	}
	//}

	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && cListener.canJump()){
	//	b2Vec2 force(accel, 0);
	//	_body->ApplyForceToCenter(force);
	//	//body->ApplyLinearImpulse(force, b2Vec2(0, 0));

	//	if (_body->GetLinearVelocity().x > maxSpeed){
	//		_body->SetLinearVelocity(b2Vec2(maxSpeed, 0));
	//	}
	//}

	//setPosition(_body->GetPosition().x * g_P2MScale, _body->GetPosition().y * g_P2MScale);
}


//Private
void Player::createSensor(const int id)
{
	b2FixtureDef auxFix;
	b2PolygonShape shape;
	shape.SetAsBox((getLocalBounds().width / 2) / g_P2MScale, (getLocalBounds().height / 6) / g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / g_P2MScale), 0);

	auxFix.isSensor = true;
	auxFix.shape = &shape;
	auxFix.userData = (void*)id;

	b2Fixture* footSensorFixture = _body->CreateFixture(&auxFix);
}