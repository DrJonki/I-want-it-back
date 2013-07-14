#include "Mainmenu.h"

namespace
{
	int selectionState;
	int subSelectionState;
	int subSelectionMax;
	int menuState;

	bool lockMouse;

	bool loaded;
}

Mainmenu::Mainmenu(sf::RenderWindow* window, sf::Event* e)
	: _window(window),
	  _e(e)
{
	selectionState = 0;
	subSelectionState = 0;
	subSelectionMax = 0;
	menuState = 0;

	lockMouse = true;

	loaded = false;
}

Mainmenu::~Mainmenu(void)
{
	_window->close();
}


bool Mainmenu::showMenu()
{
	if (!loaded) init();
	sf::View view;
	view.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
	view.setSize(sf::Vector2f(1920, 1200));
	_window->setView(view);
	titleMusic.play();
	titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, 0));
	
	while (1){
		if (mainButton[BUT_START].isPressed()){
			titleMusic.stop();
			menuState = BUT_START;
			return true;
		}
		else if (mainButton[BUT_CAMPAIGN].isPressed() && menuState == 0){
			menuState = BUT_CAMPAIGN;
			subSelectionState = _loadSettings._campaign;
		}
		else if (mainButton[BUT_LEVEL].isPressed() && menuState == 0){
			menuState = BUT_LEVEL;
			_loadSettings.loadLevels();

			if (_loadSettings._levelVector.size() > _loadSettings._level) subSelectionState = _loadSettings._level;

			initLevels();
		}
		else if (mainButton[BUT_SETTINGS].isPressed() && menuState == 0){
			menuState = BUT_SETTINGS;
		}
		else if (mainButton[BUT_CREDITS].isPressed() && menuState == 0){
			menuState = BUT_CREDITS;
			creditsText[0].setPosition(1000, 1200);
			creditsText[1].setPosition(creditsText[0].getPosition().x, creditsText[0].getPosition().y + 150);
		}
		else if (mainButton[BUT_EXIT].isPressed() && menuState == 0){
			return false;
		}

		
		update();
		draw();
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
	_window->setFramerateLimit(60);
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
	settingButton.reserve(SET_LAST);
	settingText.reserve(SET_LAST);
	for (unsigned int i = 0; i < SET_LAST; i++){
		settingButton.emplace_back(GameButton(_window));
		settingText.emplace_back(sf::Text());
	}

	//Resolution
	settingButton[SET_RESOLUTION].load(250, 50, 800, 200, image);
	settingButton[SET_RESOLUTION]._text.setFont(_font);
	settingButton[SET_RESOLUTION]._text.setCharacterSize(28);
	settingButton[SET_RESOLUTION]._text.setString("Resolution");
	settingButton[SET_RESOLUTION]._text.setColor(sf::Color::Black);

	settingText[SET_RESOLUTION].setFont(_font);
	settingText[SET_RESOLUTION].setCharacterSize(30);
	settingText[SET_RESOLUTION].setString(_engineSettings.getResolutionString());
	settingText[SET_RESOLUTION].setColor(sf::Color::White);
	settingText[SET_RESOLUTION].setOrigin(0, settingText[SET_RESOLUTION].getGlobalBounds().height / 2);
	settingText[SET_RESOLUTION].setPosition(settingButton[SET_RESOLUTION].getPosition().x + settingButton[SET_RESOLUTION].getSize().x + 25, settingButton[SET_RESOLUTION].getPosition().y + (settingButton[SET_RESOLUTION].getSize().y / 3));
	//Vsync
	settingButton[SET_VSYNC].load(200, 50, 800, settingButton[SET_RESOLUTION].getPosition().y + 100, image);
	settingButton[SET_VSYNC]._text.setFont(_font);
	settingButton[SET_VSYNC]._text.setCharacterSize(28);
	settingButton[SET_VSYNC]._text.setString("V-Sync");
	settingButton[SET_VSYNC]._text.setColor(sf::Color::Black);

	settingText[SET_VSYNC].setFont(_font);
	settingText[SET_VSYNC].setCharacterSize(30);
	if (_engineSettings.vSync) settingText[SET_VSYNC].setString("Enabled");
	else settingText[SET_VSYNC].setString("Disabled");
	settingText[SET_VSYNC].setColor(sf::Color::White);
	settingText[SET_VSYNC].setOrigin(0, settingText[SET_VSYNC].getGlobalBounds().height / 2);
	settingText[SET_VSYNC].setPosition(settingButton[SET_VSYNC].getPosition().x + settingButton[SET_VSYNC].getSize().x + 25, settingButton[SET_VSYNC].getPosition().y + (settingButton[SET_VSYNC].getSize().y / 3));

	//Full screen
	settingButton[SET_FULLSCREEN].load(200, 50, 800, settingButton[SET_VSYNC].getPosition().y + 75, image);
	settingButton[SET_FULLSCREEN]._text.setFont(_font);
	settingButton[SET_FULLSCREEN]._text.setCharacterSize(28);
	settingButton[SET_FULLSCREEN]._text.setString("Fullscreen");
	settingButton[SET_FULLSCREEN]._text.setColor(sf::Color::Black);

	settingText[SET_FULLSCREEN].setFont(_font);
	settingText[SET_FULLSCREEN].setCharacterSize(30);
	if (_engineSettings.fullScreen) settingText[SET_FULLSCREEN].setString("Enabled");
	else settingText[SET_FULLSCREEN].setString("Disabled");
	settingText[SET_FULLSCREEN].setColor(sf::Color::White);
	settingText[SET_FULLSCREEN].setOrigin(0, settingText[SET_FULLSCREEN].getGlobalBounds().height / 2);
	settingText[SET_FULLSCREEN].setPosition(settingButton[SET_FULLSCREEN].getPosition().x + settingButton[SET_FULLSCREEN].getSize().x + 25, settingButton[SET_FULLSCREEN].getPosition().y + (settingButton[SET_FULLSCREEN].getSize().y / 3));

	//AA
	settingButton[SET_AA].load(200, 50, 800, settingButton[SET_FULLSCREEN].getPosition().y + 75, image);
	settingButton[SET_AA]._text.setFont(_font);
	settingButton[SET_AA]._text.setCharacterSize(28);
	settingButton[SET_AA]._text.setString("Anti-aliasing");
	settingButton[SET_AA]._text.setColor(sf::Color::Black);

	settingText[SET_AA].setFont(_font);
	settingText[SET_AA].setCharacterSize(30);
	settingText[SET_AA].setString(_engineSettings.getAAString());
	settingText[SET_AA].setColor(sf::Color::White);
	settingText[SET_AA].setOrigin(0, settingText[SET_AA].getGlobalBounds().height / 2);
	settingText[SET_AA].setPosition(settingButton[SET_AA].getPosition().x + settingButton[SET_AA].getSize().x + 25, settingButton[SET_AA].getPosition().y + (settingButton[SET_AA].getSize().y / 3));

	//Smooth
	settingButton[SET_SMOOTH].load(200, 50, 800, settingButton[SET_AA].getPosition().y + 75, image);
	settingButton[SET_SMOOTH]._text.setFont(_font);
	settingButton[SET_SMOOTH]._text.setCharacterSize(24);
	settingButton[SET_SMOOTH]._text.setString("Smooth textures");
	settingButton[SET_SMOOTH]._text.setColor(sf::Color::Black);

	settingText[SET_SMOOTH].setFont(_font);
	settingText[SET_SMOOTH].setCharacterSize(30);
	if (_engineSettings.smoothTextures) settingText[SET_SMOOTH].setString("Enabled");
	else settingText[SET_SMOOTH].setString("Disabled");
	settingText[SET_SMOOTH].setColor(sf::Color::White);
	settingText[SET_SMOOTH].setOrigin(0, settingText[SET_SMOOTH].getGlobalBounds().height / 2);
	settingText[SET_SMOOTH].setPosition(settingButton[SET_SMOOTH].getPosition().x + settingButton[SET_SMOOTH].getSize().x + 25, settingButton[SET_SMOOTH].getPosition().y + (settingButton[SET_SMOOTH].getSize().y / 3));


	//Global volume
	settingButton[SET_GVOLUME].load(200, 50, 800, settingButton[SET_SMOOTH].getPosition().y + 100, image);
	settingButton[SET_GVOLUME]._text.setFont(_font);
	settingButton[SET_GVOLUME]._text.setCharacterSize(24);
	settingButton[SET_GVOLUME]._text.setString("Global volume");
	settingButton[SET_GVOLUME]._text.setColor(sf::Color::Black);

	settingText[SET_GVOLUME].setFont(_font);
	settingText[SET_GVOLUME].setCharacterSize(30);
	settingText[SET_GVOLUME].setString(_engineSettings.getMVolumeString());
	settingText[SET_GVOLUME].setColor(sf::Color::White);
	settingText[SET_GVOLUME].setOrigin(0, settingText[SET_GVOLUME].getGlobalBounds().height / 2);
	settingText[SET_GVOLUME].setPosition(settingButton[SET_GVOLUME].getPosition().x + settingButton[SET_GVOLUME].getSize().x + 25, settingButton[SET_GVOLUME].getPosition().y + (settingButton[SET_GVOLUME].getSize().y / 3));

	//Music volume
	settingButton[SET_MVOLUME].load(200, 50, 800, settingButton[SET_GVOLUME].getPosition().y + 75, image);
	settingButton[SET_MVOLUME]._text.setFont(_font);
	settingButton[SET_MVOLUME]._text.setCharacterSize(24);
	settingButton[SET_MVOLUME]._text.setString("Music volume");
	settingButton[SET_MVOLUME]._text.setColor(sf::Color::Black);

	settingText[SET_MVOLUME].setFont(_font);
	settingText[SET_MVOLUME].setCharacterSize(30);
	settingText[SET_MVOLUME].setString(_engineSettings.getMVolumeString());
	settingText[SET_MVOLUME].setColor(sf::Color::White);
	settingText[SET_MVOLUME].setOrigin(0, settingText[SET_MVOLUME].getGlobalBounds().height / 2);
	settingText[SET_MVOLUME].setPosition(settingButton[SET_MVOLUME].getPosition().x + settingButton[SET_MVOLUME].getSize().x + 25, settingButton[SET_MVOLUME].getPosition().y + (settingButton[SET_MVOLUME].getSize().y / 3));

	//Sound volume
	settingButton[SET_SVOLUME].load(200, 50, 800, settingButton[SET_MVOLUME].getPosition().y + 75, image);
	settingButton[SET_SVOLUME]._text.setFont(_font);
	settingButton[SET_SVOLUME]._text.setCharacterSize(24);
	settingButton[SET_SVOLUME]._text.setString("Sound volume");
	settingButton[SET_SVOLUME]._text.setColor(sf::Color::Black);

	settingText[SET_SVOLUME].setFont(_font);
	settingText[SET_SVOLUME].setCharacterSize(30);
	settingText[SET_SVOLUME].setString(_engineSettings.getMVolumeString());
	settingText[SET_SVOLUME].setColor(sf::Color::White);
	settingText[SET_SVOLUME].setOrigin(0, settingText[SET_SVOLUME].getGlobalBounds().height / 2);
	settingText[SET_SVOLUME].setPosition(settingButton[SET_SVOLUME].getPosition().x + settingButton[SET_SVOLUME].getSize().x + 25, settingButton[SET_SVOLUME].getPosition().y + (settingButton[SET_SVOLUME].getSize().y / 3));

	//Anbient volume
	settingButton[SET_AVOLUME].load(200, 50, 800, settingButton[SET_SVOLUME].getPosition().y + 75, image);
	settingButton[SET_AVOLUME]._text.setFont(_font);
	settingButton[SET_AVOLUME]._text.setCharacterSize(24);
	settingButton[SET_AVOLUME]._text.setString("Anbient volume");
	settingButton[SET_AVOLUME]._text.setColor(sf::Color::Black);

	settingText[SET_AVOLUME].setFont(_font);
	settingText[SET_AVOLUME].setCharacterSize(30);
	settingText[SET_AVOLUME].setString(_engineSettings.getMVolumeString());
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

	image.loadFromFile("Resources/Common/Graphics/UI/sheet_tsuge.png");
	titleAnimation.loadSheet(image, 0, 0, 1000, 1000, 8, true);
	titleAnimation.setStepInterval(6);

	titleBackground.setSize(sf::Vector2f(1200, 1200));
	titleBackground.setTexture(&titleAnimation.getCurrentTexture());
	titleBackground.setFillColor(sf::Color::Color(titleBackground.getFillColor().r, titleBackground.getFillColor().g, titleBackground.getFillColor().b, 0));
	titleBackground.setPosition(720, 0);

	titleMusic.openFromFile("Resources/Common/Audio/Music/junakulkee.ogg");
	titleMusic.setLoop(true);
	titleMusic.setVolume(_engineSettings.musicVolume);
	titleMusic.setRelativeToListener(true);

	loaded = true;
}

