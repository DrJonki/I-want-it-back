#include "Mainmenu.h"

#include <sstream>
#include <cmath>

#include "Globals.h"
#include "Misc.h"

namespace
{
	int selectionState = 0;
	int subSelectionState = 0;
	int subSelectionMax = 0;
	int menuState = 0;

	bool lockMouse = true;

	bool loaded = false;
	
	bool exitState = false;
}

Mainmenu::Mainmenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e),
	  titleMinAlpha(70),
	  levelMenuSelected(false)
{}

Mainmenu::~Mainmenu(void)
{
	_window->close();
}


bool Mainmenu::showMenu()
{
	selectionState = 0;
	subSelectionState = 0;
	subSelectionMax = 0;
	menuState = 0;
	lockMouse = true;
	exitState = false;

	if (!loaded) init();
	sf::View view;
	view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
	view.setSize(sf::Vector2f(1920, 1200));
	_window->setView(view);
	titleMusic.setVolume(0);
	titleMusic.play();
	titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, 0));
	
	while (!ns::exitState && !ns::deathState){
		if (mainButton[BUT_START].isPressed() && !ns::endOfLevelState){
			titleMusic.stop();
			menuState = BUT_START;
			return true;
		}
		else if (mainButton[BUT_LEVEL].isPressed() && menuState == 0){
			menuState = BUT_LEVEL;
			subSelectionState = _loadSettings._campaign;
			levelMenuSelected = false;

			_loadSettings.loadLevels();
			initLevels();
			levelSelection = _loadSettings._level;
		}
		else if (mainButton[BUT_INFO].isPressed() && menuState == 0){
			menuState = BUT_INFO;
		}
		else if (mainButton[BUT_SETTINGS].isPressed() && menuState == 0){
			menuState = BUT_SETTINGS;
		}
		else if (mainButton[BUT_CREDITS].isPressed() && menuState == 0){
			menuState = BUT_CREDITS;
			creditsText[0].setPosition(1000, 1200);
			creditsText[1].setPosition(creditsText[0].getPosition().x, creditsText[0].getPosition().y + 150);
		}
		else if ((mainButton[BUT_EXIT].isPressed() && menuState == 0) || exitState){
			return false;
		}

		if (_engineSettings.vSync){
			if (updateClock.getElapsedTime().asSeconds() > ns::g_updateTimerValue){
				update();
				draw();
			}
		}
		else {
			if (updateClock.getElapsedTime().asSeconds() > ns::g_updateTimerValue){
				update();
			}
			draw();
		}
	}

	return false;
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
	mainButton[BUT_START].load(250, 150, 100, 200, image);
	mainButton[BUT_START]._text.setFont(_font);
	mainButton[BUT_START]._text.setCharacterSize(40);
	mainButton[BUT_START]._text.setString("Start");
	mainButton[BUT_START]._text.setColor(sf::Color::Color(205,197,191, 255));
	//Campaign
	mainButton[BUT_LEVEL].load(200, 100, mainButton[BUT_START].getPosition().x, mainButton[BUT_START].getPosition().y + 200, image);
	mainButton[BUT_LEVEL]._text.setFont(_font);
	mainButton[BUT_LEVEL]._text.setCharacterSize(30);
	mainButton[BUT_LEVEL]._text.setString("Select\ncampaign");
	mainButton[BUT_LEVEL]._text.setColor(sf::Color::Color(205,197,191, 255));
	//Level
	mainButton[BUT_INFO].load(200, 100, mainButton[BUT_START].getPosition().x, mainButton[BUT_LEVEL].getPosition().y + 125, image);
	mainButton[BUT_INFO]._text.setFont(_font);
	mainButton[BUT_INFO]._text.setCharacterSize(30);
	mainButton[BUT_INFO]._text.setString("Instructions");
	mainButton[BUT_INFO]._text.setColor(sf::Color::Color(205,197,191, 255));
	//Settings
	mainButton[BUT_SETTINGS].load(200, 100, mainButton[BUT_START].getPosition().x, mainButton[BUT_INFO].getPosition().y + 125, image);
	mainButton[BUT_SETTINGS]._text.setFont(_font);
	mainButton[BUT_SETTINGS]._text.setCharacterSize(30);
	mainButton[BUT_SETTINGS]._text.setString("Settings");
	mainButton[BUT_SETTINGS]._text.setColor(sf::Color::Color(205,197,191, 255));
	//Credits
	mainButton[BUT_CREDITS].load(150, 75, mainButton[BUT_START].getPosition().x, mainButton[BUT_SETTINGS].getPosition().y + 150, image);
	mainButton[BUT_CREDITS]._text.setFont(_font);
	mainButton[BUT_CREDITS]._text.setCharacterSize(26);
	mainButton[BUT_CREDITS]._text.setString("Credits");
	mainButton[BUT_CREDITS]._text.setColor(sf::Color::Color(205,197,191, 255));
	//Exit
	mainButton[BUT_EXIT].load(150, 75, mainButton[BUT_START].getPosition().x, mainButton[BUT_CREDITS].getPosition().y + 100, image);
	mainButton[BUT_EXIT]._text.setFont(_font);
	mainButton[BUT_EXIT]._text.setCharacterSize(26);
	mainButton[BUT_EXIT]._text.setString("Exit");
	mainButton[BUT_EXIT]._text.setColor(sf::Color::Color(205,197,191, 255));

	//Confirmation buttons
	confirmButton.emplace_back(GameButton(_window));
	confirmButton.emplace_back(GameButton(_window));

	confirmButton[CON_APPLY].load(100, 65, 600, 500, image);
	confirmButton[CON_APPLY]._text.setFont(_font);
	confirmButton[CON_APPLY]._text.setCharacterSize(22);
	confirmButton[CON_APPLY]._text.setString("Apply >>");
	confirmButton[CON_APPLY]._text.setColor(sf::Color::Color(205,197,191, 255));

	confirmButton[CON_BACK].load(100, 65, confirmButton[CON_APPLY].getPosition().x, confirmButton[CON_APPLY].getPosition().y + 100, image);
	confirmButton[CON_BACK]._text.setFont(_font);
	confirmButton[CON_BACK]._text.setCharacterSize(24);
	confirmButton[CON_BACK]._text.setString("<< Back");
	confirmButton[CON_BACK]._text.setColor(sf::Color::Color(205,197,191, 255));

	//Arrow buttons
	for (int i = 0; i < 4; i++)
		arrowButton.emplace_back(GameButton(_window));

	image.loadFromFile("Resources/Common/Graphics/UI/arrow.png");

	arrowButton[ARR_UP].load(32, 32, 0, 0, image);
	arrowButton[ARR_DOWN].load(32, 32, 0, 0, image);
	arrowButton[ARR_LEFT].load(32, 32, 0, 0, image);
	arrowButton[ARR_RIGHT].load(32, 32, 0, 0, image);
	for (int i = 0; i < 4; i++)
		arrowButton[i].setOrigin(arrowButton[i].getSize().x / 2, arrowButton[i].getSize().y / 2);
	arrowButton[ARR_UP].setRotation(180);
	arrowButton[ARR_LEFT].setRotation(90);
	arrowButton[ARR_RIGHT].setRotation(270);

	//Sub menu buttons
	/////////////////////////////////////////////////////////
	image.loadFromFile("Resources/Common/Graphics/UI/button_start.png");

	//Campaign
	campaignText.reserve(_loadSettings._campaignVector.size());
	for (unsigned int i = 0; i < _loadSettings._campaignVector.size(); i++){
		campaignText.emplace_back(sf::Text());
		campaignText.back().setFont(_font);
		campaignText.back().setCharacterSize(50);

		campaignText.back().setString(_loadSettings._campaignVector[i]);
	}
	campaignText[0].setPosition(800, 500);

	levelMenuText.setFont(_font);
	levelMenuText.setCharacterSize(55);
	levelMenuText.setString("Campaign           Level");
	levelMenuText.setColor(sf::Color::White);
	levelMenuText.setPosition(800, 300);
	//Level
	//Nuthing to see hiar :)

	//Instructions
	infoTexture[0].loadFromFile("Resources/Common/Graphics/UI/info1.png");
	infoTexture[1].loadFromFile("Resources/Common/Graphics/UI/info2.png");
	infoTexture[2].loadFromFile("Resources/Common/Graphics/UI/info3.png");

	infoShape.setSize(sf::Vector2f(960, 1200));
	infoShape.setTexture(&infoTexture[0]);
	infoShape.setPosition(960, 0);

	//Settings
	settingButton.reserve(SET_LAST);
	settingText.reserve(SET_LAST);
	for (unsigned int i = 0; i < SET_LAST; i++){
		settingButton.emplace_back(GameButton(_window));
		settingText.emplace_back(sf::Text());
	}

	//Resolution
	settingButton[SET_RESOLUTION].load(250, 50, 1000, 200, image);
	settingButton[SET_RESOLUTION]._text.setFont(_font);
	settingButton[SET_RESOLUTION]._text.setCharacterSize(28);
	settingButton[SET_RESOLUTION]._text.setString("Resolution");
	settingButton[SET_RESOLUTION]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_RESOLUTION].setFont(_font);
	settingText[SET_RESOLUTION].setCharacterSize(30);
	settingText[SET_RESOLUTION].setString(ns::getString(_engineSettings.resolution.x) + " x " + ns::getString(_engineSettings.resolution.y));
	settingText[SET_RESOLUTION].setColor(sf::Color::White);
	settingText[SET_RESOLUTION].setOrigin(0, settingText[SET_RESOLUTION].getGlobalBounds().height / 2);
	settingText[SET_RESOLUTION].setPosition(settingButton[SET_RESOLUTION].getPosition().x + settingButton[SET_RESOLUTION].getSize().x + 25, settingButton[SET_RESOLUTION].getPosition().y + (settingButton[SET_RESOLUTION].getSize().y / 3));
	//Vsync
	settingButton[SET_VSYNC].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_RESOLUTION].getPosition().y + 100, image);
	settingButton[SET_VSYNC]._text.setFont(_font);
	settingButton[SET_VSYNC]._text.setCharacterSize(28);
	settingButton[SET_VSYNC]._text.setString("V-Sync");
	settingButton[SET_VSYNC]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_VSYNC].setFont(_font);
	settingText[SET_VSYNC].setCharacterSize(30);
	if (_engineSettings.vSync) settingText[SET_VSYNC].setString("Enabled");
	else settingText[SET_VSYNC].setString("Disabled");
	settingText[SET_VSYNC].setColor(sf::Color::White);
	settingText[SET_VSYNC].setOrigin(0, settingText[SET_VSYNC].getGlobalBounds().height / 2);
	settingText[SET_VSYNC].setPosition(settingButton[SET_VSYNC].getPosition().x + settingButton[SET_VSYNC].getSize().x + 25, settingButton[SET_VSYNC].getPosition().y + (settingButton[SET_VSYNC].getSize().y / 3));

	//Full screen
	settingButton[SET_FULLSCREEN].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_VSYNC].getPosition().y + 75, image);
	settingButton[SET_FULLSCREEN]._text.setFont(_font);
	settingButton[SET_FULLSCREEN]._text.setCharacterSize(28);
	settingButton[SET_FULLSCREEN]._text.setString("Fullscreen");
	settingButton[SET_FULLSCREEN]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_FULLSCREEN].setFont(_font);
	settingText[SET_FULLSCREEN].setCharacterSize(30);
	if (_engineSettings.fullScreen) settingText[SET_FULLSCREEN].setString("Enabled");
	else settingText[SET_FULLSCREEN].setString("Disabled");
	settingText[SET_FULLSCREEN].setColor(sf::Color::White);
	settingText[SET_FULLSCREEN].setOrigin(0, settingText[SET_FULLSCREEN].getGlobalBounds().height / 2);
	settingText[SET_FULLSCREEN].setPosition(settingButton[SET_FULLSCREEN].getPosition().x + settingButton[SET_FULLSCREEN].getSize().x + 25, settingButton[SET_FULLSCREEN].getPosition().y + (settingButton[SET_FULLSCREEN].getSize().y / 3));

	//AA
	settingButton[SET_AA].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_FULLSCREEN].getPosition().y + 75, image);
	settingButton[SET_AA]._text.setFont(_font);
	settingButton[SET_AA]._text.setCharacterSize(28);
	settingButton[SET_AA]._text.setString("Anti-aliasing");
	settingButton[SET_AA]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_AA].setFont(_font);
	settingText[SET_AA].setCharacterSize(30);
	settingText[SET_AA].setString(ns::getString((int)_engineSettings.antiAliasing));
	settingText[SET_AA].setColor(sf::Color::White);
	settingText[SET_AA].setOrigin(0, settingText[SET_AA].getGlobalBounds().height / 2);
	settingText[SET_AA].setPosition(settingButton[SET_AA].getPosition().x + settingButton[SET_AA].getSize().x + 25, settingButton[SET_AA].getPosition().y + (settingButton[SET_AA].getSize().y / 3));

	//Smooth
	settingButton[SET_SMOOTH].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_AA].getPosition().y + 75, image);
	settingButton[SET_SMOOTH]._text.setFont(_font);
	settingButton[SET_SMOOTH]._text.setCharacterSize(24);
	settingButton[SET_SMOOTH]._text.setString("Smooth textures");
	settingButton[SET_SMOOTH]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_SMOOTH].setFont(_font);
	settingText[SET_SMOOTH].setCharacterSize(30);
	if (_engineSettings.smoothTextures) settingText[SET_SMOOTH].setString("Enabled");
	else settingText[SET_SMOOTH].setString("Disabled");
	settingText[SET_SMOOTH].setColor(sf::Color::White);
	settingText[SET_SMOOTH].setOrigin(0, settingText[SET_SMOOTH].getGlobalBounds().height / 2);
	settingText[SET_SMOOTH].setPosition(settingButton[SET_SMOOTH].getPosition().x + settingButton[SET_SMOOTH].getSize().x + 25, settingButton[SET_SMOOTH].getPosition().y + (settingButton[SET_SMOOTH].getSize().y / 3));


	//Global volume
	settingButton[SET_GVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_SMOOTH].getPosition().y + 100, image);
	settingButton[SET_GVOLUME]._text.setFont(_font);
	settingButton[SET_GVOLUME]._text.setCharacterSize(24);
	settingButton[SET_GVOLUME]._text.setString("Global volume");
	settingButton[SET_GVOLUME]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_GVOLUME].setFont(_font);
	settingText[SET_GVOLUME].setCharacterSize(30);
	settingText[SET_GVOLUME].setString(ns::getString(_engineSettings.globalVolume));
	settingText[SET_GVOLUME].setColor(sf::Color::White);
	settingText[SET_GVOLUME].setOrigin(0, settingText[SET_GVOLUME].getGlobalBounds().height / 2);
	settingText[SET_GVOLUME].setPosition(settingButton[SET_GVOLUME].getPosition().x + settingButton[SET_GVOLUME].getSize().x + 25, settingButton[SET_GVOLUME].getPosition().y + (settingButton[SET_GVOLUME].getSize().y / 3));

	//Music volume
	settingButton[SET_MVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_GVOLUME].getPosition().y + 75, image);
	settingButton[SET_MVOLUME]._text.setFont(_font);
	settingButton[SET_MVOLUME]._text.setCharacterSize(24);
	settingButton[SET_MVOLUME]._text.setString("Music volume");
	settingButton[SET_MVOLUME]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_MVOLUME].setFont(_font);
	settingText[SET_MVOLUME].setCharacterSize(30);
	settingText[SET_MVOLUME].setString(ns::getString(_engineSettings.musicVolume));
	settingText[SET_MVOLUME].setColor(sf::Color::White);
	settingText[SET_MVOLUME].setOrigin(0, settingText[SET_MVOLUME].getGlobalBounds().height / 2);
	settingText[SET_MVOLUME].setPosition(settingButton[SET_MVOLUME].getPosition().x + settingButton[SET_MVOLUME].getSize().x + 25, settingButton[SET_MVOLUME].getPosition().y + (settingButton[SET_MVOLUME].getSize().y / 3));

	//Sound volume
	settingButton[SET_SVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_MVOLUME].getPosition().y + 75, image);
	settingButton[SET_SVOLUME]._text.setFont(_font);
	settingButton[SET_SVOLUME]._text.setCharacterSize(24);
	settingButton[SET_SVOLUME]._text.setString("Sound volume");
	settingButton[SET_SVOLUME]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_SVOLUME].setFont(_font);
	settingText[SET_SVOLUME].setCharacterSize(30);
	settingText[SET_SVOLUME].setString(ns::getString(_engineSettings.soundVolume));
	settingText[SET_SVOLUME].setColor(sf::Color::White);
	settingText[SET_SVOLUME].setOrigin(0, settingText[SET_SVOLUME].getGlobalBounds().height / 2);
	settingText[SET_SVOLUME].setPosition(settingButton[SET_SVOLUME].getPosition().x + settingButton[SET_SVOLUME].getSize().x + 25, settingButton[SET_SVOLUME].getPosition().y + (settingButton[SET_SVOLUME].getSize().y / 3));

	//Anbient volume
	settingButton[SET_AVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_SVOLUME].getPosition().y + 75, image);
	settingButton[SET_AVOLUME]._text.setFont(_font);
	settingButton[SET_AVOLUME]._text.setCharacterSize(24);
	settingButton[SET_AVOLUME]._text.setString("Anbient volume");
	settingButton[SET_AVOLUME]._text.setColor(sf::Color::Color(205,197,191, 255));

	settingText[SET_AVOLUME].setFont(_font);
	settingText[SET_AVOLUME].setCharacterSize(30);
	settingText[SET_AVOLUME].setString(ns::getString(_engineSettings.anbientVolume));
	settingText[SET_AVOLUME].setColor(sf::Color::White);
	settingText[SET_AVOLUME].setOrigin(0, settingText[SET_AVOLUME].getGlobalBounds().height / 2);
	settingText[SET_AVOLUME].setPosition(settingButton[SET_AVOLUME].getPosition().x + settingButton[SET_AVOLUME].getSize().x + 25, settingButton[SET_AVOLUME].getPosition().y + (settingButton[SET_AVOLUME].getSize().y / 3));



	//Credits
	creditsText[0].setFont(_font);
	creditsText[0].setCharacterSize(70);
	creditsText[0].setString("Credits");
	creditsText[0].setColor(sf::Color::White);
	creditsText[0].setPosition(1000, 1200);

	creditsText[1].setFont(_font);
	creditsText[1].setCharacterSize(40);
	creditsText[1].setString(_loadSettings._credits);
	creditsText[1].setColor(sf::Color::White);
	creditsText[1].setPosition(creditsText[0].getPosition().x, creditsText[0].getPosition().y + 150);

	//Other
	selectionShape.setRadius(5);
	selectionShape.setFillColor(sf::Color::Red);
	selectionShape.setOutlineThickness(2);
	selectionShape.setOutlineColor(sf::Color::White);
	selectionShape.setOrigin(selectionShape.getRadius(), selectionShape.getRadius());
	selectionShape.setPosition(mainButton[BUT_START].getPosition().x - 25, mainButton[BUT_START].getPosition().y + (mainButton[BUT_START].getGlobalBounds().height / 2));


	titleTexture.loadFromFile("Resources/Common/Graphics/UI/TitleScreen.png");
	titleBackground.setSize(sf::Vector2f(1920, 1200));
	titleBackground.setTexture(&titleTexture);
	titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, 0));
	titleBackground.setPosition(0, 0);

	titleMusic.openFromFile("Resources/Common/Audio/Music/titlemusic.ogg");
	titleMusic.setLoop(true);
	titleMusic.setVolume(0);
	titleMusic.setRelativeToListener(true);

	loaded = true;
}

