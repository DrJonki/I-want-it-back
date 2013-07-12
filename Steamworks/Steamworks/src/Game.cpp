#include "Game.h"


namespace
{
	bool runningState = false;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock debugUpdateClock;
	sf::Clock updateClock;
	sf::Clock renderClock;

	//Debug numbers
	int d_updateTime = 0.f;
	int d_renderTime = 0.f;

	sf::View view[3];
	
	sf::RectangleShape sShape;

	Mainmenu mainMenu(&gameWindow, &e);
	WorldManager worldManager(&gameWindow);
	Player* player[2];

	unsigned int soundSelection = 1;

	ContactListener* cListener;
}

Game::Game(void)
{}
Game::~Game(void)
{}


bool Game::runAndDontCrashPls()
{
	if (mainMenu.getEngineSettings().debug){
		ns::debug = new DebugConsole;
		ns::debug->draw();
	}
	
	while (mainMenu.showMenu()){
		init();

		while (runningState){
			if (mainMenu.getEngineSettings().vSync){
				if (updateClock.getElapsedTime().asSeconds() > ns::g_updateTimerValue){
					update();
					render();
					pollEvents();
				}
			}
			else {
				if (updateClock.getElapsedTime().asSeconds() > ns::g_updateTimerValue){
					update();
					pollEvents();
				}
				render();
			}
		}
		deInit();
	}

	if (ns::debug != nullptr) delete ns::debug;
	
	return true;
}



void Game::update()
{
	updateClock.restart();

	//Update loop here
	//Player 1
	gameWindow.setView(view[0]);
	player[0]->update();

	//Player 2
	gameWindow.setView(view[1]);
	player[1]->update();

	//Border checks
	if ((player[1]->getPosition().y > 1200 + player[1]->getLocalBounds().height || player[1]->getPosition().x + (player[1]->getLocalBounds().width / 2) < (view[1].getCenter().x - (view[1].getSize().x / 2))) ||
		(player[0]->getPosition().y > 600 + player[0]->getLocalBounds().height || player[0]->getPosition().x + (player[0]->getLocalBounds().width / 2) < (view[0].getCenter().x - (view[0].getSize().x / 2))))
		runningState = false;
	
	worldManager.stepWorldPhysics();

	
	view[0].move(mainMenu.getEngineSettings().cameraSpeed, 0);
	view[1].move(mainMenu.getEngineSettings().cameraSpeed, 0);

	if (player[0]->getPosition().x > view[0].getCenter().x) view[0].setCenter(sf::Vector2f(player[0]->getPosition().x, view[0].getCenter().y));
	if (player[1]->getPosition().x > view[1].getCenter().x) view[1].setCenter(sf::Vector2f(player[1]->getPosition().x, view[1].getCenter().y));

	sf::Listener::setDirection(sf::Vector3f(1.f, 0.f, 0.f));
	if (ns::soundState == 2)
		sf::Listener::setPosition(view[1].getCenter().x, 0.f, 0.f);
	else
		sf::Listener::setPosition(view[0].getCenter().x, 0.f, 0.f);
	sf::Listener::setGlobalVolume(mainMenu.getEngineSettings().globalVolume);
	//End of update loop

	if (mainMenu.getEngineSettings().debug){
		//Pointer updates
		d_updateTime = updateClock.getElapsedTime().asMicroseconds();

		if (debugUpdateClock.getElapsedTime().asMilliseconds() >= 250){
			ns::debug->draw();
			debugUpdateClock.restart();
		}
	}
}

