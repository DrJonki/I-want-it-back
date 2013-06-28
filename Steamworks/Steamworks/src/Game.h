#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include <Windows.h>

#include "Globals.h"
#include "DebugConsole.h"
#include "Mainmenu.h"
#include "Pausemenu.h"
#include "WorldManager.h"
#include "Player.h"

class Game
{
public:
	Game(void);
	~Game(void);
	
	bool runAndDontCrashPls();

private:

	void update();
	void render();
	void pollEvents();
	void init();
	void deInit();
};