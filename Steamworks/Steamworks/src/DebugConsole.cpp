#include "DebugConsole.h"


DebugConsole::DebugConsole(void)
{
	textProps.x = 5;
	textProps.y = 5;
	textProps.charSize = 14;

	defaultFont.loadFromFile(RES_FONTS "furore.otf");

	debugWindow.create(sf::VideoMode(400, 200), "Debug", sf::Style::None);
	debugWindow.setPosition(sf::Vector2i(-500, 400));
}


DebugConsole::~DebugConsole(void){}

void DebugConsole::draw()
{
	debugWindow.clear(sf::Color::Color(24, 93, 145, 255));

	for (unsigned int i = 0; i < dObject.size(); i++){
		dObject[i].update();

		debugWindow.draw(dObject[i]);
	}

	debugWindow.display();

	while (debugWindow.pollEvent(e));
}

void DebugConsole::clear()
{
	dObject.clear();

	textProps.x = 5;
	textProps.y = 5;
}