#include "Game.h"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\System\Clock.hpp>

#include <iostream>

#include "Mainmenu.h"
#include "Pausemenu.h"
#include "Deathmenu.h"
#include "Endmenu.h"
#include "WorldManager.h"
#include "Player.h"
#include "Gui.h"


void loadingScreen();

namespace
{
	bool paused = false;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock debugUpdateClock;
	sf::Clock updateClock;
	sf::Clock renderClock;

	//Debug numbers
	int d_updateTime = 0;
	int d_renderTime = 0;

	//View centers
	float viewCenterTop = 0.f;
	float viewCenterBottom = 0.f;
	
	sf::RectangleShape sShape;

	Mainmenu mainMenu(&gameWindow, &e);
	WorldManager worldManager(&gameWindow);
	Player* player[2];

	unsigned int soundSelection = 1;

	ContactListener* cListener;

	Pausemenu* pauseMenu;

	Gui* gui;

	Deathmenu deathMenu(&gameWindow, &e);
	Endmenu endMenu(&gameWindow, &e, &mainMenu.getLoadSettings());
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
	else{
		HWND hwnd = GetConsoleWindow();
		ShowWindow(hwnd, SW_HIDE);
	}
	
	while (ns::restartState || (mainMenu.showMenu() && !ns::exitState)){
		if (!ns::restartState)
			init();
		else
			resetStates();

		while (ns::runningState){
			if (mainMenu.getEngineSettings().vSync){
				if (updateClock.getElapsedTime().asSeconds() > ns::g_updateTimerValue){
					if (!paused && !ns::deathState){
						update();
						pollEvents();
					}
					render();
					if (paused){
						player[0]->resetClocks();
						player[1]->resetClocks();
					}
					if (pauseMenu->showMenu(paused))
						paused = false;
					deathMenu.showMenu();
					endMenu.showMenu();
				}
			}
			else {
				if (updateClock.getElapsedTime().asSeconds() > ns::g_updateTimerValue && !paused && !ns::deathState){
					update();
					pollEvents();
				}
				render();
				if (paused){
					player[0]->resetClocks();
					player[1]->resetClocks();
				}
				if (pauseMenu->showMenu(paused))
					paused = false;
				deathMenu.showMenu();
				endMenu.showMenu();
			}
		}
		if (!ns::restartState)
			deInit();
	}

	if (ns::debug != nullptr) delete ns::debug;
	
	return true;
}



