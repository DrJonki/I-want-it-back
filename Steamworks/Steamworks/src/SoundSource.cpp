#include "SoundSource.h"


SoundSource::SoundSource(void)
	: _data(0),
	  _level(0),
	  _type(0),
	  played(false)
{}

SoundSource::~SoundSource(void)
{
	stop();
}


void SoundSource::load(const std::string soundDir,
					   const float posX,
					   const float posZ,
					   const float minDistance,
					   const float attenuation,
					   const bool loop)
{
	_buffer.loadFromFile(soundDir);
	setBuffer(_buffer);

	setPosition(posX, 0.f, posZ);
	setMinDistance(minDistance);
	setAttenuation(attenuation);
	if (posX == 0.f && posZ == 0.f) setRelativeToListener(true);
	setLoop(loop);

	setVolume(0.f);
}