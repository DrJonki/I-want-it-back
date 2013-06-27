#include "Game.h"

namespace
{
	bool runningState = false;

	DebugConsole* debug;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock updateClock;

	sf::Time updateTime;

	sf::View view[3];
	
	sf::RectangleShape sShape;

	Mainmenu mainMenu(&gameWindow, &e);
	WorldManager worldManager(&gameWindow);
	Player* player[2];
	LoadSettings loadSettings;

	ContactListener* cListener;
	int _sensorDataP1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	int _sensorDataP2[8] = {8, 9, 10, 11, 12, 13, 14, 15};

}


Game::Game(void)
{}


Game::~Game(void)
{}


bool Game::runAndDontCrashPls()
{
	while (mainMenu.showMenu()){
		init();

		while (runningState){
			updateTime = updateClock.getElapsedTime();


			if (g_useVSync){
				if (updateTime.asSeconds() > g_updateTimerValue){
					update();
					render();
					pollEvents();
				}
			}
			else {
				if (updateTime.asSeconds() > g_updateTimerValue){
					update();
					pollEvents();
				}
				render();
			}
		}
		deInit();
	}

	return true;
}



void Game::update()
{
	updateClock.restart();

	//Update loop here
	//Player 1
	gameWindow.setView(view[0]);
	player[0]->update();
	if (player[0]->getPosition().y > 600 + player[0]->getLocalBounds().height || player[0]->getPosition().x + (player[0]->getLocalBounds().width / 2) < (view[0].getCenter().x - (view[0].getSize().x / 2)))
		runningState = false;

	//Player 2
	gameWindow.setView(view[1]);
	player[1]->update();
	if (player[1]->getPosition().y > 1200 + player[1]->getLocalBounds().height || player[1]->getPosition().x + (player[1]->getLocalBounds().width / 2) < (view[1].getCenter().x - (view[1].getSize().x / 2)))
		runningState = false;
	
	worldManager.stepWorldPhysics();

	
	view[0].move(5, 0);
	view[1].move(5, 0);

	if (player[0]->getPosition().x > view[0].getCenter().x) view[0].setCenter(sf::Vector2f(player[0]->getPosition().x, view[0].getCenter().y));
	if (player[1]->getPosition().x > view[1].getCenter().x) view[1].setCenter(sf::Vector2f(player[1]->getPosition().x, view[1].getCenter().y));
	//End of update loop

	if (g_debug){
		debug->draw();
	}
}

void Game::render()
{
	gameWindow.clear();

	//Rendering for top view
	gameWindow.setView(view[0]);

	worldManager.draw();
	gameWindow.draw(*player[0]);
	worldManager.drawForeground();


	//Rendering for bottomview
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

	player[0] = new Player(true);
	player[1] = new Player(false);

	worldManager.loadWorld(mainMenu.getSettings());
	player[0]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener, _sensorDataP1);
	player[1]->loadPlayer(&gameWindow, worldManager.getWorldPtr(), cListener, _sensorDataP2);
	runningState = true;

	worldManager.getWorldPtr()->SetContactListener(cListener);

	if (g_debug){
		debug = new DebugConsole;
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

	if (debug != 0){
		delete debug;
		debug = nullptr;
	}
}