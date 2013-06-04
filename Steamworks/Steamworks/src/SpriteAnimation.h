#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <string>
#include <vector>
#include <memory>

class SpriteAnimation
{
public:
	SpriteAnimation(void);
	~SpriteAnimation(void);

	void loadSheet(std::string spriteSheetFile,
				   const int frameSizeX,
				   const int frameSizeY,
				   const int frameCount);

	void stepForward() { _currentFrame++; };
	void stepBack() { _currentFrame--; };

	void setStepInterval(const int interval) { _stepInterval = interval; };
	int getStepInterval() { return _stepInterval; };

	sf::Texture getCurrentTexture() { return *frameTexture[_currentFrame]; };

private:
	unsigned int _currentFrame; //The current animation frame
	unsigned int _frameCount; //Number of frames in animation
	unsigned int _stepInterval; //How many times to call the update function before updating frame

	std::unique_ptr<sf::Image> spriteSheet;
	std::vector<std::unique_ptr<sf::Texture>> frameTexture;
};

