#include "SpriteAnimation.h"


SpriteAnimation::SpriteAnimation(void)
{
	_currentFrame = 0;
	_frameCount = 0;
	_stepInterval = 0;
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
	spriteSheet->loadFromFile(spriteSheetFile);

	for (int i = 0; i < frameCount; i++){
		frameTexture.push_back(std::unique_ptr<sf::Texture>(new sf::Texture));

		frameTexture[i]->loadFromImage(*spriteSheet, sf::IntRect(i * frameSizeX, 0, frameSizeX, frameSizeY));
	}
}
