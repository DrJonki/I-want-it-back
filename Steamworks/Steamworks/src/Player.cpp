#include "Player.h"



Player::Player(const bool firstPlayer)
	: _firstPlayer(firstPlayer)
{
	unloadPlayer();
}

Player::~Player(void)
{}

void Player::loadPlayer(sf::RenderWindow* window, b2World* world, ContactListener* lis, const int senData[8])
{
	_world = world;
	_cListener = lis;
	_window = window;

	loadAnimations();

	setTexture(animations[ANIM_IDLE].getCurrentTexture());
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	if (_firstPlayer) setPosition(g_windowWidth / 2, 250);
	else setPosition(g_windowWidth / 2, 850);


	createPhysBody(1.f, 0.f, 0.f);

	_sensorData[SEN_TOP] = senData[0];
	_sensorData[SEN_RIGHT] = senData[1];
	_sensorData[SEN_BOTTOM] = senData[2];
	_sensorData[SEN_LEFT] = senData[3];
	_sensorData[SEN_TOPLEFT] = senData[4];
	_sensorData[SEN_TOPRIGHT] = senData[5];
	_sensorData[SEN_BOTTOMRIGHT] = senData[6];
	_sensorData[SEN_BOTTOMLEFT] = senData[7];
	_cListener->addData(senData[0]);
	_cListener->addData(senData[1]);
	_cListener->addData(senData[2]);
	_cListener->addData(senData[3]);
	_cListener->addData(senData[4]);
	_cListener->addData(senData[5]);
	_cListener->addData(senData[6]);
	_cListener->addData(senData[7]);
	
	createSensors();
}

void Player::unloadPlayer()
{
	_world = nullptr;
	_body = nullptr;
	_cListener = nullptr;
	_window = nullptr;
}


void Player::update()
{
	setTexture(animations[ANIM_IDLE].getCurrentTexture());
	animations[ANIM_IDLE].stepForward();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _cListener->inContact(_sensorData[SEN_BOTTOM])){
		b2Vec2 impulse(0, -60);
		_body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
	}

	b2Vec2 vel = _body->GetLinearVelocity();
    float desiredVel = 0, maxSpeed = 5.175f;

	if (_cListener->inContact(_sensorData[SEN_BOTTOM]) || _cListener->inContact(_sensorData[SEN_BOTTOMRIGHT])){
		if (_window->getView().getCenter().x > getPosition().x){
			maxSpeed = 6.f;
			desiredVel = b2Min(vel.x + 0.5f, maxSpeed);
		}
		desiredVel = b2Min(vel.x + 0.3f, maxSpeed);
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
	t_fixtureDef.userData = (void*)_sensorData[0];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Right sensor
	t_shape.SetAsBox(6 / g_P2MScale, (getLocalBounds().height / 8) / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)_sensorData[1];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom sensor
	t_shape.SetAsBox((getLocalBounds().width / 8) / g_P2MScale, 6 / g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)_sensorData[2];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Left sensor
	t_shape.SetAsBox(6 / g_P2MScale, (getLocalBounds().height / 8) / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)_sensorData[3];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);


	//Top-left
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, (-getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)_sensorData[4];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Top-right
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, (-getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)_sensorData[5];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom-right
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)_sensorData[6];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom-left
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = (void*)_sensorData[7];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
}

void Player::loadAnimations()
{
	animations.emplace_back(SpriteAnimation());
	sf::Image playerImage;

	if (_firstPlayer){
		playerImage.loadFromFile("Resources/Common/Graphics/Actor/Player/player1.png");
	}
	else{
		playerImage.loadFromFile("Resources/Common/Graphics/Actor/Player/player2.png");
	}

	animations[ANIM_IDLE].loadSheet(playerImage, 0, 0, 256, 256, 10);
	animations[ANIM_IDLE].setStepInterval(5);
}