#pragma once

#include <SFML\Audio.hpp>

class SoundSource : public sf::Sound
{
public:
	SoundSource(void);
	~SoundSource(void);

	void load(const std::string soundDir,
			  const float posX = 0.f,
			  const float posZ = 0.f,
			  const float minDistance = 1.f,
			  const float attenuation = 0.f,
			  const bool loop = false);
	
	unsigned int _level;
	unsigned int _data;
	unsigned int _type;

	bool played;
private:
	sf::SoundBuffer _buffer;
};