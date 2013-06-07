#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Globals.h"
#include "Sprite.h"
#include "Player.h"

namespace
{
	bool exitState = false;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock updateClock;

	Player player;
}

void init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Steamworks", sf::Style::Close);
	gameWindow.setVerticalSyncEnabled(true);

	//player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
	player.setPosition(400, 300);
	
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

	//End of update loop
}

void render()
{
	gameWindow.clear();

	//Object rendering here
	gameWindow.draw(player);
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
		sf::Time updateTime = updateClock.getElapsedTime();

		if (updateTime.asMilliseconds() > g_updateTimerValue) update();
		render();
		pollEvents();

	}

	return 0;
}