#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Globals.h"
#include "Sprite.h"
#include "Player.h"
#include "World.h"

namespace
{
	bool exitState = false;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock updateClock;
	sf::Time updateTime;

	World world;
	Player player(world.getWorldPtr());
}

void init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Steamworks", sf::Style::Close);
	gameWindow.setVerticalSyncEnabled(0);
	
	updateClock.restart();
}

void deInit()
{
	gameWindow.close();
}

void update()
{
	updateClock.restart();

	//Update loop here
	player.update();

	world.physStep();
	//End of update loop
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
		if (e.type == sf::Event::Closed){
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