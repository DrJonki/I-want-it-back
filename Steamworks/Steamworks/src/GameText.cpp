#include "GameText.h"


GameText::GameText(void)
{
	_font.loadFromFile("Resources/Common/Fonts/Amble-Bold.ttf");

	setFont(_font);
}
GameText::~GameText(void){}