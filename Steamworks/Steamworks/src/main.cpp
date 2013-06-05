#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Globals.h"

namespace
{
	bool exitState = false;

	sf::RenderWindow gameWindow;
	sf::Event e;

	sf::Clock updateClock;

	sf::RectangleShape shape;
}

void init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Steamworks", sf::Style::Close);
	gameWindow.setVerticalSyncEnabled(true);

	shape.setSize(sf::Vector2f(250.f, 250.f));
	shape.setOrigin(125.f, 125.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition((float)g_windowWidth / 2, (float)g_windowHeight / 2);
	shape.setOutlineThickness(3.f);
	shape.setOutlineColor(sf::Color::Blue);
	
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
	shape.rotate(0.5);
	//End of update loop
}

void render()
{
	gameWindow.clear();

	//Object rendering here
	gameWindow.draw(shape);


	//End of render loop

	gameWindow.display();
}

void pollEvents()
{
	while (gameWindow.pollEvent(e)){
		if (e.type == sf::Event::KeyPressed){
			exitState = true;
		}
	}
}

int main()
{
	init();

	while (!exitState){
		sf::Time updateTime = updateClock.getElapsedTime();

		if (updateTime.asMilliseconds() > 15) update();
		render();
		pollEvents();

	}

	return 0;
}