void Mainmenu::update()
{
	updateClock.restart();

	if (lockMouse) _window->setMouseCursorVisible(false);
	else _window->setMouseCursorVisible(true);

	switch (menuState)
	{
		case BUT_LEVEL:
			{
			if (levelMenuSelected){
				_loadSettings._level = levelSelection;

				confirmButton[CON_BACK].setPosition(600, 505);

				if (levelText[0].getPosition().y < 500 - (levelSelection * 60)) levelText[0].move(0, 4);
				else if (levelText[0].getPosition().y > 500 - (levelSelection * 60)) levelText[0].move(0, -4);
				if (_loadSettings._levelVector.size() > 1){
					for (unsigned int i = 1; i < levelText.size(); i++){
						levelText[i].setPosition(levelText[0].getPosition().x, levelText[0].getPosition().y + (60 * i));

						if (i == levelSelection) levelText[i].setColor(sf::Color::White);
						else levelText[i].setColor(sf::Color::Color(255, 255, 255, 128));
					}
				}
				if (levelSelection != 0) levelText[0].setColor(sf::Color::Color(255, 255, 255, 128));
				else levelText[0].setColor(sf::Color::White);
			}

			else{
				subSelectionMax = _loadSettings._campaignVector.size() - 1;

				_loadSettings._campaign = subSelectionState;

				confirmButton[CON_BACK].setPosition(600, 505);

				if (campaignText[0].getPosition().y < 500 - (subSelectionState * 60)) campaignText[0].move(0, 4);
				else if (campaignText[0].getPosition().y > 500 - (subSelectionState * 60)) campaignText[0].move(0, -4);
				for (unsigned int i = 1; i < campaignText.size(); i++){
					campaignText[i].setPosition(campaignText[0].getPosition().x, campaignText[0].getPosition().y + (60 * i));

					if (i == subSelectionState) campaignText[i].setColor(sf::Color::White);
					else campaignText[i].setColor(sf::Color::Color(255, 255, 255, 128));
				}
				if (subSelectionState != 0) campaignText[0].setColor(sf::Color::Color(255, 255, 255, 128));
				else campaignText[0].setColor(sf::Color::White);
			}

			break;
			}
		case BUT_INFO:
			{
			subSelectionMax = 2;

			confirmButton[CON_BACK].setPosition(600, 568);

			infoShape.setTexture(&infoTexture[subSelectionState]);

			break;
			}
		case BUT_SETTINGS:
			{
			subSelectionMax = settingButton.size() - 1;

			for (unsigned int i = 0; i < settingButton.size(); i++){
				if (settingButton[i].isOver() && !lockMouse) subSelectionState = i;
					settingButton[i].update(i == subSelectionState);
			}

			confirmButton[CON_APPLY].setPosition(600, 500);
			confirmButton[CON_BACK].setPosition(600, confirmButton[CON_APPLY].getPosition().y + 100);

			settingText[SET_RESOLUTION].setString(ns::getString(_engineSettings.resolution.x) + " x " + ns::getString(_engineSettings.resolution.y));
			if (_engineSettings.vSync) settingText[SET_VSYNC].setString("Enabled");
			else settingText[SET_VSYNC].setString("Disabled");
			if (_engineSettings.fullScreen) settingText[SET_FULLSCREEN].setString("Enabled");
			else settingText[SET_FULLSCREEN].setString("Disabled");
			settingText[SET_AA].setString(ns::getString((int)_engineSettings.antiAliasing));
			if (_engineSettings.smoothTextures) settingText[SET_SMOOTH].setString("Enabled");
			else settingText[SET_SMOOTH].setString("Disabled");
			settingText[SET_GVOLUME].setString(ns::getString(_engineSettings.globalVolume));
			settingText[SET_MVOLUME].setString(ns::getString(_engineSettings.musicVolume));
			settingText[SET_SVOLUME].setString(ns::getString(_engineSettings.soundVolume));
			settingText[SET_AVOLUME].setString(ns::getString(_engineSettings.anbientVolume));

			break;
			}
		case BUT_CREDITS:
			{
			confirmButton[CON_BACK].setPosition(600, 505);

			if (creditsText[1].getPosition().y + creditsText[1].getGlobalBounds().height > 0){
				creditsText[0].move(0, -1.5);
				creditsText[1].setPosition(creditsText[0].getPosition().x, creditsText[0].getPosition().y + 150);
			}
			else{
				menuState = 0;
				subSelectionState = 0;
				subSelectionMax = 0;
			}
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
		case BUT_LEVEL: //Campaign
			{
			if (levelMenuSelected){
				selectionShape.setPosition(1160, 535);
			}
			else{
				selectionShape.setPosition(760, 535);
			}

			arrowButton[ARR_UP].setPosition(selectionShape.getPosition().x, selectionShape.getPosition().y - 50);
			arrowButton[ARR_DOWN].setPosition(selectionShape.getPosition().x, selectionShape.getPosition().y + 50);

			break;
			}
		case BUT_INFO:
			{
			arrowButton[ARR_UP].setPosition(800, 580);
			arrowButton[ARR_DOWN].setPosition(800, 620);
			break;
			}
		case BUT_SETTINGS: //Settings
			{
			selectionShape.setPosition(settingButton[subSelectionState].getPosition().x - 90, settingButton[subSelectionState].getPosition().y + (settingButton[subSelectionState].getGlobalBounds().height / 2));

			arrowButton[ARR_LEFT].setPosition(selectionShape.getPosition().x - 50, selectionShape.getPosition().y);
			arrowButton[ARR_RIGHT].setPosition(selectionShape.getPosition().x + 50, selectionShape.getPosition().y);
			
			break;

			}
		default: //Main menu
			selectionShape.setPosition(mainButton[selectionState].getPosition().x - 25, mainButton[selectionState].getPosition().y + (mainButton[selectionState].getGlobalBounds().height / 2));
	}
	

	if (menuState <= 0 && titleBackground.getFillColor().a < 254)
		titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, titleBackground.getFillColor().a + 2));
	else if (menuState > 0 && titleBackground.getFillColor().a > titleMinAlpha)
		titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, titleBackground.getFillColor().a - 6));
	
	for (unsigned int i = 0; i < mainButton.size(); i++){
		mainButton[i].setFillColor(sf::Color::Color(mainButton[i].getFillColor().r, mainButton[i].getFillColor().g, mainButton[i].getFillColor().b, titleBackground.getFillColor().a));
	}

	//Volume updates
	if ((titleMusic.getPlayingOffset().asMilliseconds() > titleMusic.getDuration().asMilliseconds() - 5000 && titleMusic.getVolume() > 1) || titleMusic.getVolume() > _engineSettings.musicVolume)
		titleMusic.setVolume(titleMusic.getVolume() - 0.5f);
	else if (titleMusic.getPlayingOffset().asMilliseconds() < titleMusic.getDuration().asMilliseconds() && titleMusic.getVolume() < _engineSettings.musicVolume)
		titleMusic.setVolume(titleMusic.getVolume() + 0.5f);


	if (menuState > 0){
		confirmButton[CON_APPLY].update(confirmButton[CON_APPLY].isOver());
		confirmButton[CON_BACK].update(confirmButton[CON_BACK].isOver());
		for (int i = 0; i < 4; i++)
			arrowButton[i].update(arrowButton[i].isOver());

		//In sub menu
		if (arrowButton[ARR_UP].isPressed()){
			if (levelMenuSelected && levelSelection > 0)
				levelSelection--;
			else if (!levelMenuSelected && subSelectionState > 0){
				subSelectionState--;
				
			if (menuState == BUT_LEVEL){
				levelSelection = 0;
					_loadSettings._campaign = subSelectionState;
					_loadSettings.loadLevels();
					initLevels();
				}
			}
		}
		else if (arrowButton[ARR_DOWN].isPressed() && subSelectionState < subSelectionMax){
			if (levelMenuSelected && levelSelection < _loadSettings._levelVector.size() - 1)
				levelSelection++;
			else if (!levelMenuSelected && subSelectionState < subSelectionMax){
				subSelectionState++;

				if (menuState == BUT_LEVEL){
					levelMenuSelected = false;
					levelSelection = 0;
					_loadSettings._campaign = subSelectionState;
					_loadSettings.loadLevels();
					initLevels();
				}
			}
		}

		if (menuState == BUT_SETTINGS){
			if (subSelectionState == SET_RESOLUTION){
				if (arrowButton[ARR_LEFT].isPressed() && (sf::VideoMode::getFullscreenModes().size() / 3) - 1 > _engineSettings.resVectorNumber){
					if (_engineSettings.usingCustomRes()){
						_engineSettings.resVectorNumber = sf::VideoMode::getFullscreenModes().size() / 3 - 1;
						_engineSettings.updateResolution();
					}
					else{
						_engineSettings.resVectorNumber++;
						_engineSettings.updateResolution();
					}
				}
				else if (arrowButton[ARR_RIGHT].isPressed() && _engineSettings.resVectorNumber > 0){
					if (_engineSettings.usingCustomRes()){
						_engineSettings.resVectorNumber = sf::VideoMode::getFullscreenModes().size() / 3 - 1;
						_engineSettings.updateResolution();
					}
					else{
					_engineSettings.resVectorNumber--;
					_engineSettings.updateResolution();
					}
				}
			}
			else if (subSelectionState == SET_VSYNC){
				if (arrowButton[ARR_LEFT].isPressed() || arrowButton[ARR_RIGHT].isPressed()){
					_engineSettings.vSync = !_engineSettings.vSync;
				}
			}
			else if (subSelectionState == SET_FULLSCREEN){
				if (arrowButton[ARR_LEFT].isPressed() || arrowButton[ARR_RIGHT].isPressed()){
					_engineSettings.fullScreen = !_engineSettings.fullScreen;
				}
			}
			else if (subSelectionState == SET_AA){
				if (arrowButton[ARR_LEFT].isPressed() && _engineSettings.antiAliasing > 0){
					_engineSettings.antiAliasing -= 2;
			}
				else if (arrowButton[ARR_RIGHT].isPressed() && _engineSettings.antiAliasing < 8){
					_engineSettings.antiAliasing += 2;
				}
			}
			else if (subSelectionState == SET_SMOOTH){
				if (arrowButton[ARR_LEFT].isPressed() || arrowButton[ARR_RIGHT].isPressed()){
					_engineSettings.smoothTextures = !_engineSettings.smoothTextures;
				}
			}
			else if (subSelectionState == SET_GVOLUME){
				if (arrowButton[ARR_LEFT].isPressed() && _engineSettings.globalVolume > 0){
					_engineSettings.globalVolume--;
				}
				else if (arrowButton[ARR_RIGHT].isPressed() && _engineSettings.globalVolume < 100){
					_engineSettings.globalVolume++;
				}
			}
			else if (subSelectionState == SET_MVOLUME){
				if (arrowButton[ARR_LEFT].isPressed() && _engineSettings.musicVolume > 0){
					_engineSettings.musicVolume--;
				}
				else if (arrowButton[ARR_RIGHT].isPressed() && _engineSettings.musicVolume < 100){
					_engineSettings.musicVolume++;
				}
			}
			else if (subSelectionState == SET_SVOLUME){
				if (arrowButton[ARR_LEFT].isPressed() && _engineSettings.soundVolume > 0){
					_engineSettings.soundVolume--;
				}
				else if (arrowButton[ARR_RIGHT].isPressed() && _engineSettings.soundVolume < 100){
					_engineSettings.soundVolume++;
				}
			}
			else if (subSelectionState == SET_AVOLUME){
				if (arrowButton[ARR_LEFT].isPressed() && _engineSettings.anbientVolume > 0){
					_engineSettings.anbientVolume--;
				}
				else if (arrowButton[ARR_RIGHT].isPressed() && _engineSettings.anbientVolume < 100){
					_engineSettings.anbientVolume++;
				}
			}
		}

		if (confirmButton[CON_BACK].isPressed()){
			menuState = 0;
			subSelectionState = 0;
			subSelectionMax = 0;
			levelMenuSelected = false;
			_engineSettings.loadFromFile();
		}
		else if (confirmButton[CON_APPLY].isPressed() && menuState == BUT_SETTINGS && confirmButton[CON_APPLY].isOver()){
			restartVideo();
		}
	}


	//Events
	while (_window->pollEvent(*_e)){

		//In main menu
		if (_e->type == sf::Event::KeyPressed && menuState <= 0){
			if (_e->key.code == sf::Keyboard::Up && selectionState > 0){
				selectionState--;
				lockMouse = true;
			}
			else if (_e->key.code == sf::Keyboard::Down && selectionState < BUT_LAST - 1){
				selectionState++;
				lockMouse = true;
			}
			else if (_e->key.code == sf::Keyboard::Escape){
				exitState = true;
			}
		}

		else if (_e->type == sf::Event::KeyReleased){
			if (_e->key.code == sf::Keyboard::Return) ns::endOfLevelState = false;
		}

		//In sub menu
		else if (_e->type == sf::Event::KeyPressed && menuState > 0){
			if (_e->key.code == sf::Keyboard::Up){
				if (levelMenuSelected && levelSelection > 0)
					levelSelection--;
				else if (!levelMenuSelected && subSelectionState > 0){
					subSelectionState--;

					if (menuState == BUT_LEVEL){
						levelSelection = 0;
						_loadSettings._campaign = subSelectionState;
						_loadSettings.loadLevels();
						initLevels();
					}
				}
				lockMouse = true;
			}
			else if (_e->key.code == sf::Keyboard::Down && subSelectionState < subSelectionMax){
				if (levelMenuSelected && levelSelection < _loadSettings._levelVector.size() - 1)
					levelSelection++;
				else if (!levelMenuSelected && subSelectionState < subSelectionMax){
					subSelectionState++;

					if (menuState == BUT_LEVEL){
						levelMenuSelected = false;
						levelSelection = 0;
						_loadSettings._campaign = subSelectionState;
						_loadSettings.loadLevels();
						initLevels();
					}
				}
				lockMouse = true;
			}
			else if (_e->key.code == sf::Keyboard::Escape){
				menuState = 0;
				subSelectionState = 0;
				subSelectionMax = 0;
				levelMenuSelected = false;
				_engineSettings.loadFromFile();
			}

			//Levels menu
			if (menuState == BUT_LEVEL){
				if (_e->key.code == sf::Keyboard::Left || _e->key.code == sf::Keyboard::Right)
					levelMenuSelected = !levelMenuSelected;
			}

			//Settings menu
			else if (menuState == BUT_SETTINGS){
				if (subSelectionState == SET_RESOLUTION){
					if ((_e->key.code == sf::Keyboard::Left || _e->key.code == sf::Keyboard::Right) && _engineSettings.usingCustomRes()){
						_engineSettings.resVectorNumber = sf::VideoMode::getFullscreenModes().size() / 3 - 1;
						_engineSettings.updateResolution();
					}
					else if (_e->key.code == sf::Keyboard::Left && (sf::VideoMode::getFullscreenModes().size() / 3) - 1 > _engineSettings.resVectorNumber){
						_engineSettings.resVectorNumber++;
						_engineSettings.updateResolution();
					}
					else if (_e->key.code == sf::Keyboard::Right && _engineSettings.resVectorNumber > 0){
						_engineSettings.resVectorNumber--;
						_engineSettings.updateResolution();
					}
				}
				else if (subSelectionState == SET_VSYNC){
					if (_e->key.code == sf::Keyboard::Left || _e->key.code == sf::Keyboard::Right){
						_engineSettings.vSync = !_engineSettings.vSync;
					}
				}
				else if (subSelectionState == SET_FULLSCREEN){
					if (_e->key.code == sf::Keyboard::Left || _e->key.code == sf::Keyboard::Right){
						_engineSettings.fullScreen = !_engineSettings.fullScreen;
					}
				}
				else if (subSelectionState == SET_AA){
					if (_e->key.code == sf::Keyboard::Left && _engineSettings.antiAliasing > 0){
						_engineSettings.antiAliasing -= 2;
					}
					else if (_e->key.code == sf::Keyboard::Right && _engineSettings.antiAliasing < 8){
						_engineSettings.antiAliasing += 2;
					}
				}
				else if (subSelectionState == SET_SMOOTH){
					if (_e->key.code == sf::Keyboard::Left || _e->key.code == sf::Keyboard::Right){
						_engineSettings.smoothTextures = !_engineSettings.smoothTextures;
					}
				}
				else if (subSelectionState == SET_GVOLUME){
					if (_e->key.code == sf::Keyboard::Left && _engineSettings.globalVolume > 0){
						_engineSettings.globalVolume--;
					}
					else if (_e->key.code == sf::Keyboard::Right && _engineSettings.globalVolume < 100){
						_engineSettings.globalVolume++;
					}
				}
				else if (subSelectionState == SET_MVOLUME){
					if (_e->key.code == sf::Keyboard::Left && _engineSettings.musicVolume > 0){
						_engineSettings.musicVolume--;
					}
					else if (_e->key.code == sf::Keyboard::Right && _engineSettings.musicVolume < 100){
						_engineSettings.musicVolume++;
					}
				}
				else if (subSelectionState == SET_SVOLUME){
					if (_e->key.code == sf::Keyboard::Left && _engineSettings.soundVolume > 0){
						_engineSettings.soundVolume--;
					}
					else if (_e->key.code == sf::Keyboard::Right && _engineSettings.soundVolume < 100){
						_engineSettings.soundVolume++;
					}
				}
				else if (subSelectionState == SET_AVOLUME){
					if (_e->key.code == sf::Keyboard::Left && _engineSettings.anbientVolume > 0){
						_engineSettings.anbientVolume--;
					}
					else if (_e->key.code == sf::Keyboard::Right && _engineSettings.anbientVolume < 100){
						_engineSettings.anbientVolume++;
					}
				}


				if (_e->key.code == sf::Keyboard::Return){
					restartVideo();
				}
			}
		}

		//Mouse events
		if (_e->type == sf::Event::MouseMoved) lockMouse = false;
	}
}

