#include "Pausemenu.h"


namespace
{
	int selectionState = 0;
	int subSelectionState = 0;
	int subSelectionMax = 0;
	int menuState = 0;

	bool lockMouse = true;
	
	bool continueState = false;
}


Pausemenu::Pausemenu(sf::RenderWindow* window, sf::Event* e, EngineSettings& esettings)
	: _window(window),
	  _e(e)
{
	_engineSettings = esettings;

	init();

	resetViews();
}


Pausemenu::~Pausemenu(void)
{}


bool Pausemenu::showMenu(bool paused)
{
	if (paused){
		if (pauseBackground.getFillColor().a < 200)
			pauseBackground.setFillColor(sf::Color::Color(0, 0, 0, pauseBackground.getFillColor().a + 6));

		if (mainButton[BUT_START].isPressed() || continueState){
			menuState = BUT_START;
			return true;
		}
		else if (mainButton[BUT_SETTINGS].isPressed() && menuState == 0){
			menuState = BUT_SETTINGS;
		}
		else if (((mainButton[BUT_EXIT].isPressed()) && menuState == 0)){
			ns::runningState = false;
		}
		else if (mainButton[BUT_EXITTOWIN].isPressed() && menuState == 0){
			ns::runningState = false;
			ns::exitState = true;
		}
		update();
	}
	else{
		selectionState = 0;
		subSelectionState = 0;
		subSelectionMax = 0;
		menuState = 0;

		lockMouse = true;

		continueState = false;

		if (pauseBackground.getFillColor().a >= 6)
			pauseBackground.setFillColor(sf::Color::Color(0, 0, 0, pauseBackground.getFillColor().a - 6));
	}

	for (unsigned int i = 0; i < mainButton.size(); i++){
		if (pauseBackground.getFillColor().a < 128)
			mainButton[i].setFillColor(sf::Color::Color(mainButton[i].getFillColor().r, mainButton[i].getFillColor().g, mainButton[i].getFillColor().b, pauseBackground.getFillColor().a * 2));
		else
			mainButton[i].setFillColor(sf::Color::Color(mainButton[i].getFillColor().r, mainButton[i].getFillColor().g, mainButton[i].getFillColor().b, 255));
	}
	if (pauseBackground.getFillColor().a < 128)
		selectionShape.setFillColor(sf::Color::Color(selectionShape.getFillColor().r, selectionShape.getFillColor().g, selectionShape.getFillColor().b, pauseBackground.getFillColor().a * 2));
	else
		selectionShape.setFillColor(sf::Color::Color(selectionShape.getFillColor().r, selectionShape.getFillColor().g, selectionShape.getFillColor().b, 255));

	return false;
}

void Pausemenu::update()
{
	switch (menuState)
	{
		case BUT_SETTINGS:
			{
			subSelectionMax = settingButton.size() - 1;

			for (unsigned int i = 0; i < settingButton.size(); i++){
				if (settingButton[i].isOver() && !lockMouse) subSelectionState = i;
					settingButton[i].update(i == subSelectionState);
			}

			confirmButton[CON_APPLY].setPosition(600, 500);
			confirmButton[CON_BACK].setPosition(600, confirmButton[CON_APPLY].getPosition().y + 100);

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
		case BUT_SETTINGS: //Settings
			selectionShape.setPosition(settingButton[subSelectionState].getPosition().x - 25, settingButton[subSelectionState].getPosition().y + (settingButton[subSelectionState].getGlobalBounds().height / 2));
			break;
		default: //Main menu
			selectionShape.setPosition(mainButton[selectionState].getPosition().x - 25, mainButton[selectionState].getPosition().y + (mainButton[selectionState].getGlobalBounds().height / 2));
	}


	if (menuState > 0){
		confirmButton[CON_APPLY].update(confirmButton[CON_APPLY].isOver());
		confirmButton[CON_BACK].update(confirmButton[CON_BACK].isOver());

		if (confirmButton[CON_BACK].isPressed()){
			menuState = 0;
			subSelectionState = 0;
			subSelectionMax = 0;
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
				continueState = true;
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
					restartVideo();
				}
			}
		}

		//Mouse events
		if (_e->type == sf::Event::MouseMoved) lockMouse = false;
	}
}

