#include "SoundStream.h"


SoundStream::SoundStream(void)
	: _data(0),
	  _level(0),
	  _type(0),
	  played(false)
{
	_stream = std::shared_ptr<sf::Music>(new sf::Music);
}


SoundStream::~SoundStream(void)
{
	_stream->stop();
	_stream.reset();
}


void SoundStream::load(std::string soundDir,
					   const float posX,
					   const float posZ,
				   	   const float minDistance,
					   const float attenuation,
					   const bool loop)
{
	_stream.get()->openFromFile(soundDir);

	_stream.get()->setPosition(posX, 0.f, posZ);
	_stream.get()->setMinDistance(minDistance);
	_stream.get()->setAttenuation(attenuation);
	if (posX == 0.f && posZ == 0.f) _stream.get()->setRelativeToListener(true);
	_stream.get()->setLoop(loop);

	_stream.get()->setVolume(0);
}