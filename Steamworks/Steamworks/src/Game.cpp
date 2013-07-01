#include "Game.h"

namespace
{
	bool runningState = false;

	DebugConsole* debug;

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
	LoadSettings loadSettings;

	ContactListener* cListener;
}

Game::Game(void)
{}
Game::~Game(void)
{}


bool Game::runAndDontCrashPls()
{
	if (g_debug){
		debug = new DebugConsole;
		debug->draw();
	}
	
	while (mainMenu.showMenu()){
		init();

		while (runningState){
			if (g_useVSync){
				if (updateClock.getElapsedTime().asSeconds() > g_updateTimerValue){
					update();
					render();
					pollEvents();
				}
			}
			else {
				if (updateClock.getElapsedTime().asSeconds() > g_updateTimerValue){
					update();
					pollEvents();
				}
				render();
			}
		}
		deInit();
	}

	if (debug != 0) delete debug;
	
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

	
	view[0].move(5, 0);
	view[1].move(5, 0);

	if (player[0]->getPosition().x > view[0].getCenter().x) view[0].setCenter(sf::Vector2f(player[0]->getPosition().x, view[0].getCenter().y));
	if (player[1]->getPosition().x > view[1].getCenter().x) view[1].setCenter(sf::Vector2f(player[1]->getPosition().x, view[1].getCenter().y));
	//End of update loop

	if (g_debug){
		//Pointer updates
		d_updateTime = updateClock.getElapsedTime().asMilliseconds();

		if (debugUpdateClock.getElapsedTime().asMilliseconds() >= 250){
			debug->draw();
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
	worldManager.drawForeground();


	//Rendering for bottom view
	gameWindow.setView(view[1]);

	worldManager.draw();
	gameWindow.draw(*player[1]);
	worldManager.drawForeground();


	//UI rendering
	gameWindow.setView(view[2]);

	gameWindow.draw(sShape);

	//End of render loop
	glFlush();
	gameWindow.display();

	if (g_debug){
		d_renderTime = renderClock.getElapsedTime().asMilliseconds();
	}
}

void Game::pollEvents()
{
	while (gameWindow.pollEvent(e)){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			runningState = false;
		}
	}
}

void Game::init()
{
	cListener = new ContactListener;

	player[0] = new Player(1);
	player[1] = new Player(2);

	worldManager.loadWorld(mainMenu.getSettings());
	player[0]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener);
	player[1]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener);
	runningState = true;

	worldManager.getWorldPtr()->SetContactListener(cListener);

	if (g_debug){
		debug->assignPtr(&d_updateTime, "Update time(ms): ");
		debug->assignPtr(&d_renderTime, "Render time(ms): ");
	}


	float s_scale =  ((float)g_windowWidth / (float)g_windowHeight) / (1920.f / 1200.f);
	//Top view
	view[0].setCenter(sf::Vector2f((1920 * s_scale) / 2, 300));
	view[0].setSize(sf::Vector2f(1920 * s_scale, 600));
	view[0].setViewport(sf::FloatRect(0, 0, 1.f, 0.5f));

	//Bottom view
	view[1].setCenter(sf::Vector2f((1920 * s_scale) / 2, 900));
	view[1].setSize(sf::Vector2f(1920 * s_scale, 600));
	view[1].setViewport(sf::FloatRect(0, 0.5f, 1.f, 0.5f));

	//Whole view
	view[2].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight / 2));
	view[2].setSize(sf::Vector2f((float)g_windowWidth, (float)g_windowHeight));
	view[2].setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

	sShape.setFillColor(sf::Color::Black);
	sShape.setOutlineThickness(2);
	sShape.setOutlineColor(sf::Color::Yellow);
	sShape.setSize(sf::Vector2f((float)g_windowWidth, 11));
	sShape.setOrigin(0, 6);
	sShape.setPosition(0, g_windowHeight / 2);

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

	if (g_debug){
		debug->clear();
		debug->draw();
	}
}