#pragma once

#include <SFML\System\Vector2.hpp>

#include <string>

class EngineSettings
{
public:
	EngineSettings(void);
	~EngineSettings(void);

	void loadDefaults();
	void loadFromFile();
	void writeToFile();

	void updateResolution();

	bool usingCustomRes();

	int resVectorNumber;
	sf::Vector2i resolution;
	unsigned int antiAliasing;
	bool smoothTextures;
	bool vSync;
	bool fullScreen;

	float worldGravity;

	bool debug;

	int globalVolume;
	int soundVolume;
	int musicVolume;
	int anbientVolume;

	unsigned int backgroundObjectLimit;
	unsigned int mapObjectLimit;
	unsigned int foregroundObjectLimit;
	unsigned int triggerObjectLimit;
	unsigned int soundSourceLimit;
	unsigned int soundStreamLimit;
};

