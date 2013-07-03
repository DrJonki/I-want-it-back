#include "Mainmenu.h"


namespace
{
	int t_campaign = 0;

}


Mainmenu::Mainmenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || button[BUT_START].isPressed()){
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			return true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || button[BUT_EXIT].isPressed()){
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			return false;
		}
	}
}


void Mainmenu::init()
{
	button.clear();

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

	button.reserve(BUT_LAST);
	for (int i = 0; i < BUT_LAST; i++){
		button.emplace_back(GameButton(_window));
	}
	sf::Image image;
	image.loadFromFile("Resources/Common/Graphics/UI/button_start.png");
	_font.loadFromFile("Resources/Common/Fonts/Amble-Bold.ttf");

	//Start
	button[BUT_START].load(250, 150, 200, 200, image);
	button[BUT_START]._text.setFont(_font);
	button[BUT_START]._text.setCharacterSize(40);
	button[BUT_START]._text.setString("Start");
	button[BUT_START]._text.setColor(sf::Color::Black);

	//Campaign
	button[BUT_CAMPAIGN].load(200, 100, 200, 400, image);
	button[BUT_CAMPAIGN]._text.setFont(_font);
	button[BUT_CAMPAIGN]._text.setCharacterSize(30);
	button[BUT_CAMPAIGN]._text.setString("Select\ncampaign");
	button[BUT_CAMPAIGN]._text.setColor(sf::Color::Black);

	//Level
	button[BUT_LEVEL].load(200, 100, 200, 550, image);
	button[BUT_LEVEL]._text.setFont(_font);
	button[BUT_LEVEL]._text.setCharacterSize(30);
	button[BUT_LEVEL]._text.setString("Select\nlevel");
	button[BUT_LEVEL]._text.setColor(sf::Color::Black);

	//Settings
	button[BUT_SETTINGS].load(200, 100, 200, 700, image);
	button[BUT_SETTINGS]._text.setFont(_font);
	button[BUT_SETTINGS]._text.setCharacterSize(30);
	button[BUT_SETTINGS]._text.setString("Settings");
	button[BUT_SETTINGS]._text.setColor(sf::Color::Black);

	//Credits
	button[BUT_CREDITS].load(150, 75, 200, 875, image);
	button[BUT_CREDITS]._text.setFont(_font);
	button[BUT_CREDITS]._text.setCharacterSize(26);
	button[BUT_CREDITS]._text.setString("Credits");
	button[BUT_CREDITS]._text.setColor(sf::Color::Black);

	//Exit
	button[BUT_EXIT].load(150, 75, 400, 875, image);
	button[BUT_EXIT]._text.setFont(_font);
	button[BUT_EXIT]._text.setCharacterSize(26);
	button[BUT_EXIT]._text.setString("Exit");
	button[BUT_EXIT]._text.setColor(sf::Color::Black);
}

void Mainmenu::update()
{
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

	for (int i = 0; i < button.size(); i++){
		button[i].update();
	}

	while (_window->pollEvent(*_e));
}

void Mainmenu::draw()
{
	_window->clear();

	for (int i = 0; i < button.size(); i++){
		_window->draw(button[i]);
		_window->draw(button[i]._text);
	}

	_window->display();
}