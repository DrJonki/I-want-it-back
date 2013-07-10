#include "SoundStream.h"


SoundStream::SoundStream(void)
	: _data(0)
{}


SoundStream::~SoundStream(void)
{
	_stream->stop();
}


void SoundStream::load(const std::string soundDir,
					   const float posX,
					   const float posY,
				   	   const float minDistance,
					   const float attenuation,
					   const bool loop)
{
	_stream = std::shared_ptr<sf::Music>(new sf::Music);

	_stream->openFromFile(soundDir);

	_stream->setPosition(posX, posY, 0.f);
	_stream->setMinDistance(minDistance);
	_stream->setAttenuation(attenuation);
	if (posX == 0.f && posY == 0.f) _stream->setRelativeToListener(true);
	_stream->setLoop(loop);
}