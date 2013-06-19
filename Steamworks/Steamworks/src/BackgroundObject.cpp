#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(void)
{}

BackgroundObject::~BackgroundObject(void)
{}

void BackgroundObject::load(const bool bottom,
							const float sizeX,
							const float sizeY,
							const float posX,
							std::string textureDir)
{
	setSize(sf::Vector2f(sizeX, sizeY));
	if (!bottom) setOrigin(0, sizeY);
	setPosition(posX, 600);

	if (!_texture.loadFromFile(textureDir)) throw;
	setTexture(&_texture);
}