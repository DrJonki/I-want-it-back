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

	int upTime = 0;
	float testFloat = 0.f;

	World world;
	Player player(world.getWorldPtr());
}

void init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Steamworks", sf::Style::Close);
	gameWindow.setVerticalSyncEnabled(g_useVSync);

	if (g_debug){
		debug = new DebugConsole;
		debug->assignPtr(&monUpdateTime, "Update time (ms): ");
		debug->assignPtr(&upTime, "Uptime (s): ");
		debug->assignPtr(&testFloat, "Test float: ");
	}
	
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
	player.update();
	world.physStep();
	//End of update loop

	if (g_debug){
		monUpdateTime = updateClock.getElapsedTime();
		sf::Time sfUpTime = uptimeClock.getElapsedTime();
		upTime = (int)sfUpTime.asSeconds();

		debug->draw();
	}

	testFloat += 0.025f;
}

void render()
{
	gameWindow.clear();

	//Object rendering here
	gameWindow.draw(player);
	world.draw(gameWindow);
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