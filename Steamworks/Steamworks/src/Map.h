#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>

#include "MapObject.h"
#include "BackgroundObject.h"
#include "ForegroundObject.h"
#include "EngineSettings.h"
#include "Trigger.h"

class Map
{
public:
	Map(void);
	~Map(void);


	/// Base function for loading the map information.
	/// @param a pointer to the main world object.
	/// @param a pointer to the main window object.
	/// @param name of the campaign to load.
	/// @param name of the level to load.
	void load(b2World* world,
			  sf::RenderWindow* window,
			  std::string campaign,
			  std::string level,
			  EngineSettings& esettings);
	
	/// Updates the animation states
	void update();

	/// Draws all the objects in the map.
	void draw();
	void drawForeground();

private:

	/// A local function to load the data from backgrounds.dat and generate the backgrounds.
	void createBackgrounds();


	/// A local function to load the data from statics.dat and generate the static physical objects.
	void createStatics();


	/// A local function to load the data from foreground.dat and generate the foreground objects.
	void createForeground();


	/// A local function to load the data from triggers.dat and generate the triggers.
	void createTriggers();


	/// A container for the background objects.
	std::vector<BackgroundObject> _backGroundObject;

	/// A container for the static physical objects.
	std::vector<MapObject> _mapObject;

	/// A container for the foreground objects.
	std::vector<ForegroundObject> _foregroundObject;

	// A container for the trigger objects.
	std::vector<Trigger> _triggerObject;

	/// A local pointer to the main window.
	sf::RenderWindow* _window;

	/// A local pointer to the main world.
	b2World* _world;

	/// Locally stored name of the currently loaded campaign.
	std::string _campaign;

	/// Locally stored name of the currently loaded level.
	std::string _level;
};