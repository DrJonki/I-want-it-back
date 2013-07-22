#include "Gui.h"

#include "Globals.h"


namespace
{
	const float minAlpha = 80.f;
}

Gui::Gui(sf::RenderWindow* window)
	: _window(window)
{
	_soundShapeTexture.loadFromFile("Resources/Common/Graphics/UI/speaker.png");

	_soundShape[0].setTexture(&_soundShapeTexture);
	_soundShape[1].setTexture(&_soundShapeTexture);
	_soundShape[0].setFillColor(sf::Color::Color(_soundShape[0].getFillColor().r, _soundShape[0].getFillColor().g, _soundShape[0].getFillColor().b, minAlpha));
	_soundShape[1].setFillColor(sf::Color::Color(_soundShape[1].getFillColor().r, _soundShape[1].getFillColor().g, _soundShape[1].getFillColor().b, minAlpha));

	_soundShape[0].setSize(sf::Vector2f(150, 150));
	_soundShape[0].setOrigin(_soundShape[0].getSize().x / 2, _soundShape[0].getSize().y / 2);
	_soundShape[1].setSize(sf::Vector2f(150, 150));
	_soundShape[1].setOrigin(_soundShape[1].getSize().x / 2, _soundShape[1].getSize().y / 2);
}


Gui::~Gui(void)
{}


void Gui::update()
{
	if (ns::soundState == 0){
		if (_soundShape[0].getFillColor().a < 220)
			_soundShape[0].setFillColor(sf::Color::Color(_soundShape[0].getFillColor().r, _soundShape[0].getFillColor().g, _soundShape[0].getFillColor().b, _soundShape[0].getFillColor().a + 5));
		if (_soundShape[1].getFillColor().a < 220)
			_soundShape[1].setFillColor(sf::Color::Color(_soundShape[1].getFillColor().r, _soundShape[1].getFillColor().g, _soundShape[1].getFillColor().b, _soundShape[1].getFillColor().a + 5));
	}
	else if (ns::soundState == 1){
		if (_soundShape[0].getFillColor().a < 220)
			_soundShape[0].setFillColor(sf::Color::Color(_soundShape[0].getFillColor().r, _soundShape[0].getFillColor().g, _soundShape[0].getFillColor().b, _soundShape[0].getFillColor().a + 5));
		if (_soundShape[1].getFillColor().a > 80)
			_soundShape[1].setFillColor(sf::Color::Color(_soundShape[1].getFillColor().r, _soundShape[1].getFillColor().g, _soundShape[1].getFillColor().b, _soundShape[1].getFillColor().a - 5));
	}
	else if (ns::soundState == 2){
		if (_soundShape[0].getFillColor().a > 80)
			_soundShape[0].setFillColor(sf::Color::Color(_soundShape[0].getFillColor().r, _soundShape[0].getFillColor().g, _soundShape[0].getFillColor().b, _soundShape[0].getFillColor().a - 5));
		if (_soundShape[1].getFillColor().a < 220)
			_soundShape[1].setFillColor(sf::Color::Color(_soundShape[1].getFillColor().r, _soundShape[1].getFillColor().g, _soundShape[1].getFillColor().b, _soundShape[1].getFillColor().a + 5));
	}
}

void Gui::draw()
{
	_soundShape[0].setPosition(90, _window->getView().getCenter().y - 95);
	_soundShape[1].setPosition(90, _window->getView().getCenter().y + 95);
	_window->draw(_soundShape[0]);
	_window->draw(_soundShape[1]);
}