#pragma once

#include <SFML\Graphics\RectangleShape.hpp>

#include "SpriteAnimation.h"

class ForegroundObject : public sf::RectangleShape, public SpriteAnimation
{
public:
	ForegroundObject(void);
	~ForegroundObject(void);

	void load(const float sizeX,
			  const float sizeY,
			  const float posX,
			  const float posY,
			  const std::string textureDir,
			  const bool smooth,
			  const int aSizeX = 0,
			  const int aSizeY = 0,
			  const int startX = 0,
			  const int startY = 0,
			  const unsigned int interval = 1,
			  const unsigned int frames = 1);

	void update(){
		if (getFillColor() != sf::Color::Transparent){
			if (_trigData == 0){
				stepForward();
				if (frameChanged()) setTexture(&getCurrentTexture());
			}
			else if (_trigData != 0 && _playing && (_loop || !lastFrame())){
				stepForward();
				if (frameChanged()) setTexture(&getCurrentTexture());
			}
		}
	};

	unsigned int _trigData;

	bool _loop;
	bool _playing;
};