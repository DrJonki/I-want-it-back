#include "Player.h"



Player::Player(const unsigned short playerNo, LoadSettings& lsettings, EngineSettings& esettings)
	: _playerNumber(playerNo),
	  hitGround(false)
{
	unloadPlayer();

	_sensorData[SEN_MIDDLE] = (void*)(playerNo * 1);
	_sensorData[SEN_TOP] = (void*)(playerNo * 2);
	_sensorData[SEN_BOTTOM] = (void*)(playerNo * 3);
	_sensorData[SEN_TOPRIGHT] = (void*)(playerNo * 4);
	_sensorData[SEN_BOTTOMRIGHT] = (void*)(playerNo * 5);
	_sensorData[SEN_BOTTOMLEFT] = (void*)(playerNo * 6);
	_sensorData[SEN_TOPLEFT] = (void*)(playerNo * 7);
	_sensorData[SEN_TOPLEFT_CORNER] = (void*)(playerNo * 8);
	_sensorData[SEN_TOPRIGHT_CORNER] = (void*)(playerNo * 9);
	_sensorData[SEN_BOTTOMRIGHT_CORNER] = (void*)(playerNo * 10);
	_sensorData[SEN_BOTTOMLEFT_CORNER] = (void*)(playerNo * 11);

	loadProperties(lsettings);
	loadAnimations(lsettings, esettings);
}

Player::~Player(void)
{}

void Player::loadPlayer(sf::RenderWindow* window, b2World* world, ContactListener* lis, EngineSettings& settings)
{
	_world = world;
	_cListener = lis;
	_window = window;

	setSize(sf::Vector2f(_playerProps.sizeX, _playerProps.sizeY));
	setTexture(&animations[ANIM_RUNNING].getCurrentTexture());
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	if (_playerNumber == 1) setPosition((float)settings.resolution.x / 2, 250);
	else if (_playerNumber == 2) setPosition((float)settings.resolution.x / 2, 850);


	createPhysBody(1.f, 0.f, 0.f, _playerNumber);

	_cListener->addData(_sensorData[SEN_MIDDLE]);
	_cListener->addData(_sensorData[SEN_TOP]);
	_cListener->addData(_sensorData[SEN_BOTTOM]);
	_cListener->addData(_sensorData[SEN_TOPRIGHT]);
	_cListener->addData(_sensorData[SEN_BOTTOMRIGHT]);
	_cListener->addData(_sensorData[SEN_BOTTOMLEFT]);
	_cListener->addData(_sensorData[SEN_TOPLEFT]);
	_cListener->addData(_sensorData[SEN_TOPLEFT_CORNER]);
	_cListener->addData(_sensorData[SEN_TOPRIGHT_CORNER]);
	_cListener->addData(_sensorData[SEN_BOTTOMRIGHT_CORNER]);
	_cListener->addData(_sensorData[SEN_BOTTOMLEFT_CORNER]);
	
	createSensors();
}

void Player::unloadPlayer()
{
	_world = nullptr;
	_body = nullptr;
	_cListener = nullptr;
	_window = nullptr;

	_playerProps.sizeX = 0.f;
	_playerProps.sizeY = 0.f;
	_playerProps.baseSpeed = 0.f;
	_playerProps.catchingSpeed = 0.f;
	_playerProps.jumpForce = 0.f;
	_playerProps.airDrag = 0.f;
}


void Player::update()
{
	//Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		if (_cListener->inContact(_sensorData[SEN_BOTTOM])){
			b2Vec2 impulse(0, -_playerProps.jumpForce);
			_body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
		}
		else if (_cListener->inContact(_sensorData[SEN_BOTTOMRIGHT])){
			b2Vec2 impulse(0, -_playerProps.jumpForce / 4);
			_body->ApplyLinearImpulse(impulse, b2Vec2(0, 0));
		}
	}
	//Crouching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || hitGround){
		b2Filter filter = topFixture->GetFilterData();

		filter.maskBits = FIL_NULL;

		topFixture->SetFilterData(filter);
	}
	else{
		b2Filter filter = topFixture->GetFilterData();

		if (_playerNumber == 1) filter.maskBits = FIL_TOPLEVEL;
		else if (_playerNumber == 2) filter.maskBits = FIL_BOTTOMLEVEL;

		topFixture->SetFilterData(filter);
	}



	//Forward movement
	b2Vec2 vel = _body->GetLinearVelocity();
	float desiredVel = 0, maxSpeed = _playerProps.baseSpeed;

	if (_cListener->inContact(_sensorData[SEN_BOTTOM]) || _cListener->inContact(_sensorData[SEN_BOTTOMRIGHT])){
		if (_window->getView().getCenter().x > getPosition().x){
			animations[ANIM_RUNNING].setStepInterval(animations[ANIM_RUNNING].getStepInterval() - 1);
			maxSpeed = _playerProps.catchingSpeed;
			desiredVel = b2Min(vel.x + 0.5f, maxSpeed);
		}
		desiredVel = b2Min(vel.x + 0.3f, maxSpeed);
	}
	else{
		desiredVel = vel.x * (1.f - _playerProps.airDrag);
	}
	


    float velChange = desiredVel - vel.x;
    float impulse = _body->GetMass() * velChange; //disregard time factor
    _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());

	setPosition(_body->GetPosition().x * ns::g_P2MScale, _body->GetPosition().y * ns::g_P2MScale);

	updateAnimation();

	if (_cListener->inContact(_sensorData[SEN_BOTTOM])) hangTime.restart();
}