void Pausemenu::draw()
{
	if (pauseBackground.getFillColor().a > 6){
		pauseView.setCenter(sf::Vector2f(1920 / 2, 1200 / 2));
		pauseView.setSize(sf::Vector2f(1920, 1200));
		_window->setView(pauseView);

		_window->draw(pauseBackground);

		switch (menuState)
		{
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
				break;
				}
		}

		for (unsigned int i = 0; i < mainButton.size(); i++){
			_window->draw(mainButton[i]);
			_window->draw(mainButton[i]._text);
		}

		_window->draw(selectionShape);
	}
}

void Pausemenu::init()
{
	mainButton.clear();
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
	mainButton[BUT_START]._text.setString("Continue");
	mainButton[BUT_START]._text.setColor(sf::Color::Black);
	//Settings
	mainButton[BUT_SETTINGS].load(200, 100, mainButton[BUT_START].getPosition().x, mainButton[BUT_START].getPosition().y + 200, image);
	mainButton[BUT_SETTINGS]._text.setFont(_font);
	mainButton[BUT_SETTINGS]._text.setCharacterSize(30);
	mainButton[BUT_SETTINGS]._text.setString("Settings");
	mainButton[BUT_SETTINGS]._text.setColor(sf::Color::Black);
	//Exit
	mainButton[BUT_EXIT].load(250, 75, mainButton[BUT_START].getPosition().x, mainButton[BUT_SETTINGS].getPosition().y + 200, image);
	mainButton[BUT_EXIT]._text.setFont(_font);
	mainButton[BUT_EXIT]._text.setCharacterSize(26);
	mainButton[BUT_EXIT]._text.setString("Exit to menu");
	mainButton[BUT_EXIT]._text.setColor(sf::Color::Black);
	//Exit to Windows
	mainButton[BUT_EXITTOWIN].load(250, 75, mainButton[BUT_START].getPosition().x, mainButton[BUT_EXIT].getPosition().y + 100, image);
	mainButton[BUT_EXITTOWIN]._text.setFont(_font);
	mainButton[BUT_EXITTOWIN]._text.setCharacterSize(26);
	mainButton[BUT_EXITTOWIN]._text.setString("Exit game");
	mainButton[BUT_EXITTOWIN]._text.setColor(sf::Color::Black);


	//Confirmation buttons
	confirmButton.emplace_back(GameButton(_window));
	confirmButton.emplace_back(GameButton(_window));

	confirmButton[CON_APPLY].load(100, 65, 600, 500, image);
	confirmButton[CON_APPLY]._text.setFont(_font);
	confirmButton[CON_APPLY]._text.setCharacterSize(22);
	confirmButton[CON_APPLY]._text.setString("Apply >>");
	confirmButton[CON_APPLY]._text.setColor(sf::Color::Black);

	confirmButton[CON_BACK].load(100, 65, confirmButton[CON_APPLY].getPosition().x, confirmButton[CON_APPLY].getPosition().y + 100, image);
	confirmButton[CON_BACK]._text.setFont(_font);
	confirmButton[CON_BACK]._text.setCharacterSize(24);
	confirmButton[CON_BACK]._text.setString("<< Back");
	confirmButton[CON_BACK]._text.setColor(sf::Color::Black);

	//Sub menu buttons
	/////////////////////////////////////////////////////////
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
	settingButton[SET_RESOLUTION]._text.setColor(sf::Color::Black);

	settingText[SET_RESOLUTION].setFont(_font);
	settingText[SET_RESOLUTION].setCharacterSize(30);
	settingText[SET_RESOLUTION].setString(_engineSettings.getResolutionString());
	settingText[SET_RESOLUTION].setColor(sf::Color::White);
	settingText[SET_RESOLUTION].setOrigin(0, settingText[SET_RESOLUTION].getGlobalBounds().height / 2);
	settingText[SET_RESOLUTION].setPosition(settingButton[SET_RESOLUTION].getPosition().x + settingButton[SET_RESOLUTION].getSize().x + 25, settingButton[SET_RESOLUTION].getPosition().y + (settingButton[SET_RESOLUTION].getSize().y / 3));
	//Vsync
	settingButton[SET_VSYNC].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_RESOLUTION].getPosition().y + 100, image);
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
	settingButton[SET_FULLSCREEN].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_VSYNC].getPosition().y + 75, image);
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
	settingButton[SET_AA].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_FULLSCREEN].getPosition().y + 75, image);
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
	settingButton[SET_SMOOTH].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_AA].getPosition().y + 75, image);
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
	settingButton[SET_GVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_SMOOTH].getPosition().y + 100, image);
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
	settingButton[SET_MVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_GVOLUME].getPosition().y + 75, image);
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
	settingButton[SET_SVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_MVOLUME].getPosition().y + 75, image);
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
	settingButton[SET_AVOLUME].load(200, 50, settingButton[SET_RESOLUTION].getPosition().x, settingButton[SET_SVOLUME].getPosition().y + 75, image);
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


	//Other
	selectionShape.setRadius(5);
	selectionShape.setFillColor(sf::Color::Red);
	selectionShape.setOutlineThickness(2);
	selectionShape.setOutlineColor(sf::Color::White);
	selectionShape.setOrigin(selectionShape.getRadius(), selectionShape.getRadius());
	selectionShape.setPosition(mainButton[BUT_START].getPosition().x - 25, mainButton[BUT_START].getPosition().y + (mainButton[BUT_START].getGlobalBounds().height / 2));


	pauseBackground.setSize(sf::Vector2f(1920, 1200));
	pauseBackground.setFillColor(sf::Color::Color(0, 0, 0, 0));
	pauseBackground.setPosition(0, 0);
}

