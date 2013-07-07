#include "Mainmenu.h"



Mainmenu::Mainmenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e),
	  selectionState(0),
	  subSelectionState(0),
	  subSelectionMax(0),
	  menuState(0),
	  lockMouse(false)
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
			titleMusic.stop();
			menuState = BUT_START;
			return true;
		}
		else if (mainButton[BUT_CAMPAIGN].isPressed() && menuState == 0){
			menuState = BUT_CAMPAIGN;
		}
		else if (mainButton[BUT_LEVEL].isPressed() && menuState == 0){
			menuState = BUT_LEVEL;
			_loadSettings.loadLevels();
			initLevels();
		}
		else if (mainButton[BUT_SETTINGS].isPressed() && menuState == 0){
			menuState = BUT_SETTINGS;
		}
		else if (mainButton[BUT_CREDITS].isPressed() && menuState == 0){
			menuState = BUT_CREDITS;
		}
		else if (mainButton[BUT_EXIT].isPressed() && menuState == 0){
			return false;
		}
	}
}


void Mainmenu::init()
{
	mainButton.clear();
	campaignText.clear();

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

	//Main buttons
	/////////////////////////////////////////////////////////
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

	//Sub menu buttons
	/////////////////////////////////////////////////////////
	//Campaign
	campaignText.reserve(_loadSettings._campaignVector.size());
	for (unsigned int i = 0; i < _loadSettings._campaignVector.size(); i++){
		campaignText.emplace_back(sf::Text());
		campaignText.back().setFont(_font);
		campaignText.back().setCharacterSize(50);

		campaignText.back().setString(_loadSettings._campaignVector[i]);
	}
	campaignText[0].setPosition(800, 500);

	//Level
	//Nuthing to see hiar :)

	//Settings

	//Credits

	selectionShape.setRadius(4);
	selectionShape.setFillColor(sf::Color::Red);
	selectionShape.setOutlineThickness(2);
	selectionShape.setOutlineColor(sf::Color::White);
	selectionShape.setOrigin(selectionShape.getRadius(), selectionShape.getRadius());
	selectionShape.setPosition(mainButton[BUT_START].getPosition().x - 25, mainButton[BUT_START].getPosition().y + (mainButton[BUT_START].getGlobalBounds().height / 2));

	image.loadFromFile("Resources/Common/Graphics/UI/sheet_tsuge.png");
	titleAnimation.loadSheet(image, 0, 0, 1000, 1000, 8, true);
	titleAnimation.setStepInterval(6);

	titleBackground.setSize(sf::Vector2f(1200, 1200));
	titleBackground.setTexture(&titleAnimation.getCurrentTexture());
	titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, 0));
	titleBackground.setPosition(720, 0);

	titleMusic.openFromFile("Resources/Common/Audio/Music/junakulkee.ogg");
	titleMusic.setLoop(true);
	titleMusic.setVolume(75);
	titleMusic.play();
}