void Player::updateAnimation()
{
	if ((hangTime.getElapsedTime().asMilliseconds() > 1000 || hitGround) && _cListener->inContact(_sensorData[SEN_BOTTOM])){
		resetAnimations(ANIM_SOMERSAULT);
		if (!animations[ANIM_SOMERSAULT].lastFrame()){
			animations[ANIM_SOMERSAULT].stepForward();
			if (animations[ANIM_SOMERSAULT].frameChanged()) setTexture(&animations[ANIM_SOMERSAULT].getCurrentTexture());
			hitGround = true;
		}
		else hitGround = false;
	}

	else if (!_cListener->inContact(_sensorData[SEN_BOTTOM]) && !_cListener->inContact(_sensorData[SEN_BOTTOMLEFT]) && !_cListener->inContact(_sensorData[SEN_BOTTOMRIGHT])){
		resetAnimations(ANIM_JUMPING);
		if (animations[ANIM_JUMPING].frameChanged()) setTexture(&animations[ANIM_JUMPING].getCurrentTexture());
		if (!animations[ANIM_JUMPING].lastFrame()) animations[ANIM_JUMPING].stepForward();

		hitGround = false;
	}

	else{
		resetAnimations(ANIM_RUNNING);
		if (animations[ANIM_RUNNING].frameChanged()) setTexture(&animations[ANIM_RUNNING].getCurrentTexture());
		animations[ANIM_RUNNING].stepForward();
		animations[ANIM_RUNNING].setStepInterval(5);

		hitGround = false;
	}
}


//Private
void Player::createSensors()
{
	b2FixtureDef t_fixtureDef;
	b2PolygonShape t_shape;
	b2Fixture* t_sensorFixture;

	//Common properties
	t_fixtureDef.isSensor = true;


	//Main fixture, used for triggers
	t_shape.SetAsBox((getLocalBounds().width / 2) / ns::g_P2MScale, (getLocalBounds().height / 2) / ns::g_P2MScale);
	t_fixtureDef.shape = &t_shape;
	if (_playerNumber == 1)
		t_fixtureDef.userData = (void*)MAINFIX_P1;
	else if (_playerNumber == 2)
		t_fixtureDef.userData = (void*)MAINFIX_P2;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);


	//Top sensor
	t_shape.SetAsBox((getLocalBounds().width / 8) / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2(0, (-getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[0];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Right sensor
	t_shape.SetAsBox(6 / ns::g_P2MScale, (getLocalBounds().height / 8) / ns::g_P2MScale, b2Vec2((getLocalBounds().height / 2) / ns::g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[1];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom sensor
	t_shape.SetAsBox((getLocalBounds().width / 8) / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[2];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Left sensor
	t_shape.SetAsBox(6 / ns::g_P2MScale, (getLocalBounds().height / 8) / ns::g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / ns::g_P2MScale, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[3];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);


	//Top-left
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / ns::g_P2MScale, (-getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[4];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Top-right
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((getLocalBounds().height / 2) / ns::g_P2MScale, (-getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[5];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom-right
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((getLocalBounds().height / 2) / ns::g_P2MScale, (getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[6];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);

	//Bottom-left
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((-getLocalBounds().height / 2) / ns::g_P2MScale, (getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[7];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
}

void Player::loadAnimations(LoadSettings& lsettings, EngineSettings& esettings)
{
	animations.reserve(3);

	std::string path("Levels/");
	path += (char)lsettings._campaign;
	path += "/0/playeranimdata.dat";

	std::ifstream file(path, std::ifstream::in);
	if (!file.good()){
		path = "Levels/Common/Player/playeranimdata.dat";
		file.open(path, std::ifstream::in);
	}

	if (file.good()){
		int t_animNo = 0;

		while (!file.eof()){
			int t_playerNo = 0;
			file >> t_playerNo;

			if (_playerNumber == t_playerNo){
				sf::Image playerImage;
				std::string t_textureDir;
				int t_sizeX = 0, t_sizeY = 0, t_startX = 0, t_startY = 0, t_interval = 1, t_frames = 1;

				file >> t_textureDir;
				file >> t_sizeX;
				file >> t_sizeY;
				file >> t_startX;
				file >> t_startY;
				file >> t_interval;
				file >> t_frames;
				
				animations.emplace_back(SpriteAnimation());
				playerImage.loadFromFile(t_textureDir);
				animations[t_animNo].loadSheet(playerImage, t_startX, t_startY, t_sizeX, t_sizeY, t_frames, esettings.smoothTextures);
				animations[t_animNo].setStepInterval(t_interval);

				t_animNo++;
			}
			else file.ignore(256, '\n');
		}
	}
}

void Player::loadProperties(LoadSettings& settings)
{
	std::string path("Levels/");
	path += (char)settings._campaign;
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

			if (tempS == "sizeX:"){
				file >> tempF;
				_playerProps.sizeX = tempF;
			}
			else if (tempS == "sizeY:"){
				file >> tempF;
				_playerProps.sizeY = tempF;
			}
			else if (tempS == "baseSpeed:"){
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
			else if (tempS == "airDrag:"){
				file >> tempF;
				_playerProps.airDrag = tempF;
			}
		}
	}

}