void Game::update()
{
	updateClock.restart();

	pauseMenu->getView(VIEW_TOP).setCenter(sf::Vector2f(viewCenterTop, 300));
	pauseMenu->getView(VIEW_BOTTOM).setCenter(sf::Vector2f(viewCenterBottom, 900));

	//Update loop here
	//Player 1
	gameWindow.setView(pauseMenu->getView(VIEW_TOP));
	player[0]->update();

	//Player 2
	gameWindow.setView(pauseMenu->getView(VIEW_BOTTOM));
	player[1]->update();

	//Border checks
	if ((player[1]->getPosition().y > 1200 + player[1]->getLocalBounds().height || player[1]->getPosition().x + (player[1]->getLocalBounds().width / 2) < (pauseMenu->getView(VIEW_BOTTOM).getCenter().x - (pauseMenu->getView(VIEW_BOTTOM).getSize().x / 2))) ||
		(player[0]->getPosition().y > 600 + player[0]->getLocalBounds().height || player[0]->getPosition().x + (player[0]->getLocalBounds().width / 2) < (pauseMenu->getView(VIEW_TOP).getCenter().x - (pauseMenu->getView(VIEW_TOP).getSize().x / 2))))
		ns::deathState = true;
	
	worldManager.stepWorldPhysics();
	
	if (!ns::endOfLevelState){
		pauseMenu->getView(VIEW_TOP).move(ns::cameraSpeed, 0);
		pauseMenu->getView(VIEW_BOTTOM).move(ns::cameraSpeed, 0);

		if (player[0]->getPosition().x > pauseMenu->getView(VIEW_TOP).getCenter().x) pauseMenu->getView(VIEW_TOP).setCenter(sf::Vector2f(player[0]->getPosition().x, pauseMenu->getView(VIEW_TOP).getCenter().y));
		if (player[1]->getPosition().x > pauseMenu->getView(VIEW_BOTTOM).getCenter().x) pauseMenu->getView(VIEW_BOTTOM).setCenter(sf::Vector2f(player[1]->getPosition().x, pauseMenu->getView(VIEW_BOTTOM).getCenter().y));
	}

	viewCenterTop = pauseMenu->getView(VIEW_TOP).getCenter().x;
	viewCenterBottom = pauseMenu->getView(VIEW_BOTTOM).getCenter().x;

	sf::Listener::setDirection(sf::Vector3f(1.f, 0.f, 0.f));
	if (ns::soundState == 2)
		sf::Listener::setPosition(pauseMenu->getView(VIEW_BOTTOM).getCenter().x, 0.f, 0.f);
	else
		sf::Listener::setPosition(pauseMenu->getView(VIEW_TOP).getCenter().x, 0.f, 0.f);
	sf::Listener::setGlobalVolume((float)mainMenu.getEngineSettings().globalVolume);

	gui->update();
	//End of update loop

	if (mainMenu.getEngineSettings().debug){
		//Pointer updates
		d_updateTime = (int)updateClock.getElapsedTime().asMicroseconds();

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

	if (paused){
		pauseMenu->getView(VIEW_TOP).setCenter(sf::Vector2f(viewCenterTop, 300));
		pauseMenu->getView(VIEW_BOTTOM).setCenter(sf::Vector2f(viewCenterBottom, 900));
	}

	//Rendering for top view
	gameWindow.setView(pauseMenu->getView(VIEW_TOP));

	worldManager.draw();
	gameWindow.draw(*player[0]);
	if (mainMenu.getEngineSettings().debug){
		for (unsigned int i = 0; i < player[0]->sensorShape.size(); i++){
			gameWindow.draw(player[0]->sensorShape[i]);
		}
	}

	worldManager.drawForeground();


	//Rendering for bottom view
	gameWindow.setView(pauseMenu->getView(VIEW_BOTTOM));

	worldManager.draw();
	gameWindow.draw(*player[1]);
	if (mainMenu.getEngineSettings().debug){
		for (unsigned int i = 0; i < player[1]->sensorShape.size(); i++){
			gameWindow.draw(player[1]->sensorShape[i]);
		}
	}

	worldManager.drawForeground();


	//UI rendering
	gameWindow.setView(pauseMenu->getView(VIEW_WHOLE));
	
	sShape.setSize(sf::Vector2f(pauseMenu->getView(VIEW_WHOLE).getSize().x, 11));
	sShape.setOrigin(0, 6);
	sShape.setPosition(0, pauseMenu->getView(VIEW_WHOLE).getCenter().y);
	gameWindow.draw(sShape);

	gui->draw();
	pauseMenu->draw();
	deathMenu.draw();
	endMenu.draw();

	//End of render loop
	glFlush();
	gameWindow.display();

	if (mainMenu.getEngineSettings().debug){
		d_renderTime = (int)renderClock.getElapsedTime().asMicroseconds();
	}
}

void Game::pollEvents()
{
	if (!ns::endOfLevelState){
		while (gameWindow.pollEvent(e)){
			if (e.type == sf::Event::KeyPressed){
				if (e.key.code == sf::Keyboard::Escape){
					if (!paused) paused = true;
				}
				else if (e.key.code == sf::Keyboard::Up){
					ns::soundState++;
					if (ns::soundState > 2)
						ns::soundState = 0;
				}
				else if (e.key.code == sf::Keyboard::Down){
					ns::soundState--;
					if (ns::soundState < 0)
						ns::soundState = 2;
				}
			}
			if (e.type == sf::Event::LostFocus){
				paused = true;
			}
		}
	}
}

void Game::init()
{
	paused = false;
	ns::deathState = false;
	ns::restartState = false;
	
	pauseMenu = new Pausemenu(&gameWindow, &e, mainMenu.getEngineSettings());
	
	gameWindow.setActive(false);

	viewCenterTop = pauseMenu->getView(VIEW_TOP).getCenter().x;
	viewCenterBottom = pauseMenu->getView(VIEW_BOTTOM).getCenter().x;

	sf::Thread loadingScreenThread(&loadingScreen);
	loadingScreenThread.launch();

	gui = new Gui(&gameWindow);
	cListener = new ContactListener;

	sf::Clock loadClock;
	loadClock.restart();

	std::cout << "Constructing players..." << std::endl;
	player[0] = new Player(1, mainMenu.getLoadSettings(), mainMenu.getEngineSettings());
	player[1] = new Player(2, mainMenu.getLoadSettings(), mainMenu.getEngineSettings());
	std::cout << "constructing players complete! Time: " << loadClock.getElapsedTime().asSeconds() << std::endl;
	loadClock.restart();

	std::cout << "Loading world..." << std::endl;
	worldManager.loadWorld(cListener, mainMenu.getLoadSettings(), mainMenu.getEngineSettings());
	std::cout << "Loading world complete! Time: " << loadClock.getElapsedTime().asSeconds() << std::endl;
	loadClock.restart();

	std::cout << "Loading player data..." << std::endl;
	player[0]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener);
	player[1]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener);
	std::cout << "Loading player data complete! Time: " << loadClock.getElapsedTime().asSeconds() << std::endl;

	worldManager.getWorldPtr()->SetContactListener(cListener);

	if (mainMenu.getEngineSettings().debug){
		ns::debug->assignPtr(&d_updateTime, "Update time(us): ");
		ns::debug->assignPtr(&d_renderTime, "Render time(us): ");
	}

	sShape.setFillColor(sf::Color::Black);
	sShape.setOutlineThickness(2);
	sShape.setOutlineColor(sf::Color::Yellow);
	sShape.setSize(sf::Vector2f((float)mainMenu.getEngineSettings().resolution.x, 11));
	sShape.setOrigin(0, 6);
	sShape.setPosition(0.f, (float)(mainMenu.getEngineSettings().resolution.y / 2));

	updateClock.restart();
	SetForegroundWindow(gameWindow.getSystemHandle());

	ns::runningState = true;
	loadingScreenThread.wait();
	gameWindow.setActive(true);

	std::cout << "Done loading!" << std::endl;
}

