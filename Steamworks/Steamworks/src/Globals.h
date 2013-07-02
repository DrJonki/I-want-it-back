#pragma once


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




}