void Mainmenu::update()
{
	switch (menuState)
	{
		case BUT_CAMPAIGN:
			{
			subSelectionMax = _loadSettings._campaignVector.size() - 1;

			subSelectionState = _loadSettings._campaign;

			if (campaignText[0].getPosition().y < 500 - (subSelectionState * 60)) campaignText[0].move(0, 4);
			else if (campaignText[0].getPosition().y > 500 - (subSelectionState * 60)) campaignText[0].move(0, -4);
			for (unsigned int i = 1; i < campaignText.size(); i++){
				campaignText[i].setPosition(campaignText[0].getPosition().x, campaignText[0].getPosition().y + (60 * i));

				if (i == subSelectionState) campaignText[i].setColor(sf::Color::White);
				else campaignText[i].setColor(sf::Color::Color(255, 255, 255, 128));
			}
			if (subSelectionState != 0) campaignText[0].setColor(sf::Color::Color(255, 255, 255, 128));
			else campaignText[0].setColor(sf::Color::White);
			

			break;
			}
		case BUT_LEVEL:
			{
			subSelectionMax = _loadSettings._levelVector.size() - 1;

			subSelectionState = _loadSettings._level;

			if (levelText[0].getPosition().y < 500 - (subSelectionState * 60)) levelText[0].move(0, 4);
			else if (levelText[0].getPosition().y > 500 - (subSelectionState * 60)) levelText[0].move(0, -4);
			if (_loadSettings._levelVector.size() > 1){
				for (unsigned int i = 1; i < levelText.size(); i++){
					levelText[i].setPosition(levelText[0].getPosition().x, levelText[0].getPosition().y + (60 * i));

					if (i == subSelectionState) levelText[i].setColor(sf::Color::White);
					else levelText[i].setColor(sf::Color::Color(255, 255, 255, 128));
				}
			}
			if (subSelectionState != 0) levelText[0].setColor(sf::Color::Color(255, 255, 255, 128));
			else levelText[0].setColor(sf::Color::White);


			break;
			}
		case BUT_SETTINGS:
			{

			break;
			}
		case BUT_CREDITS:
			{

			break;
			}
		default:
			{
			//Main button state updates
			for (unsigned int i = 0; i < mainButton.size(); i++){
				if (menuState <= 0){
					if (mainButton[i].isOver() && !lockMouse) selectionState = i;
					mainButton[i].update(i == selectionState);
				}
				else{
					mainButton[i].update();
				}
			}
			}
	}

	//Selection shape repositioning
	switch (menuState)
	{
		case BUT_CAMPAIGN: //Campaign
			selectionShape.setPosition(campaignText[subSelectionState].getPosition().x - 25, campaignText[subSelectionState].getPosition().y + campaignText[subSelectionState].getGlobalBounds().height);
			break;
		case BUT_LEVEL: //Level
			{
			if (levelText.size() <= 1){
				selectionShape.setPosition(levelText[subSelectionState].getPosition().x - 25, levelText[subSelectionState].getPosition().y + (levelText[subSelectionState].getLocalBounds().height / 1.5));
			}
			else{
				selectionShape.setPosition(levelText[subSelectionState].getPosition().x - 25, levelText[subSelectionState].getPosition().y + levelText[subSelectionState].getLocalBounds().height);
			}
			break;
			}
		case BUT_SETTINGS: //Settings
			selectionShape.setPosition(mainButton[selectionState].getPosition().x - 25, mainButton[selectionState].getPosition().y + (mainButton[selectionState].getGlobalBounds().height / 2));
			break;
		case BUT_CREDITS: //Credits
			selectionShape.setPosition(mainButton[selectionState].getPosition().x - 25, mainButton[selectionState].getPosition().y + (mainButton[selectionState].getGlobalBounds().height / 2));
			break;
		default: //Main menu
			selectionShape.setPosition(mainButton[selectionState].getPosition().x - 25, mainButton[selectionState].getPosition().y + (mainButton[selectionState].getGlobalBounds().height / 2));
	}
	

	if (menuState <= 0){
		if (titleBackground.getFillColor().a < 255)
			titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, titleBackground.getFillColor().a + 1));
		if (titleAnimation.frameChanged()) titleBackground.setTexture(&titleAnimation.getCurrentTexture());
		titleAnimation.stepForward();
	}
	else{
		titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, 0));
	}

		//Events
	while (_window->pollEvent(*_e)){
		if (_e->type == sf::Event::KeyPressed && menuState <= 0){
			if (_e->key.code == sf::Keyboard::Up && selectionState > 0){
				selectionState--;
				lockMouse = true;

			}
			else if (_e->key.code == sf::Keyboard::Down && selectionState < BUT_LAST - 1){
				selectionState++;
				lockMouse = true;
			}
		}
		else if (_e->type == sf::Event::KeyPressed && menuState > 0){
			if (_e->key.code == sf::Keyboard::Up && subSelectionState > 0){
				subSelectionState--;
				lockMouse = true;
			}
			else if (_e->key.code == sf::Keyboard::Down && subSelectionState < subSelectionMax){
				subSelectionState++;
				lockMouse = true;
			}
			else if (_e->key.code == sf::Keyboard::Escape){
				menuState = 0;
				subSelectionState = 0;
				subSelectionMax = 0;
			}
		}

		//Mouse events
		if (_e->type == sf::Event::MouseMoved) lockMouse = false;
	}
}

void Mainmenu::draw()
{
	_window->clear();

	switch (menuState)
	{
		case BUT_CAMPAIGN:
			for (unsigned int i = 0; i < campaignText.size(); i++)
				_window->draw(campaignText[i]);
			break;
		case BUT_LEVEL:
			for (unsigned int i = 0; i < levelText.size(); i++)
				_window->draw(levelText[i]);
			break;
		default:
			_window->draw(titleBackground);
	}

	for (unsigned int i = 0; i < mainButton.size(); i++){
		_window->draw(mainButton[i]);
		_window->draw(mainButton[i]._text);
	}

	_window->draw(selectionShape);

	_window->display();
}

void Mainmenu::initLevels()
{
	levelText.clear();

	levelText.reserve(_loadSettings._levelVector.size());
	for (unsigned int i = 0; i <_loadSettings._levelVector.size(); i++){
		levelText.emplace_back(sf::Text());
		levelText.back().setFont(_font);
		levelText.back().setCharacterSize(50);

		levelText.back().setString(_loadSettings._levelVector[i]);
	}
	levelText[0].setPosition(800, 500);

	subSelectionMax = levelText.size() - 1;
}