#include "Player.h"



Player::Player(const unsigned short playerNo, LoadSettings& lsettings, EngineSettings& esettings)
	: _playerNumber(playerNo),
	  hitGround(false),
	  animationState(0)
{
	unloadPlayer();

	_sensorData[SEN_MIDDLE] = (void*)((playerNo * 1) + ((playerNo - 1) * 10));
	_sensorData[SEN_TOP] = (void*)((playerNo * 2) + ((playerNo - 1) * 10));
	_sensorData[SEN_BOTTOM] = (void*)((playerNo * 3) + ((playerNo - 1) * 10));
	_sensorData[SEN_TOPRIGHT] = (void*)((playerNo * 4) + ((playerNo - 1) * 10));
	_sensorData[SEN_BOTTOMRIGHT] = (void*)((playerNo * 5) + ((playerNo - 1) * 10));
	_sensorData[SEN_BOTTOMLEFT] = (void*)((playerNo * 6) + ((playerNo - 1) * 10));
	_sensorData[SEN_TOPLEFT] = (void*)((playerNo * 7) + ((playerNo - 1) * 10));
	_sensorData[SEN_TOPLEFT_CORNER] = (void*)((playerNo * 8) + ((playerNo - 1) * 10));
	_sensorData[SEN_TOPRIGHT_CORNER] = (void*)((playerNo * 9) + ((playerNo - 1) * 10));
	_sensorData[SEN_BOTTOMRIGHT_CORNER] = (void*)((playerNo * 10) + ((playerNo - 1) * 10));
	_sensorData[SEN_BOTTOMLEFT_CORNER] = (void*)((playerNo * 11) + ((playerNo - 1) * 10));

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
	if (_playerNumber == 1) setPosition(ns::spawnPoint, 250);
	else if (_playerNumber == 2) setPosition(ns::spawnPoint, 850);


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

	if (_cListener->inContact(_sensorData[SEN_BOTTOM])){
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



	//Sensor shapes
	for (unsigned int i = 0; i < sensorShape.size(); i++){
		if (_cListener->inContact(_sensorData[i])) sensorShape[i].setFillColor(sf::Color::Red);
		else sensorShape[i].setFillColor(sf::Color::Cyan);
	}

	sensorShape[0].setPosition(getPosition().x, getPosition().y);
	sensorShape[1].setPosition(getPosition().x, getPosition().y - (getLocalBounds().height / 2));
	sensorShape[2].setPosition(getPosition().x, getPosition().y + (getLocalBounds().height / 2));
	sensorShape[3].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 4));
	sensorShape[4].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 4));
	sensorShape[5].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 4));
	sensorShape[6].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 4));
	sensorShape[7].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 2));
	sensorShape[8].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 2));
	sensorShape[9].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 2));
	sensorShape[10].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 2));
}


