#include "Mainmenu.h"


namespace
{
	GameText _text[3];

	int t_campaign = 0;
}


Mainmenu::Mainmenu(sf::RenderWindow* window, sf::Event& e)
	:_window(window),
	 _e(e)
{}


Mainmenu::~Mainmenu(void)
{
	_window->close();
}


bool Mainmenu::showMenu()
{
	init();

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		update();
		draw();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			return true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			return false;
		}
	}
}

LoadSettings Mainmenu::getSettings()
{
	return _settings;
}


void Mainmenu::init()
{
	if (!_window->isOpen()) _window->create(sf::VideoMode(g_windowWidth, g_windowHeight), "Template title :(", sf::Style::Close);
	_window->setVerticalSyncEnabled(g_useVSync);
	sf::View view;
	view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
	view.setSize(sf::Vector2f(1920, 1200));
	_window->setView(view);

	_text[0].setCharacterSize(75);
	_text[0].setString("#green Enter - Start\n#red Escape - Exit");
	_text[0].setOrigin(_text[0].getLocalBounds().width / 2, _text[0].getLocalBounds().height / 2);
	_text[0].setPosition(1920 / 2, 600);
	
	_text[1].setCharacterSize(50);
	_text[1].setPosition(1600, 550);

	_text[2].setCharacterSize(50);
	_text[2].setPosition(1600, 600);
}

void Mainmenu::update()
{
	std::stringstream ss;
	ss.str("");

	
	int t_level = std::atoi(_settings._level.c_str());
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && t_level > 1){
		t_level--;
		ss << t_level;
		_settings._level = ss.str();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		t_level++;
		ss << t_level;
		_settings._level = ss.str();
	}
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && t_campaign > 0){
		t_campaign--;
		_settings._campaign = _settings._campaignVector[t_campaign];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _settings._campaignVector.size() - 1 > t_campaign){
		t_campaign++;
		_settings._campaign = _settings._campaignVector[t_campaign];
	}
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));



	
	ss.str("");
	ss << _settings._campaign;
	_text[1].setString(ss.str());

	ss.str("");
	ss << _settings._level;
	_text[2].setString(ss.str());

	while (_window->pollEvent(_e));
}

void Mainmenu::draw()
{
	_window->clear();

	_window->draw(_text[0]);
	_window->draw(_text[1]);
	_window->draw(_text[2]);

	_window->display();
}