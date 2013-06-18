#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <Box2D\Box2D.h>

#include <Windows.h>
#include <cstdlib>
#include <iostream>

#include "Globals.h"
#include "Sprite.h"
#include "Player.h"
#include "World.h"
#include "DebugConsole.h"

namespace
{
	bool exitState = false;

	DebugConsole* debug;

	sf::RenderWindow gameWindow;
	sf::Event e;
	sf::Clock updateClock;

	sf::Time updateTime;

	sf::View view[3];

	World world(&gameWindow);

	sf::RectangleShape sShape;
}

void init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Template title :(", sf::Style::Fullscreen);
	gameWindow.setVerticalSyncEnabled(g_useVSync);

	if (g_debug){
		debug = new DebugConsole;
	}

	//Top view
	view[0].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight * 0.25f));
	view[0].setSize(sf::Vector2f((float)g_windowWidth, (float)g_windowHeight / 2));
	view[0].setViewport(sf::FloatRect(0, 0, 1.f, 0.5f));
	//view[0].zoom(0.5f);

	//Bottom view
	view[1].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight * 0.75f));
	view[1].setSize(sf::Vector2f((float)g_windowWidth, (float)g_windowHeight / 2));
	view[1].setViewport(sf::FloatRect(0, 0.5f, 1.f, 0.5f));

	//Whole view
	view[2].setCenter(sf::Vector2f(g_windowWidth / 2, g_windowHeight / 2));
	view[2].setSize(sf::Vector2f((float)g_windowWidth, (float)g_windowHeight));
	view[2].setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

	sShape.setFillColor(sf::Color::Black);
	sShape.setOutlineThickness(2);
	sShape.setOutlineColor(sf::Color::Yellow);
	sShape.setSize(sf::Vector2f(g_windowWidth, 11));
	sShape.setOrigin(0, 6);
	sShape.setPosition(0, g_windowHeight / 2);

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

void render()
{
	gameWindow.clear();

	//Rendering for top view
	gameWindow.setView(view[0]);

	world.draw();


	//Rendering for bottomview
	gameWindow.setView(view[1]);

	world.draw();


	//UI rendering
	gameWindow.setView(view[2]);

	gameWindow.draw(sShape);

	//End of render loop
	glFlush();
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