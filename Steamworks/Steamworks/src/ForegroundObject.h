#pragma once

#include <SFML\Graphics.hpp>

class ForegroundObject : public sf::RectangleShape
{
public:
	ForegroundObject(void);
	~ForegroundObject(void);

	void load(const float sizeX,
			  const float sizeY,
			  const float posX,
			  const float posY,
			  const std::string textureDir);

private:
	sf::Texture _texture;
};

