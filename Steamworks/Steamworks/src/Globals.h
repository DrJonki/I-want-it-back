#pragma once

#include <string>

//Window dimensions
static const int g_windowWidth = 800, g_windowHeight = 600;

//Gravity
static const float g_worldGravity = 9.8f;

//Pixels2Metric & vice-versa. Needed to make B2D and SFML work together.
static const float P2MScale = 30.f;