void Game::render()
{
	renderClock.restart();
	gameWindow.clear();

	//Rendering for top view
	gameWindow.setView(view[0]);

	worldManager.draw();
	gameWindow.draw(*player[0]);
	if (mainMenu.getEngineSettings().debug){
		for (unsigned int i = 0; i < player[0]->sensorShape.size(); i++){
			gameWindow.draw(player[0]->sensorShape[i]);
		}
	}

	worldManager.drawForeground();


	//Rendering for bottom view
	gameWindow.setView(view[1]);

	worldManager.draw();
	gameWindow.draw(*player[1]);
	if (mainMenu.getEngineSettings().debug){
		for (unsigned int i = 0; i < player[1]->sensorShape.size(); i++){
			gameWindow.draw(player[1]->sensorShape[i]);
		}
	}

	worldManager.drawForeground();


	//UI rendering
	gameWindow.setView(view[2]);

	gameWindow.draw(sShape);

	//End of render loop
	glFlush();
	gameWindow.display();

	if (mainMenu.getEngineSettings().debug){
		d_renderTime = renderClock.getElapsedTime().asMicroseconds();
	}
}

void Game::pollEvents()
{
	while (gameWindow.pollEvent(e)){
		if (e.type == sf::Event::KeyPressed){
			if (e.key.code == sf::Keyboard::Escape){
				runningState = false;
			}
			else if (e.key.code == sf::Keyboard::Up && ns::soundState < 2){
				ns::soundState++;
			}
			else if (e.key.code == sf::Keyboard::Down && ns::soundState > 0){
				ns::soundState--;
			}
		}
	}
}

void Game::init()
{
	cListener = new ContactListener;

	player[0] = new Player(1, mainMenu.getLoadSettings(), mainMenu.getEngineSettings());
	player[1] = new Player(2, mainMenu.getLoadSettings(), mainMenu.getEngineSettings());

	worldManager.loadWorld(cListener, mainMenu.getLoadSettings(), mainMenu.getEngineSettings());
	player[0]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener, mainMenu.getEngineSettings());
	player[1]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener, mainMenu.getEngineSettings());
	runningState = true;

	worldManager.getWorldPtr()->SetContactListener(cListener);

	if (mainMenu.getEngineSettings().debug){
		ns::debug->assignPtr(&d_updateTime, "Update time(us): ");
		ns::debug->assignPtr(&d_renderTime, "Render time(us): ");
	}

	EngineSettings engineSettings = mainMenu.getEngineSettings();
	float s_scale =  ((float)engineSettings.resolution.x / (float)engineSettings.resolution.y) / (1920.f / 1200.f);
	//Top view
	view[0].setCenter(sf::Vector2f((1920 * s_scale) / 2, 300));
	view[0].setSize(sf::Vector2f(1920 * s_scale, 600));
	view[0].setViewport(sf::FloatRect(0, 0, 1.f, 0.5f));

	//Bottom view
	view[1].setCenter(sf::Vector2f((1920 * s_scale) / 2, 900));
	view[1].setSize(sf::Vector2f(1920 * s_scale, 600));
	view[1].setViewport(sf::FloatRect(0, 0.5f, 1.f, 0.5f));

	//Whole view
	view[2].setCenter(sf::Vector2f(engineSettings.resolution.x / 2, engineSettings.resolution.y / 2));
	view[2].setSize(sf::Vector2f((float)engineSettings.resolution.x, (float)engineSettings.resolution.y));
	view[2].setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

	sShape.setFillColor(sf::Color::Black);
	sShape.setOutlineThickness(2);
	sShape.setOutlineColor(sf::Color::Yellow);
	sShape.setSize(sf::Vector2f((float)engineSettings.resolution.x, 11));
	sShape.setOrigin(0, 6);
	sShape.setPosition(0, engineSettings.resolution.y / 2);

	updateClock.restart();
	SetForegroundWindow(gameWindow.getSystemHandle());
}

void Game::deInit()
{
	player[0]->unloadPlayer();
	player[1]->unloadPlayer();
	worldManager.deleteWorld();
	delete player[0];
	delete player[1];
	delete cListener;
	runningState = false;

	if (mainMenu.getEngineSettings().debug){
		ns::debug->clear();
		ns::debug->draw();
	}
}