void Mainmenu::update()
{
	switch (menuState)
	{
		case BUT_CAMPAIGN:
			{
			subSelectionMax = _loadSettings._campaignVector.size() - 1;

			_loadSettings._campaign = subSelectionState;

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

			_loadSettings._level = subSelectionState;

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
			subSelectionMax = settingButton.size() - 1;

			for (unsigned int i = 0; i < settingButton.size(); i++){
				if (settingButton[i].isOver() && !lockMouse) subSelectionState = i;
					settingButton[i].update(i == subSelectionState);
			}

			settingText[SET_RESOLUTION].setString(_engineSettings.getResolutionString());
			if (_engineSettings.vSync) settingText[SET_VSYNC].setString("Enabled");
			else settingText[SET_VSYNC].setString("Disabled");
			if (_engineSettings.fullScreen) settingText[SET_FULLSCREEN].setString("Enabled");
			else settingText[SET_FULLSCREEN].setString("Disabled");
			settingText[SET_AA].setString(_engineSettings.getAAString());
			if (_engineSettings.smoothTextures) settingText[SET_SMOOTH].setString("Enabled");
			else settingText[SET_SMOOTH].setString("Disabled");
			settingText[SET_GVOLUME].setString(_engineSettings.getGVolumeString());
			settingText[SET_MVOLUME].setString(_engineSettings.getMVolumeString());
			settingText[SET_SVOLUME].setString(_engineSettings.getSVolumeString());
			settingText[SET_AVOLUME].setString(_engineSettings.getAVolumeString());

			break;
			}
		case BUT_CREDITS:
			{
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
		case BUT_CAMPAIGN: //Campaign
			{
			if (campaignText.size() <= 1){
				selectionShape.setPosition(campaignText[subSelectionState].getPosition().x - 25, campaignText[subSelectionState].getPosition().y + (campaignText[subSelectionState].getLocalBounds().height / 1.5));
			}
			else{
				selectionShape.setPosition(campaignText[subSelectionState].getPosition().x - 25, campaignText[subSelectionState].getPosition().y + campaignText[subSelectionState].getLocalBounds().height);
			}
			break;
			}
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
			selectionShape.setPosition(settingButton[subSelectionState].getPosition().x - 25, settingButton[subSelectionState].getPosition().y + (settingButton[subSelectionState].getGlobalBounds().height / 2));
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
	

	//Volume updates
	titleMusic.setVolume(_engineSettings.musicVolume);


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
		}

		//In sub menu
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
				if (menuState == BUT_CAMPAIGN){
					_loadSettings.loadLevels();
				}
				menuState = 0;
				subSelectionState = 0;
				subSelectionMax = 0;
				_engineSettings.loadFromFile();
			}

			//Settings menu
			if (menuState == BUT_SETTINGS){
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
		case BUT_SETTINGS:
			{
			for (unsigned int i = 0; i < settingButton.size(); i++){
				_window->draw(settingButton[i]);
				_window->draw(settingButton[i]._text);
				_window->draw(settingText[i]);
			}
			break;
			}
		case BUT_CREDITS:
			{
			_window->draw(creditsText[0]);
			_window->draw(creditsText[1]);
			break;
			}
		default:
			_window->draw(titleBackground);
	}

	for (unsigned int i = 0; i < mainButton.size(); i++){
		_window->draw(mainButton[i]);
		_window->draw(mainButton[i]._text);
	}

	if (menuState != 0){
		//_window->draw(
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
	levelText[0].setPosition(800, 500 - (subSelectionState * 60));
}