void Game::deInit()
{
	player[0]->unloadPlayer();
	player[1]->unloadPlayer();
	worldManager.deleteWorld();
	delete player[0];
	delete player[1];
	delete cListener;
	delete pauseMenu;
	ns::runningState = false;

	if (mainMenu.getEngineSettings().debug){
		ns::debug->clear();
		ns::debug->draw();
	}
}

void loadingScreen()
{
	gameWindow.setActive(true);

	sf::Font font;
	font.loadFromFile("Resources/Common/Fonts/Amble-Bold.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(100);
	text.setPosition(300, 300);
	text.setString("Loading...");

	sf::View view;
	view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
	view.setSize(sf::Vector2f(1920, 1200));
	gameWindow.setView(view);

	while (!ns::runningState){
		gameWindow.clear(sf::Color::Black);
		gameWindow.draw(text);
		gameWindow.display();
	}

	gameWindow.setActive(false);
}

void Game::resetStates()
{
	viewCenterTop = pauseMenu->getView(VIEW_TOP).getCenter().x;
	viewCenterBottom = pauseMenu->getView(VIEW_BOTTOM).getCenter().x;

	SetForegroundWindow(gameWindow.getSystemHandle());

	paused = false;
	ns::deathState = false;
	ns::restartState = false;
	ns::runningState = true;

	worldManager.resetWorldStates();
	player[0]->resetState();
	player[1]->resetClocks();

	pauseMenu->getView(VIEW_TOP).setCenter(ns::spawnPoint, 300);
	pauseMenu->getView(VIEW_BOTTOM).setCenter(ns::spawnPoint, 900);
}