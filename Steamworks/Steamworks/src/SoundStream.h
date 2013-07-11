#pragma once

#include <SFML\Audio.hpp>

#include <Windows.h>

class SoundStream
{
public:
	SoundStream(void);
	~SoundStream(void);

	void load(const std::string soundDir,
			  const float posX = 0.f,
			  const float posZ = 0.f,
			  const float minDistance = 1.f,
			  const float attenuation = 0.f,
			  const bool loop = true);


	unsigned int _data;
	unsigned int _level;
	unsigned int _type;

	bool played;

	std::shared_ptr<sf::Music> _stream;
};