void Mainmenu::draw()
{
	_window->clear();

	_window->draw(titleBackground);

	switch (menuState)
	{
		case BUT_LEVEL:
			{
			for (unsigned int i = 0; i < campaignText.size(); i++)
				_window->draw(campaignText[i]);

			for (unsigned int i = 0; i < levelText.size(); i++)
				_window->draw(levelText[i]);

			_window->draw(confirmButton[CON_BACK]);
			_window->draw(confirmButton[CON_BACK]._text);
			_window->draw(levelMenuText);
			_window->draw(arrowButton[ARR_UP]);
			_window->draw(arrowButton[ARR_DOWN]);
			break;
			}
		case BUT_INFO:
			{
			_window->draw(infoShape);
			_window->draw(confirmButton[CON_BACK]);
			_window->draw(confirmButton[CON_BACK]._text);
			_window->draw(arrowButton[ARR_UP]);
			_window->draw(arrowButton[ARR_DOWN]);
			break;
			}
		case BUT_SETTINGS:
			{
			for (unsigned int i = 0; i < settingButton.size(); i++){
				_window->draw(settingButton[i]);
				_window->draw(settingButton[i]._text);
				_window->draw(settingText[i]);
			}
			_window->draw(confirmButton[CON_APPLY]);
			_window->draw(confirmButton[CON_APPLY]._text);
			_window->draw(confirmButton[CON_BACK]);
			_window->draw(confirmButton[CON_BACK]._text);
			_window->draw(arrowButton[ARR_LEFT]);
			_window->draw(arrowButton[ARR_RIGHT]);
			break;
			}
		case BUT_CREDITS:
			{
			_window->draw(creditsText[0]);
			_window->draw(creditsText[1]);

			_window->draw(confirmButton[CON_BACK]);
			_window->draw(confirmButton[CON_BACK]._text);
			break;
			}
	}

	for (unsigned int i = 0; i < mainButton.size(); i++){
		_window->draw(mainButton[i]);
		_window->draw(mainButton[i]._text);
	}

	if (menuState != BUT_CREDITS) _window->draw(selectionShape);

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
	levelText[0].setPosition(1200, 500 - (levelSelection * 60));

	for (unsigned int i = 1; i < _loadSettings._levelVector.size(); i++){
		levelText[i].setPosition(levelText[0].getPosition().x, levelText[0].getPosition().y + (60 * i));

		if (i == levelSelection) levelText[i].setColor(sf::Color::White);
		else levelText[i].setColor(sf::Color::Color(255, 255, 255, 128));
	}
	if (levelSelection != 0) levelText[0].setColor(sf::Color::Color(255, 255, 255, 128));
	else levelText[0].setColor(sf::Color::White);
}

void Mainmenu::restartVideo()
{
	_engineSettings.writeToFile();

	_window->close();
	
	if (_engineSettings.fullScreen)
		_window->create(sf::VideoMode(_engineSettings.resolution.x, _engineSettings.resolution.y), "Template title :(", sf::Style::Fullscreen, sf::ContextSettings(0, 0, _engineSettings.antiAliasing, 2, 0));
	else
		_window->create(sf::VideoMode(_engineSettings.resolution.x, _engineSettings.resolution.y), "Template title :(", sf::Style::Default, sf::ContextSettings(0, 0, _engineSettings.antiAliasing, 2, 0));
						
	_window->setVerticalSyncEnabled(_engineSettings.vSync);
	sf::View view;
	view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
	view.setSize(sf::Vector2f(1920, 1200));
	_window->setView(view);
}