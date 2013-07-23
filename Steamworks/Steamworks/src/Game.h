#pragma once

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
	void resetStates();
};