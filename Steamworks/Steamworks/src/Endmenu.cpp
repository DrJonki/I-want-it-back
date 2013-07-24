#include "Endmenu.h"

#include <sstream>

#include "Globals.h"
#include "Misc.h"


Endmenu::Endmenu(sf::RenderWindow* window, sf::Event* e, LoadSettings* lsettings)
	: _window(window),
	  _e(e),
	  _lSettings(lsettings)
{
	_backgroundShape.setSize(sf::Vector2f(1920, 1200));
	_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));

	_font.loadFromFile("Resources/Common/Fonts/galvanize.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(60);
	_text.setPosition(300, 300);
	_text.setString("Level completed!\n\n\nEnter - Next level (if one exists)\nR - Restart current level\nEscape - Exit to menu");

	_timeText.setFont(_font);
	_timeText.setCharacterSize(60);
	_timeText.setPosition(1000, 300);
}

Endmenu::~Endmenu(void)
{}


void Endmenu::showMenu(float time)
{
	if (ns::endOfLevelState){
		if (_backgroundShape.getFillColor().a < 200){
			_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, _backgroundShape.getFillColor().a + 5));
		}

		std::stringstream ss;
		ss << "Time: ";
		ss << time;
		ss << " s";
		_timeText.setString(ss.str());

		while (_window->pollEvent(*_e)){
			if (_e->type == sf::Event::KeyPressed){
				if (_e->key.code == sf::Keyboard::R){
					_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));
					ns::spawnPoint = 1000.f;
					ns::runningState = false;
					ns::endOfLevelState = false;
					ns::deathState = false;
					ns::restartState = true;
				}
				else if (_e->key.code == sf::Keyboard::Return){
					_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));
					ns::spawnPoint = 1000.f;
					if (_lSettings->_level < _lSettings->_levelVector.size() - 1){
						_lSettings->_level++;
						ns::runningState = false;
						ns::endOfLevelState = false;
						ns::deathState = false;
						ns::restartState = true;
					}
					else{
						ns::runningState = false;
					}
				}
				else if (_e->key.code == sf::Keyboard::Escape){
					_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));
					ns::spawnPoint = 1000.f;
					ns::runningState = false;
					ns::endOfLevelState = false;
				}
			}
		}
	}
	else{
		if (_backgroundShape.getFillColor().a >= 5){
			_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, _backgroundShape.getFillColor().a - 5));
		}
	}
}

void Endmenu::draw()
{
	if (_backgroundShape.getFillColor().a < 127){
		_text.setColor(sf::Color::Color(255, 255, 255, _backgroundShape.getFillColor().a * 2));
		_timeText.setColor(sf::Color::Color(255, 255, 255, _backgroundShape.getFillColor().a * 2));
	}
	else{
		_text.setColor(sf::Color::Color(255, 255, 255, 255));
		_timeText.setColor(sf::Color::Color(255, 255, 255, 255));
	}

	if (_backgroundShape.getFillColor().a >= 5){
		sf::View view;
		view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
		view.setSize(sf::Vector2f(1920, 1200));
		_window->setView(view);

		_window->draw(_backgroundShape);
		_window->draw(_text);
		_window->draw(_timeText);
	}
}