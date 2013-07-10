#pragma once

#include <SFML\Audio.hpp>

class SoundStream
{
public:
	SoundStream(void);
	~SoundStream(void);

	void load(const std::string soundDir,
			  const float posX = 0.f,
			  const float posY = 0.f,
			  const float minDistance = 1.f,
			  const float attenuation = 0.f,
			  const bool loop = false);

	unsigned int _data;

	std::shared_ptr<sf::Music> _stream;
};