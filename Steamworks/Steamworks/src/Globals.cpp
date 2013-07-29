#include "Globals.h"

namespace ns
{
	bool runningState = false;
	bool exitState = false;
	bool restartState = false;
	bool reloadState = false;
	bool deathState = false;
	bool endOfLevelState = false;
	float spawnPoint = 1100.f;
	sf::Time checkPointTime = sf::Time::Zero;
	bool dirtyRun = false;

	int soundState = 0;

	float cameraSpeed = 0.f;

	DebugConsole* debug = nullptr;

	GameStateLoader* gameStateLoader = new GameStateLoader;
}