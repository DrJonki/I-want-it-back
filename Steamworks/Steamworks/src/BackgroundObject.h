#pragma once

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Texture.hpp>

class BackgroundObject : public sf::RectangleShape
{
public:
	BackgroundObject(void);
	~BackgroundObject(void);
	
	void load(const bool bottom,
			  const float sizeX,
			  const float sizeY,
			  const float posX,
			  std::string textureDir);

private:
	sf::Texture _texture;
};

