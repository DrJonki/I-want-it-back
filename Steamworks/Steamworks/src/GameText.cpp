#include "GameText.h"


GameText::GameText(void)
{
	sf::Font font;
	font.loadFromFile("Resources/Fonts/FancyPants.ttf");

	setFont(font);
}
GameText::~GameText(void){}
