#include "SpriteAnimation.h"


SpriteAnimation::SpriteAnimation(void)
{
	_currentFrame = 1;
	_frameCount = 1;
	_stepInterval = 1;
	_tempSteps = 1;
}


SpriteAnimation::~SpriteAnimation(void)
{
	frameTexture.clear();
}

void SpriteAnimation::loadSheet(sf::Image &sheet,
								const int startX,
								const int startY,
								const int frameSizeX,
								const int frameSizeY,
								const int frameCount)
{
	_frameCount = frameCount;

	frameTexture.reserve(_frameCount);

	for (unsigned int i = 0; i < _frameCount; i++){
		frameTexture.emplace_back(sf::Texture());
		
		frameTexture[i].loadFromImage(sheet, sf::IntRect((i * frameSizeX) + startX, startY, frameSizeX, frameSizeY));
	}
}


void SpriteAnimation::stepForward(const bool force)
{
	if (force){
		_currentFrame++;
		if (_currentFrame > _frameCount) _currentFrame = 1;
		_tempSteps = 1;
	}

	else {
		if (_stepInterval == _tempSteps) _currentFrame++;

		if (_currentFrame > _frameCount) _currentFrame = 1;

		_tempSteps++;
		if (_tempSteps > _stepInterval) _tempSteps = 1;
	}
}
void SpriteAnimation::stepBack(const bool force)
{
	if (force){
		_currentFrame--;
		if (_currentFrame < 1) _currentFrame = _frameCount;
		_tempSteps = 1;
	}

	else {
		if (_tempSteps == 1) _currentFrame--;

		if (_currentFrame < 1) _currentFrame = _frameCount;

		_tempSteps--;
		if (_tempSteps < 1) _tempSteps = _stepInterval;
	}
}

bool SpriteAnimation::lastFrame()
{
	if (_currentFrame == _frameCount) return true;
	return false;
}