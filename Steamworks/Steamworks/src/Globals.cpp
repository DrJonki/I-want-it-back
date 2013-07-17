#include "Globals.h"

namespace ns
{
	bool runningState = false;
	bool exitState = false;
	bool deathState = false;
	bool endOfLevelState = false;
	float spawnPoint = 1000.f;

	unsigned int soundState = 0;

	float cameraSpeed = 0.f;

	DebugConsole* debug = nullptr;
}