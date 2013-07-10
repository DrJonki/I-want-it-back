#pragma once

#include <vector>

#include "SoundSource.h"
#include "LoadSettings.h"
#include "EngineSettings.h"
#include "SoundStream.h"
#include "Globals.h"

class SoundManager
{
public:
	SoundManager(void);
	~SoundManager(void);

	void loadSounds(LoadSettings& lsettings, EngineSettings& esettings);

	void loadStreams(LoadSettings& lsettings, EngineSettings& esettings);

	void playSound(const unsigned int data = 0);
	void playStreams();

	void resetSounds();

private:
	std::vector<SoundSource> _sound;
	std::vector<SoundStream> _stream;

	const unsigned int managerNumber;
};

