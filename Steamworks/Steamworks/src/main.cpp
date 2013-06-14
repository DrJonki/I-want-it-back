#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

#include <Windows.h>
#include <cstdlib>
#include <iostream>

#include "Globals.h"
#include "Sprite.h"
#include "Player.h"
#include "World.h"
#include "DebugConsole.h"
#include "Particle.h"

namespace
{
	bool exitState = false;

	DebugConsole* debug;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock updateClock;
	sf::Clock uptimeClock;

	sf::Time updateTime;
	sf::Time monUpdateTime;

	sf::View view[3];

	int upTime = 0;

	World world;

	sf::RectangleShape shaper;
}

void init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Steamworks", sf::Style::Close);
	gameWindow.setVerticalSyncEnabled(g_useVSync);

	if (g_debug){
		debug = new DebugConsole;
		debug->assignPtr(&monUpdateTime, "Update time (ms): ");
		debug->assignPtr(&upTime, "Uptime (s): ");
	}

	//Top view
	view[0].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight * 0.25f));
	view[0].setSize(sf::Vector2f(g_windowWidth, g_windowHeight / 2));
	view[0].setViewport(sf::FloatRect(0, 0, 1.f, 0.5f));

	//Bottom view
	view[1].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight * 0.75f));
	view[1].setSize(sf::Vector2f(g_windowWidth, g_windowHeight / 2));
	view[1].setViewport(sf::FloatRect(0, 0.5f, 1.f, 0.5f));

	//Whole view
	view[2].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight / 2));
	view[2].setSize(sf::Vector2f(g_windowWidth, g_windowHeight));
	view[2].setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

	shaper.setSize(sf::Vector2f(g_windowWidth - 100, 20));
	shaper.setOutlineThickness(2);
	shaper.setOutlineColor(sf::Color::Green);
	shaper.setPosition(50, g_windowHeight / 2 - 10);

	updateClock.restart();
}

void deInit()
{
	gameWindow.close();

	if (debug != 0) delete debug;
}

void update()
{
	updateClock.restart();

	//Update loop here
	world.physStep();
	//End of update loop

	if (g_debug){
		monUpdateTime = updateClock.getElapsedTime();
		sf::Time sfUpTime = uptimeClock.getElapsedTime();
		upTime = (int)sfUpTime.asSeconds();

		debug->draw();
	}
}

void render()
{
	gameWindow.clear();

	//Rendering for top view
	gameWindow.setView(view[0]);

	world.draw(gameWindow);


	//Rendering for bottomview
	gameWindow.setView(view[1]);

	world.draw(gameWindow);




	//UI rendering
	gameWindow.setView(view[2]);

	gameWindow.draw(shaper);

	//End of render loop

	gameWindow.display();
}

void pollEvents()
{
	while (gameWindow.pollEvent(e)){
		if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			exitState = true;
		}
	}
}

int main()
{
	init();

	while (!exitState){
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

	return 0;
}