#include "GameButton.h"


GameButton::GameButton(void)
{
	_buttonText.setString("Template text :(");
	_buttonText.setPosition(0.f, 0.f);

	_activateable = true;
}


GameButton::~GameButton(void){}
