#pragma once

#include "DebugConsole.h"

namespace ns
{
	//Update timer value in seconds
	static const float g_updateTimerValue = 1.f / 60.f;

	//Pixels2Metric & vice-versa. Needed to make B2D and SFML work together.
	//When converting from SFML units(pixels) to B2D meters, divide by this value.
	//When converting from B2D units to SFML, multiply by this value.
	static const float g_P2MScale = 60.f;

	//Resource directory strings for quick access
	//Fonts
	#define RES_FONTS "Resources/Common/Fonts/"

	extern bool runningState;
	extern bool deathState;
	extern bool endOfLevelState;
	extern float spawnPoint;

	extern unsigned int soundState;

	extern float cameraSpeed;

	extern DebugConsole* debug;
}

static const enum
{
	MAINFIX_P1 = 0x22,
	MAINFIX_P2
};

static const enum
{
	TRIG_LETHAL = 90,
	TRIG_CHECKPOINT,
	TRIG_ENDOFLEVEL
};

static const enum // Filter data
{
	//Top level
	FIL_LEVEL_TOP = 0x0001,

	FIL_PLAYERBOTTOM_TOP = 0x0002,
	FIL_PLAYERTOP_TOP = 0x0004,

	FIL_TRIGGERS_TOP = 0x0008,
	FIL_PLAYERMAINFIX_TOP = 0x0010,

	//Bottom level
	FIL_LEVEL_BOTTOM = 0x0100,

	FIL_PLAYERBOTTOM_BOTTOM = 0x0200,
	FIL_PLAYERTOP_BOTTOM = 0x0400,

	FIL_TRIGGERS_BOTTOM = 0x0800,
	FIL_PLAYERMAINFIX_BOTTOM = 0x1000,

	FIL_NULL = 0x0000
};

static const enum  // Resource types
{
	RT_ANIMATION,
	RT_SOUND
};

static const enum //Sound types
{
	ST_SOUND,
	ST_MUSIC,
	ST_ANBIENT
};