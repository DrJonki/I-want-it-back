#include "ForegroundObject.h"


ForegroundObject::ForegroundObject(void)
	: _data(0)
{}

ForegroundObject::~ForegroundObject(void)
{}


void ForegroundObject::load(const float sizeX,
						    const float sizeY,
							const float posX,
							const float posY,
							const std::string textureDir,
							const int aSizeX,
							const int aSizeY,
							const int startX,
							const int startY,
							const unsigned int interval,
							const unsigned int frames)
{
	setSize(sf::Vector2f(sizeX, sizeY));
	setOrigin(sizeX / 2, sizeY / 2);
	setPosition(posX, posY);

	sf::Image image;
	if (image.loadFromFile(textureDir)){
		if (aSizeX <= 0 || aSizeY <= 0) loadSheet(image, startX, startY, sizeX, sizeY, frames);
		else loadSheet(image, startX, startY, aSizeX, aSizeY, frames);
		setStepInterval(interval);
		setTexture(&getCurrentTexture());
	}
	else setFillColor(sf::Color::Transparent);
}