#include "SoundSource.h"


SoundSource::SoundSource(void)
	: _data(0),
	  _level(0),
	  played(false)
{}

SoundSource::~SoundSource(void)
{
	stop();
}


void SoundSource::load(const std::string soundDir,
					   const float posX,
					   const float posY,
					   const float minDistance,
					   const float attenuation,
					   const bool loop)
{
	_buffer.loadFromFile(soundDir);
	setBuffer(_buffer);

	setPosition(posX, 0.f, posY);
	setMinDistance(minDistance);
	setAttenuation(attenuation);
	if (posX == 0.f && posY == 0.f) setRelativeToListener(true);
	setLoop(loop);
}