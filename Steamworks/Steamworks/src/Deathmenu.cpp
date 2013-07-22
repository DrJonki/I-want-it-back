#include "Deathmenu.h"

#include "Globals.h"


Deathmenu::Deathmenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e)
{
	_backgroundShape.setSize(sf::Vector2f(1920, 1200));
	_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, 0));

	_font.loadFromFile("Resources/Common/Fonts/Amble-Bold.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(60);
	_text.setPosition(300, 300);
	_text.setString("Enter - Restart\nEscape - Exit to menu");
}

Deathmenu::~Deathmenu(void)
{}


void Deathmenu::showMenu()
{
	if (ns::deathState){
		if (_backgroundShape.getFillColor().a < 100){
			_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, _backgroundShape.getFillColor().a + 5));
		}
		while (_window->pollEvent(*_e)){
			if (_e->type == sf::Event::KeyPressed){
				if (_e->key.code == sf::Keyboard::Return){
					_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, 0));
					ns::runningState = false;
				}
				else if (_e->key.code == sf::Keyboard::Escape){
					_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, 0));
					ns::spawnPoint = 1000.f;
					ns::runningState = false;
					ns::deathState = false;
				}
			}
		}
	}
	else{
		if (_backgroundShape.getFillColor().a >= 5){
			_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, _backgroundShape.getFillColor().a - 5));
		}
	}
}

void Deathmenu::draw()
{
	if (_backgroundShape.getFillColor().a < 127) _text.setColor(sf::Color::Color(255, 255, 255, _backgroundShape.getFillColor().a * 2));
	else _text.setColor(sf::Color::Color(255, 255, 255, 255));

	if (_backgroundShape.getFillColor().a >= 5){
		sf::View view;
		view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
		view.setSize(sf::Vector2f(1920, 1200));
		_window->setView(view);

		_window->draw(_backgroundShape);
		_window->draw(_text);
	}
}