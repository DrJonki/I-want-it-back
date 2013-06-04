#include "SpriteAnimation.h"


SpriteAnimation::SpriteAnimation(void)
{
	_currentFrame = 1;
	_frameCount = 1;
	_stepInterval = 1;
}


SpriteAnimation::~SpriteAnimation(void)
{
	frameTexture.clear();
}

void SpriteAnimation::loadSheet(std::string spriteSheetFile,
								const int frameSizeX,
								const int frameSizeY,
								const int frameCount)
{
	_frameCount = frameCount;

	spriteSheet = std::unique_ptr<sf::Image>(new sf::Image);
	spriteSheet->loadFromFile(spriteSheetFile);

	for (int i = 0; i < frameCount; i++){
		frameTexture.push_back(std::unique_ptr<sf::Texture>(new sf::Texture));

		frameTexture[i]->loadFromImage(*spriteSheet, sf::IntRect(i * frameSizeX, 0, frameSizeX, frameSizeY));
	}
}


void SpriteAnimation::stepForward()
{
	_currentFrame += _stepInterval;

	if (_currentFrame > _frameCount) _currentFrame = 1;
}
void SpriteAnimation::stepBack()
{
	_currentFrame -= _stepInterval;

	if (_currentFrame < _frameCount) _currentFrame = _frameCount;
}