void Pausemenu::restartVideo()
{
	_engineSettings.writeToFile();

	_window->close();
	
	if (_engineSettings.fullScreen)
		_window->create(sf::VideoMode(_engineSettings.resolution.x, _engineSettings.resolution.y), "Template title :(", sf::Style::Fullscreen, sf::ContextSettings(0, 0, _engineSettings.antiAliasing, 2, 0));
	else
		_window->create(sf::VideoMode(_engineSettings.resolution.x, _engineSettings.resolution.y), "Template title :(", sf::Style::Default, sf::ContextSettings(0, 0, _engineSettings.antiAliasing, 2, 0));
						
	_window->setVerticalSyncEnabled(_engineSettings.vSync);

	resetViews();
}

void Pausemenu::resetViews()
{
	float s_scale = ((float)_engineSettings.resolution.x / (float)_engineSettings.resolution.y) / (1920.f / 1200.f);
	//Top view
	_view[0].setCenter(sf::Vector2f((1920 * s_scale) / 2, 300));
	_view[0].setSize(sf::Vector2f(1920 * s_scale, 600));
	_view[0].setViewport(sf::FloatRect(0, 0, 1.f, 0.5f));

	//Bottom view
	_view[1].setCenter(sf::Vector2f((1920 * s_scale) / 2, 900));
	_view[1].setSize(sf::Vector2f(1920 * s_scale, 600));
	_view[1].setViewport(sf::FloatRect(0, 0.5f, 1.f, 0.5f));

	//Whole view
	_view[2].setCenter(sf::Vector2f(_engineSettings.resolution.x / 2, _engineSettings.resolution.y / 2));
	_view[2].setSize(sf::Vector2f((float)_engineSettings.resolution.x, (float)_engineSettings.resolution.y));
	_view[2].setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
}

sf::View& Pausemenu::getView(const unsigned short view)
{
	return _view[view];
}