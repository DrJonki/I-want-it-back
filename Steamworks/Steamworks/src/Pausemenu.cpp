#include "Pausemenu.h"


Pausemenu::Pausemenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e)
{}


Pausemenu::~Pausemenu(void)
{}


bool Pausemenu::update()
{
	while (_window->pollEvent(*_e)){
		if (_e->type == sf::Event::KeyPressed){
			if (_e->key.code == sf::Keyboard::Return)
				return true;
			else if (_e->key.code == sf::Keyboard::Escape)
				ns::runningState = false;
		}
	}

	return false;
}