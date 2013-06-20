#include "Game.h"

namespace
{
	bool exitState = false, runningState = true;

	DebugConsole* debug;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock updateClock;

	sf::Time updateTime;

	sf::View view[3];
	
	sf::RectangleShape sShape;

	Mainmenu mainMenu(&gameWindow);
	WorldManager worldManager(&gameWindow);
	LoadSettings loadSettings;
	Player player;
}


Game::Game(void)
{}


Game::~Game(void)
{}


bool Game::runAndDontCrashPls()
{
	if (mainMenu.showMenu()){
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
	player.update();
	worldManager.stepWorldPhysics();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		view[0].move(5, 0);
		view[1].move(5, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		view[0].move(-5, 0);
		view[1].move(-5, 0);
	}
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
	gameWindow.draw(player);


	//Rendering for bottomview
	gameWindow.setView(view[1]);

	worldManager.draw();


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
		if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			runningState = false;
		}
	}
}

void Game::init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Template title :(", sf::Style::Close);
	gameWindow.setVerticalSyncEnabled(g_useVSync);

	loadSettings = mainMenu.getSettings();
	worldManager.loadWorld(loadSettings);
	player.loadPlayer(worldManager.getWorldPtr());

	if (g_debug){
		debug = new DebugConsole;
	}

	//Top view
	/*view[0].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight * 0.25f));
	view[0].setSize(sf::Vector2f((float)g_windowWidth, (float)g_windowHeight / 2));
	view[0].setViewport(sf::FloatRect(0, 0, 1.f, 0.5f));*/
	view[0].setCenter(sf::Vector2f(g_windowWidth / 2, 300));
	view[0].setSize(sf::Vector2f((float)g_windowWidth, 600));
	view[0].setViewport(sf::FloatRect(0, 0, 1.f, 0.5f));

	//Bottom view
	/*view[1].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight * 0.75f));
	view[1].setSize(sf::Vector2f((float)g_windowWidth, (float)g_windowHeight / 2));
	view[1].setViewport(sf::FloatRect(0, 0.5f, 1.f, 0.5f));*/
	view[1].setCenter(sf::Vector2f(g_windowWidth / 2, 900));
	view[1].setSize(sf::Vector2f((float)g_windowWidth, 600));
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
	player.unloadPlayer();
	//worldManager.deleteWorld();

	gameWindow.close();

	if (debug != 0) delete debug;
}