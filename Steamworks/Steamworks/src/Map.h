#pragma once

#include "ContactListener.h"
#include "LoadSettings.h"
#include "EngineSettings.h"
#include "MapObject.h"
#include "ForegroundObject.h"
#include "BackgroundObject.h"
#include "Trigger.h"
#include "SoundManager.h"

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
			  ContactListener* listener,
			  sf::RenderWindow* window,
			  LoadSettings& lsettigns,
			  EngineSettings& esettings);

	void resetMapStates();
	
	/// Updates the animation states & triggers
	void update();

	/// Draws all the objects in the map.
	void draw();
	void drawForeground();

private:

	/// A local variable for debug mode
	bool _debug;

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

	/// A sound manager for both levels
	SoundManager sManager;

	/// A local pointer to the main window.
	sf::RenderWindow* _window;

	/// A local pointer to the main world.
	b2World* _world;

	/// A local pointer to the contact listener.
	ContactListener* _cListener;

	/// Locally stored name of the currently loaded campaign.
	std::string _campaign;

	/// Locally stored name of the currently loaded level.
	std::string _level;

	
	EngineSettings* _esettings;
};