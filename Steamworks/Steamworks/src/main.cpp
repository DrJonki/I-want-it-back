#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

using namespace sf;
namespace
{
	bool exitState = false;

	RenderWindow gameWindow;
	Event e;

	Clock updateClock;
}

void init()
{
	gameWindow.create(VideoMode(600, 600), "Steamworks", Style::Close);
	gameWindow.setVerticalSyncEnabled(true);
	
	updateClock.restart();
}

void deInit()
{
	gameWindow.close();
}

void update()
{
	updateClock.restart();
}

void render()
{
	gameWindow.clear();

	gameWindow.display();
}

void pollEvents()
{
	while (gameWindow.pollEvent(e)){
		if (e.type == Event::KeyPressed){
			exitState = true;
		}
	}
}

int main()
{
	init();

	while (!exitState){
		Time updateTime = updateClock.getElapsedTime();

		if (updateTime.asMilliseconds() > 15) update();
		render();
		pollEvents();

	}

	return 0;
}