//Private
void Player::createSensors()
{
	for (int i = 0; i < SEN_LAST; i++){
		sensorShape.emplace_back(sf::RectangleShape());

		sensorShape.back().setFillColor(sf::Color::Cyan);
	}

	b2FixtureDef t_fixtureDef;
	b2PolygonShape t_shape;
	b2Fixture* t_sensorFixture;

	//Common properties
	t_fixtureDef.isSensor = true;


	//Main fixture, used for triggers
	t_shape.SetAsBox((getLocalBounds().width / 3) / ns::g_P2MScale, (getLocalBounds().height / 3) / ns::g_P2MScale);
	t_fixtureDef.shape = &t_shape;
	if (_playerNumber == 1)
		t_fixtureDef.userData = (void*)MAINFIX_P1;
	else if (_playerNumber == 2)
		t_fixtureDef.userData = (void*)MAINFIX_P2;
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);


	//Middle sensor
	t_shape.SetAsBox((getLocalBounds().height / 8) / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2(0, 0), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[0];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[0].setSize(sf::Vector2f(getLocalBounds().height / 8, 6));
	sensorShape[0].setOrigin(sensorShape[0].getSize().x / 2, sensorShape[0].getSize().y / 2);
	sensorShape[0].setPosition(getPosition().x, getPosition().y);

	//Top sensor
	t_shape.SetAsBox((getLocalBounds().width / 8) / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2(0, (-getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[1];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[1].setSize(sf::Vector2f(getLocalBounds().height / 8, 6));
	sensorShape[1].setOrigin(sensorShape[1].getSize().x / 2, sensorShape[1].getSize().y / 2);
	sensorShape[1].setPosition(getPosition().x, getPosition().y - (getLocalBounds().height / 2));
	//Bottom sensor
	t_shape.SetAsBox((getLocalBounds().width / 8) / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2(0, (getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[2];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[2].setSize(sf::Vector2f(getLocalBounds().height / 8, 6));
	sensorShape[2].setOrigin(sensorShape[2].getSize().x / 2, sensorShape[2].getSize().y / 2);
	sensorShape[2].setPosition(getPosition().x, getPosition().y + (getLocalBounds().height / 2));


	//Topright sensor
	t_shape.SetAsBox(6 / ns::g_P2MScale, (getLocalBounds().height / 8) / ns::g_P2MScale, b2Vec2((getLocalBounds().height / 4) / ns::g_P2MScale, (-getLocalBounds().height / 4) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[3];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[3].setSize(sf::Vector2f(6, getLocalBounds().height / 8));
	sensorShape[3].setOrigin(sensorShape[3].getSize().x / 2, sensorShape[3].getSize().y / 2);
	sensorShape[3].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 4));
	//Bottomright sensor
	t_shape.SetAsBox(6 / ns::g_P2MScale, (getLocalBounds().height / 8) / ns::g_P2MScale, b2Vec2((getLocalBounds().height / 4) / ns::g_P2MScale, (getLocalBounds().height / 4) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[4];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[4].setSize(sf::Vector2f(6, getLocalBounds().height / 8));
	sensorShape[4].setOrigin(sensorShape[4].getSize().x / 2, sensorShape[4].getSize().y / 2);
	sensorShape[4].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 4));


	//Bottomleft sensor
	t_shape.SetAsBox(6 / ns::g_P2MScale, (getLocalBounds().height / 8) / ns::g_P2MScale, b2Vec2((-getLocalBounds().height / 4) / ns::g_P2MScale, (getLocalBounds().height / 4) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[5];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[5].setSize(sf::Vector2f(6, getLocalBounds().height / 8));
	sensorShape[5].setOrigin(sensorShape[5].getSize().x / 2, sensorShape[5].getSize().y / 2);
	sensorShape[5].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 4));
	//Topleft sensor
	t_shape.SetAsBox(6 / ns::g_P2MScale, (getLocalBounds().height / 8) / ns::g_P2MScale, b2Vec2((-getLocalBounds().height / 4) / ns::g_P2MScale, (-getLocalBounds().height / 4) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[6];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[6].setSize(sf::Vector2f(6, getLocalBounds().height / 8));
	sensorShape[6].setOrigin(sensorShape[6].getSize().x / 2, sensorShape[6].getSize().y / 2);
	sensorShape[6].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 4));




	//Top-left corner
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((-getLocalBounds().height / 4) / ns::g_P2MScale, (-getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[7];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[7].setSize(sf::Vector2f(6, 6));
	sensorShape[7].setOrigin(sensorShape[7].getSize().x / 2, sensorShape[7].getSize().y / 2);
	sensorShape[7].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 2));

	//Top-right corner
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((getLocalBounds().height / 4) / ns::g_P2MScale, (-getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[8];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[8].setSize(sf::Vector2f(6, 6));
	sensorShape[8].setOrigin(sensorShape[8].getSize().x / 2, sensorShape[8].getSize().y / 2);
	sensorShape[8].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y - (getLocalBounds().height / 2));

	//Bottom-right corner
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((getLocalBounds().height / 4) / ns::g_P2MScale, (getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[9];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[9].setSize(sf::Vector2f(6, 6));
	sensorShape[9].setOrigin(sensorShape[9].getSize().x / 2, sensorShape[9].getSize().y / 2);
	sensorShape[9].setPosition(getPosition().x + (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 2));

	//Bottom-left corner
	t_shape.SetAsBox(6 / ns::g_P2MScale, 6 / ns::g_P2MScale, b2Vec2((-getLocalBounds().height / 4) / ns::g_P2MScale, (getLocalBounds().height / 2) / ns::g_P2MScale), 0);
	t_fixtureDef.shape = &t_shape;
	t_fixtureDef.userData = _sensorData[10];
	t_sensorFixture = _body->CreateFixture(&t_fixtureDef);
	sensorShape[10].setSize(sf::Vector2f(6, 6));
	sensorShape[10].setOrigin(sensorShape[10].getSize().x / 2, sensorShape[10].getSize().y / 2);
	sensorShape[10].setPosition(getPosition().x - (getLocalBounds().height / 4), getPosition().y + (getLocalBounds().height / 2));
}

void Player::loadAnimations(LoadSettings& lsettings, EngineSettings& esettings)
{
	animations.reserve(6);

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
			else if (tempS == "cameraSpeed:"){
				file >> tempF;
				ns::cameraSpeed = tempF;
			}
		}
	}

}