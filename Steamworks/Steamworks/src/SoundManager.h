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
	void playStream(const unsigned int data = 0);

	void resetSounds();

	void updateVolumes();

private:
	std::vector<SoundSource> _sound;
	std::vector<SoundStream> _stream;

	EngineSettings _esettings;
};

