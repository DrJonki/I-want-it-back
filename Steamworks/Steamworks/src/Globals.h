#pragma once

//Debug configuration
#ifdef _DEBUG
	static const bool g_debug = true;
#else
	static const bool g_debug = false;
#endif

//Window dimensions
static const int g_windowWidth = 800, g_windowHeight = 600;

//Vertical sync setting
static const bool g_useVSync = true;

//Update timer value in seconds
static const float g_updateTimerValue = 1.f / 60.f;

//Gravity
static const float g_worldGravity = 25.f;

//Pixels2Metric & vice-versa. Needed to make B2D and SFML work together.
//When converting from SFML units(pixels) to B2D meters, divide by this value.
//When converting from B2D units to SFML, multiply by this value.
static const float g_P2MScale = 30.f;

//Resource directory strings for quick access
//Audio
#define RES_AUDIO_SOUND_ACTOR "Resources/Audio/Sound/Actor/"
#define RES_AUDIO_SOUND_OTHER "Resources/Audio/Sound/Other/"
#define RES_AUDIO_MUSIC "Resources/Audio/Music/"

//Fonts
#define RES_FONTS "Resources/Fonts/"

//Graphics
#define RES_GRAPHICS_ACTOR "Resources/Graphics/Actor/"
#define RES_GRAPHICS_LEVEL "Resources/Graphics/Level/"
#define RES_GRAPHICS_OTHER "Resources/Graphics/Other/"

