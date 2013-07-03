#include "Mainmenu.h"


namespace
{
	int t_campaign = 0;
}


Mainmenu::Mainmenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e),
	  selectionState(0),
	  menuState(-1)
{}


Mainmenu::~Mainmenu(void)
{
	_window->close();
}


bool Mainmenu::showMenu()
{
	init();

	while (1){
		update();
		draw();

		if (mainButton[BUT_START].isPressed()){
			return true;
		}
		else if (mainButton[BUT_CAMPAIGN].isPressed()){

		}
		else if (mainButton[BUT_LEVEL].isPressed()){

		}
		else if (mainButton[BUT_SETTINGS].isPressed()){

		}
		else if (mainButton[BUT_CREDITS].isPressed()){

		}
		else if (mainButton[BUT_EXIT].isPressed()){
			return false;
		}
	}
}


void Mainmenu::init()
{
	mainButton.clear();

	if (!_window->isOpen()){
		if (_engineSettings.fullScreen)
			_window->create(sf::VideoMode(_engineSettings.resolution.x, _engineSettings.resolution.y), "Template title :(", sf::Style::Fullscreen, sf::ContextSettings(0, 0, _engineSettings.antiAliasing, 2, 0));
		else
			_window->create(sf::VideoMode(_engineSettings.resolution.x, _engineSettings.resolution.y), "Template title :(", sf::Style::Default, sf::ContextSettings(0, 0, _engineSettings.antiAliasing, 2, 0));
	}
	_window->setVerticalSyncEnabled(_engineSettings.vSync);
	sf::View view;
	view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
	view.setSize(sf::Vector2f(1920, 1200));
	_window->setView(view);

	mainButton.reserve(BUT_LAST);
	for (int i = 0; i < BUT_LAST; i++){
		mainButton.emplace_back(GameButton(_window));
	}
	sf::Image image;
	image.loadFromFile("Resources/Common/Graphics/UI/button_start.png");
	_font.loadFromFile("Resources/Common/Fonts/Amble-Bold.ttf");

	//Start
	mainButton[BUT_START].load(250, 150, 200, 200, image);
	mainButton[BUT_START]._text.setFont(_font);
	mainButton[BUT_START]._text.setCharacterSize(40);
	mainButton[BUT_START]._text.setString("Start");
	mainButton[BUT_START]._text.setColor(sf::Color::Black);

	//Campaign
	mainButton[BUT_CAMPAIGN].load(200, 100, 200, mainButton[BUT_START].getPosition().y + 200, image);
	mainButton[BUT_CAMPAIGN]._text.setFont(_font);
	mainButton[BUT_CAMPAIGN]._text.setCharacterSize(30);
	mainButton[BUT_CAMPAIGN]._text.setString("Select\ncampaign");
	mainButton[BUT_CAMPAIGN]._text.setColor(sf::Color::Black);

	//Level
	mainButton[BUT_LEVEL].load(200, 100, 200, mainButton[BUT_CAMPAIGN].getPosition().y + 125, image);
	mainButton[BUT_LEVEL]._text.setFont(_font);
	mainButton[BUT_LEVEL]._text.setCharacterSize(30);
	mainButton[BUT_LEVEL]._text.setString("Select\nlevel");
	mainButton[BUT_LEVEL]._text.setColor(sf::Color::Black);

	//Settings
	mainButton[BUT_SETTINGS].load(200, 100, 200, mainButton[BUT_LEVEL].getPosition().y + 125, image);
	mainButton[BUT_SETTINGS]._text.setFont(_font);
	mainButton[BUT_SETTINGS]._text.setCharacterSize(30);
	mainButton[BUT_SETTINGS]._text.setString("Settings");
	mainButton[BUT_SETTINGS]._text.setColor(sf::Color::Black);

	//Credits
	mainButton[BUT_CREDITS].load(150, 75, 200, mainButton[BUT_SETTINGS].getPosition().y + 150, image);
	mainButton[BUT_CREDITS]._text.setFont(_font);
	mainButton[BUT_CREDITS]._text.setCharacterSize(26);
	mainButton[BUT_CREDITS]._text.setString("Credits");
	mainButton[BUT_CREDITS]._text.setColor(sf::Color::Black);

	//Exit
	mainButton[BUT_EXIT].load(150, 75, 200, mainButton[BUT_CREDITS].getPosition().y + 100, image);
	mainButton[BUT_EXIT]._text.setFont(_font);
	mainButton[BUT_EXIT]._text.setCharacterSize(26);
	mainButton[BUT_EXIT]._text.setString("Exit");
	mainButton[BUT_EXIT]._text.setColor(sf::Color::Black);

	selectionShape.setRadius(4);
	selectionShape.setFillColor(sf::Color::Red);
	selectionShape.setOutlineThickness(2);
	selectionShape.setOutlineColor(sf::Color::White);
	selectionShape.setOrigin(selectionShape.getRadius(), selectionShape.getRadius());
	selectionShape.setPosition(mainButton[BUT_START].getPosition().x - 25, mainButton[BUT_START].getPosition().y + (mainButton[BUT_START].getGlobalBounds().height / 2));
}

void Mainmenu::update()
{
	
	//Campaign && level selection
	std::stringstream ss;
	ss.str("");

	int t_level = std::atoi(_loadSettings._level.c_str());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && t_level > 1){
		t_level--;
		ss << t_level;
		_loadSettings._level = ss.str();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		t_level++;
		ss << t_level;
		_loadSettings._level = ss.str();
	}
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && t_campaign > 0){
		t_campaign--;
		_loadSettings._campaign = _loadSettings._campaignVector[t_campaign];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _loadSettings._campaignVector.size() - 1 > t_campaign){
		t_campaign++;
		_loadSettings._campaign = _loadSettings._campaignVector[t_campaign];
	}
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

	//Button state updates
	for (int i = 0; i < mainButton.size(); i++){
		if (menuState <= -1){
			if (mainButton[i].isOver()) selectionState = i;
			mainButton[i].update(i == selectionState);
		}
		else{
			mainButton[i].update();
		}
	}

	//Selection shape repositioning
	selectionShape.setPosition(mainButton[selectionState].getPosition().x - 25, mainButton[selectionState].getPosition().y + (mainButton[selectionState].getGlobalBounds().height / 2));

	//Events
	while (_window->pollEvent(*_e)){
		if (_e->type == sf::Event::KeyPressed && menuState <= -1){
			if (_e->key.code == sf::Keyboard::Up && selectionState > 0) selectionState--;
			else if (_e->key.code == sf::Keyboard::Down && selectionState < BUT_LAST - 1) selectionState++;
		}
	}
}

void Mainmenu::draw()
{
	_window->clear();

	for (int i = 0; i < mainButton.size(); i++){
		_window->draw(mainButton[i]);
		_window->draw(mainButton[i]._text);
	}

	_window->draw(selectionShape);

	_window->display();
}