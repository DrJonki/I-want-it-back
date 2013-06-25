#include "ForegroundObject.h"


ForegroundObject::ForegroundObject(void)
{}

ForegroundObject::~ForegroundObject(void)
{}


void ForegroundObject::load(const float sizeX,
						    const float sizeY,
							const float posX,
							const float posY,
							const std::string textureDir)
{
	setSize(sf::Vector2f(sizeX, sizeY));
	setOrigin(sizeX / 2, sizeY / 2);
	setPosition(posX, posY);

	_texture.loadFromFile(textureDir);
	setTexture(&_texture);
}