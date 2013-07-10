#include "SoundSource.h"


SoundSource::SoundSource(void)
	: _data(0)
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

	setPosition(posX, posY, 0.f);
	setMinDistance(minDistance);
	setAttenuation(attenuation);
	if (posX == 0.f && posY == 0.f) setRelativeToListener(true);
	setLoop(loop);
}