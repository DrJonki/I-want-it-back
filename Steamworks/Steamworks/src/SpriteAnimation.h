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

	void stepForward();
	void stepBack();
	void setFrame(const unsigned int frame) { _currentFrame = frame; };

	void setStepInterval(const int interval) { _stepInterval = interval; };
	int getStepInterval() { return _stepInterval; };

	sf::Texture getCurrentTexture() { return *frameTexture[_currentFrame - 1]; };

private:
	unsigned int _currentFrame; //The current animation frame
	unsigned int _frameCount; //Number of frames in animation
	unsigned int _stepInterval; //How many times to call the update function before updating frame

	std::unique_ptr<sf::Image> spriteSheet; //Pointer to the spritesheet image file
	std::vector<std::unique_ptr<sf::Texture>> frameTexture; //Container for the frame textures
};

