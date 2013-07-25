#include "Endmenu.h"

#include <sstream>

#include "Globals.h"
#include "Misc.h"


namespace
{
	int selectionState = 0;

	bool lockMouse = true;
}


Endmenu::Endmenu(sf::RenderWindow* window, sf::Event* e, LoadSettings* lsettings)
	: _window(window),
	  _e(e),
	  _lSettings(lsettings)
{
	init();
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
		ss.precision(1);
		ss << "Time: ";
		ss << std::fixed << time;
		ss << "s" << std::endl;
		ss << "Best: ";

		bool newRecord = false;
		if (time < ns::gameStateLoader->getLevelTime(_lSettings->_campaignVector[_lSettings->_campaign], _lSettings->_levelVector[_lSettings->_level]) ||
			ns::gameStateLoader->getLevelTime(_lSettings->_campaignVector[_lSettings->_campaign], _lSettings->_levelVector[_lSettings->_level]) == 0.f)
		{
			ns::gameStateLoader->saveLevelData(_lSettings->_campaignVector[_lSettings->_campaign], _lSettings->_levelVector[_lSettings->_level], true, time);
			newRecord = true;
		}

		ss << ns::gameStateLoader->getLevelTime(_lSettings->_campaignVector[_lSettings->_campaign], _lSettings->_levelVector[_lSettings->_level]) << "s";
		if (newRecord)
			ss << "New Record!";

		_timeText.setString(ss.str());

		for (unsigned int i = 0; i < _button.size(); i++){
			if (_button[i].isOver() && !lockMouse){
				selectionState = i;
			}
			_button[i].update(i == selectionState);
		}

		while (_window->pollEvent(*_e)){
			if (_e->type == sf::Event::KeyPressed){
				if (_e->key.code == sf::Keyboard::Up && selectionState > 0){
					selectionState--;
				}
				else if (_e->key.code == sf::Keyboard::Down && selectionState < _button.size() - 1){
					selectionState++;
				}
			}
			else if (_e->type == sf::Event::MouseMoved){
				lockMouse = false;
			}
		}

		if (_button[BUT_CONTINUE].isPressed()){
			_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));
			ns::spawnPoint = 1000.f;
			if (_lSettings->_level < _lSettings->_levelVector.size() - 1){
				ns::gameStateLoader->saveLevelData(_lSettings->_campaignVector[_lSettings->_campaign], _lSettings->_levelVector[_lSettings->_level + 1], true);
				_lSettings->_level++;
				ns::runningState = false;
				ns::endOfLevelState = false;
				ns::deathState = false;
				ns::restartState = false;
				ns::reloadState = true;
			}
			else{
				ns::runningState = false;
			}
			selectionState = 0;
		}
		else if (_button[BUT_RESTART].isPressed()){
			_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));
			ns::spawnPoint = 1000.f;
			if (_lSettings->_level < _lSettings->_levelVector.size() - 1){
				ns::gameStateLoader->saveLevelData(_lSettings->_campaignVector[_lSettings->_campaign], _lSettings->_levelVector[_lSettings->_level + 1], true);
			}
			ns::runningState = false;
			ns::endOfLevelState = false;
			ns::deathState = false;
			ns::restartState = true;
			selectionState = 0;
		}
		else if (_button[BUT_EXIT].isPressed()){
			_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));
			ns::spawnPoint = 1000.f;
			if (_lSettings->_level < _lSettings->_levelVector.size() - 1){
				ns::gameStateLoader->saveLevelData(_lSettings->_campaignVector[_lSettings->_campaign], _lSettings->_levelVector[_lSettings->_level + 1], true);
			}
			ns::runningState = false;
			ns::endOfLevelState = false;
			selectionState = 0;
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
		for (unsigned int i = 0; i < _button.size(); i++){
			_button[i].setFillColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, _backgroundShape.getFillColor().a * 2));
			_button[i]._text.setColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, _backgroundShape.getFillColor().a * 2));
		}
		_timeText.setColor(sf::Color::Color(255, 255, 255, _backgroundShape.getFillColor().a * 2));
	}
	else{
		for (unsigned int i = 0; i < _button.size(); i++){
			_button[i].setFillColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, 255));
			_button[i]._text.setColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, 255));
		}
		_timeText.setColor(sf::Color::Color(255, 255, 255, 255));
	}


	if (_backgroundShape.getFillColor().a >= 5){
		sf::View view;
		view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
		view.setSize(sf::Vector2f(1920, 1200));
		_window->setView(view);

		_window->draw(_backgroundShape);
		_window->draw(_timeText);

		for (unsigned int i = 0; i < _button.size(); i++){
			_window->draw(_button[i]);
			_window->draw(_button[i]._text);
		}
	}
}

void Endmenu::init()
{
	_backgroundShape.setSize(sf::Vector2f(1920, 1200));
	_backgroundShape.setFillColor(sf::Color::Color(0, 0, 0, 0));

	_font.loadFromFile("Resources/Common/Fonts/galvanize.ttf");

	_timeText.setFont(_font);
	_timeText.setCharacterSize(60);
	_timeText.setPosition(1000, 300);

	sf::Image image;
	image.loadFromFile("Resources/Common/Graphics/UI/button_start.png");
	_font.loadFromFile("Resources/Common/Fonts/galvanize.ttf");


	for (int i = 0; i < BUT_LAST; i++)
		_button.emplace_back(GameButton(_window));

	_button[BUT_CONTINUE].load(250, 150, 300, 300, image);
	_button[BUT_CONTINUE]._text.setFont(_font);
	_button[BUT_CONTINUE]._text.setCharacterSize(40);
	_button[BUT_CONTINUE]._text.setString("Continue");
	_button[BUT_CONTINUE]._text.setColor(sf::Color::Color(205, 197, 191, 255));

	_button[BUT_RESTART].load(250, 150, _button[BUT_CONTINUE].getPosition().x, _button[BUT_CONTINUE].getPosition().y + 175, image);
	_button[BUT_RESTART]._text.setFont(_font);
	_button[BUT_RESTART]._text.setCharacterSize(40);
	_button[BUT_RESTART]._text.setString("Restart");
	_button[BUT_RESTART]._text.setColor(sf::Color::Color(205, 197, 191, 255));

	_button[BUT_EXIT].load(250, 150, _button[BUT_RESTART].getPosition().x, _button[BUT_RESTART].getPosition().y + 175, image);
	_button[BUT_EXIT]._text.setFont(_font);
	_button[BUT_EXIT]._text.setCharacterSize(40);
	_button[BUT_EXIT]._text.setString("Exit to menu");
	_button[BUT_EXIT]._text.setColor(sf::Color::Color(205, 197, 191, 255));
}