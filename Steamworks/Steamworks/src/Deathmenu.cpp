#include "Deathmenu.h"

#include "Globals.h"


namespace
{
	int selectionState = 0;

	bool lockMouse = true;
}


Deathmenu::Deathmenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e)
{
	init();
}

Deathmenu::~Deathmenu(void)
{}


void Deathmenu::showMenu()
{
	if (ns::deathState){
		if (_backgroundShape.getFillColor().a < 100){
			_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, _backgroundShape.getFillColor().a + 5));
		}

		for (unsigned int i = 0; i < _button.size(); i++){
			if (_button[i].isOver() && !lockMouse){
				selectionState = i;
			}
			_button[i].update(i == selectionState);
		}

		if (lockMouse)
			_window->setMouseCursorVisible(false);
		else
			_window->setMouseCursorVisible(true);


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
		if (_button[BUT_RESTART].isPressed()){
			_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, 0));
			ns::runningState = false;
			ns::deathState = false;
			ns::restartState = true;
			selectionState = 0;
		}
		else if (_button[BUT_EXIT].isPressed()){
			_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, 0));
			ns::spawnPoint = 1000.f;
			ns::runningState = false;
			ns::restartState = false;
			selectionState = 0;
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
	if (_backgroundShape.getFillColor().a < 127){
		for (unsigned int i = 0; i < _button.size(); i++){
			_button[i].setFillColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, _backgroundShape.getFillColor().a * 2));
			_button[i]._text.setColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, _backgroundShape.getFillColor().a * 2));
		}
	}
	else{
		for (unsigned int i = 0; i < _button.size(); i++){
			_button[i].setFillColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, 255));
			_button[i]._text.setColor(sf::Color::Color(_button[i].getFillColor().r, _button[i].getFillColor().g, _button[i].getFillColor().b, 255));
		}
	}

	if (_backgroundShape.getFillColor().a >= 5){
		sf::View view;
		view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
		view.setSize(sf::Vector2f(1920, 1200));
		_window->setView(view);

		_window->draw(_backgroundShape);
		for (unsigned int i = 0; i < _button.size(); i++){
			_window->draw(_button[i]);
			_window->draw(_button[i]._text);
		}
	}
}

void Deathmenu::init()
{
	_backgroundShape.setSize(sf::Vector2f(1920, 1200));
	_backgroundShape.setFillColor(sf::Color::Color(255, 0, 0, 0));

	sf::Image image;
	image.loadFromFile("Resources/Common/Graphics/UI/button_start.png");
	_font.loadFromFile("Resources/Common/Fonts/galvanize.ttf");


	for (int i = 0; i < BUT_LAST; i++)
		_button.emplace_back(GameButton(_window));

	_button[BUT_RESTART].load(250, 150, 300, 300, image);
	_button[BUT_RESTART]._text.setFont(_font);
	_button[BUT_RESTART]._text.setCharacterSize(40);
	_button[BUT_RESTART]._text.setString("Restart");
	_button[BUT_RESTART]._text.setColor(sf::Color::Color(205, 197, 191, 255));

	_button[BUT_EXIT].load(250, 150, _button[BUT_RESTART].getPosition().x, _button[BUT_RESTART].getPosition().y + 175, image);
	_button[BUT_EXIT]._text.setFont(_font);
	_button[BUT_EXIT]._text.setCharacterSize(40);
	_button[BUT_EXIT]._text.setString("Exit To Menu");
	_button[BUT_EXIT]._text.setColor(sf::Color::Color(205, 197, 191, 255));
}