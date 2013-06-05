#include "GameButton.h"


GameButton::GameButton(void)
{
	_assignedButton = nullptr;

	_buttonTexture[0] = nullptr;
	_buttonTexture[1] = nullptr;
	_buttonTexture[2] = nullptr;

	_buttonText.setString("Template text :(");
	_buttonText.setPosition(0.f, 0.f);

	_activateable = true;
}


GameButton::~GameButton(void){}
