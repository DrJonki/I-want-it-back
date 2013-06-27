#pragma once

//Debug configuration
//#ifdef _DEBUG
//	static const bool g_debug = true;
//#else
	static const bool g_debug = false;
//#endif

//Window dimensions
static const int g_windowWidth = 1600, g_windowHeight = 900;

//Vertical sync setting
static const bool g_useVSync = true;

//Update timer value in seconds
static const float g_updateTimerValue = 1.f / 60.f;

//Gravity
static const float g_worldGravity = 25.f;

//Pixels2Metric & vice-versa. Needed to make B2D and SFML work together.
//When converting from SFML units(pixels) to B2D meters, divide by this value.
//When converting from B2D units to SFML, multiply by this value.
static const float g_P2MScale = 60.f;

//Resource directory strings for quick access
//Fonts
#define RES_FONTS "Resources/Common/Fonts/"

//Enumeration for the different animation states
static const enum
{
	ANIM_IDLE,
	ANIM_RUNNING,
	ANIM_JUMPING,
	ANIM_FALLING,
	ETC
};