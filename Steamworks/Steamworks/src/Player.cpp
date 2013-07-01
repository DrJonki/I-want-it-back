#include "Player.h"



Player::Player(const unsigned short playerNo, LoadSettings& settings)
	: _playerNumber(playerNo)
{
	unloadPlayer();

	_sensorData[SEN_TOP] = (void*)(playerNo * 1);
	_sensorData[SEN_RIGHT] = (void*)(playerNo * 2);
	_sensorData[SEN_BOTTOM] = (void*)(playerNo * 3);
	_sensorData[SEN_LEFT] = (void*)(playerNo * 4);
	_sensorData[SEN_TOPLEFT] = (void*)(playerNo * 5);
	_sensorData[SEN_TOPRIGHT] = (void*)(playerNo * 6);
	_sensorData[SEN_BOTTOMRIGHT] = (void*)(playerNo * 7);
	_sensorData[SEN_BOTTOMLEFT] = (void*)(playerNo * 8);

	loadProperties(settings);
}

Player::~Player(void)
{}

void Player::loadPlayer(sf::RenderWindow* window, b2World* world, ContactListener* lis)
{
	_world = world;
	_cListener = lis;
	_window = window;

	loadAnimations();

	setTexture(animations[ANIM_IDLE].getCurrentTexture());
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	if (_playerNumber == 1) setPosition(g_windowWidth / 2, 250);
	else if (_playerNumber == 2) setPosition(g_windowWidth / 2, 850);


	createPhysBody(1.f, 0.f, 0.f);

	_cListener->addData(_sensorData[SEN_TOP]);
	_cListener->addData(_sensorData[SEN_RIGHT]);
	_cListener->addData(_sensorData[SEN_BOTTOM]);
	_cListener->addData(_sensorData[SEN_LEFT]);
	_cListener->addData(_sensorData[SEN_TOPLEFT]);
	_cListener->addData(_sensorData[SEN_TOPRIGHT]);
	_cListener->addData(_sensorData[SEN_BOTTOMRIGHT]);
	_cListener->addData(_sensorData[SEN_BOTTOMLEFT]);
	
	createSensors();
}

void Player::unloadPlayer()
{
	_world = nullptr;
	_body = nullptr;
	_cListener = nullptr;
	_window = nullptr;

	_playerProps.baseSpeed = 0.f;
	_playerProps.catchingSpeed = 0.f;
	_playerProps.jumpForce = 0.f;
}


void Player::update()
{
	if (animations[ANIM_IDLE].frameChanged()) setTexture(animations[ANIM_IDLE].getCurrentTexture());
	animations[ANIM_IDLE].stepForward();
	animations[ANIM_IDLE].setStepInterval(5);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _cListener->inContact(_sensorData[SEN_BOTTOM])){
		b2Vec2 impulse(0, -_playerProps.jumpForce);
		_body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
	}

	b2Vec2 vel = _body->GetLinearVelocity();
	float desiredVel = 0, maxSpeed = _playerProps.baseSpeed;

	if (_cListener->inContact(_sensorData[SEN_BOTTOM]) || _cListener->inContact(_sensorData[SEN_BOTTOMRIGHT])){
		if (_window->getView().getCenter().x > getPosition().x){
			animations[ANIM_IDLE].setStepInterval(4);
			maxSpeed = _playerProps.catchingSpeed;
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
	t_fixtureDef.userData = _sensorData[0];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Right sensor
	t_shape.SetAsBox(6 / g_P2MScale, (getLocalBounds().height / 8) / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[1];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom sensor
	t_shape.SetAsBox((getLocalBounds().width / 8) / g_P2MScale, 6 / g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[2];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Left sensor
	t_shape.SetAsBox(6 / g_P2MScale, (getLocalBounds().height / 8) / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[3];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);


	//Top-left
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, (-getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[4];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Top-right
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, (-getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[5];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom-right
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((getLocalBounds().height / 2) / g_P2MScale, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[6];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom-left
	t_shape.SetAsBox(6 / g_P2MScale, 6 / g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / g_P2MScale, (getLocalBounds().height / 2) / g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[7];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
}

void Player::loadAnimations()
{
	animations.emplace_back(SpriteAnimation());
	sf::Image playerImage;

	if (_playerNumber == 1){
		playerImage.loadFromFile("Resources/Common/Graphics/Actor/Player/player1.png");
	}
	else if (_playerNumber == 2){
		playerImage.loadFromFile("Resources/Common/Graphics/Actor/Player/player2.png");
	}

	animations[ANIM_IDLE].loadSheet(playerImage, 0, 0, 256, 256, 10);
	animations[ANIM_IDLE].setStepInterval(5);
}

void Player::loadProperties(LoadSettings& settings)
{
	std::string path("Levels/");
	path += settings._campaign;
	path += "/0/playerdata.dat";

	std::ifstream file(path, std::ifstream::in);
	if (!file.good()){
		path = "Levels/Common/Player/playerdata.dat";
		file.open(path, std::ifstream::in);
	}

	if (file.good()){
		std::string tempS;
		float tempF;

		while (!file.eof()){
			file >> tempS;

			if (tempS == "baseSpeed:"){
				file >> tempF;
				_playerProps.baseSpeed = tempF;
			}
			else if (tempS == "catchingSpeed:"){
				file >> tempF;
				_playerProps.catchingSpeed = tempF;
			}
			else if (tempS == "jumpForce:"){
				file >> tempF;
				_playerProps.jumpForce = tempF;
			}
		}
	}

}