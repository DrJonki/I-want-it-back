#include "SpriteAnimation.h"

#include "Globals.h"


SpriteAnimation::SpriteAnimation(void)
{
	_currentFrame = 1;
	_frameCount = 1;
	_stepInterval = 1;
	_tempSteps = 1;
	_frameChanged = false;
}


SpriteAnimation::~SpriteAnimation(void)
{
	_assignedSounds.clear();
	frameTexture.clear();
}

bool SpriteAnimation::loadSheet(sf::Image &sheet,
								const int startX,
								const int startY,
								const int frameSizeX,
								const int frameSizeY,
								const int frameCount,
								const bool smooth)
{
	_frameCount = frameCount;

	frameTexture.reserve(_frameCount);

	for (unsigned int i = 0; i < _frameCount; i++){
		frameTexture.emplace_back(sf::Texture());
		
		frameTexture[i].loadFromImage(sheet, sf::IntRect((i * frameSizeX) + startX, startY, frameSizeX, frameSizeY));
		frameTexture[i].setSmooth(smooth);
	}

	return true;
}


void SpriteAnimation::stepForward(const bool force)
{
	if (force){
		_currentFrame++;
		if (_currentFrame > _frameCount) _currentFrame = 1;
		_tempSteps = 1;
		_frameChanged = true;
	}

	else {
		if (_stepInterval == _tempSteps){
			_currentFrame++;
			_frameChanged = true;
		}

		if (_currentFrame > _frameCount) _currentFrame = 1;

		_tempSteps++;
		if (_tempSteps > _stepInterval) _tempSteps = 1;
	}

	checkSounds();
}
void SpriteAnimation::stepBack(const bool force)
{
	if (force){
		_currentFrame--;
		if (_currentFrame < 1) _currentFrame = _frameCount;
		_tempSteps = 1;
		_frameChanged = true;
	}

	else {
		if (_tempSteps == 1){
			_currentFrame--;
			_frameChanged = true;
		}

		if (_currentFrame < 1) _currentFrame = _frameCount;

		_tempSteps--;
		if (_tempSteps < 1) _tempSteps = _stepInterval;
	}

	checkSounds();
}

void SpriteAnimation::setCurrentFrame(const unsigned int currentFrame)
{
	if (frameTexture.size() > 0){
		_currentFrame = currentFrame;
		_tempSteps = 1;
		_frameChanged = true;
	}

	checkSounds();
}

bool SpriteAnimation::lastFrame()
{
	if (_currentFrame == _frameCount) return true;
	return false;
}

bool SpriteAnimation::frameChanged()
{
	if (_frameChanged){
		_frameChanged = false;
		return true;
	}
	else return false;
}

void SpriteAnimation::assignSound(sf::Sound* sound, const unsigned int frameNo, const unsigned int levelNo)
{
	_assignedSounds.emplace_back(assignedSound());

	_assignedSounds.back()._sound = sound;
	_assignedSounds.back()._frame = frameNo;
	_assignedSounds.back()._level = levelNo;
}

void SpriteAnimation::checkSounds()
{
	for (unsigned int i = 0; i < _assignedSounds.size(); i++){
		if (_currentFrame == _assignedSounds[i]._frame && (_assignedSounds[i]._level == ns::soundState || ns::soundState == 0)) _assignedSounds[i]._sound->play();
	}
}