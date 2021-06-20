#include "Audio.h"

Audio::Audio()
{
	this->Music = createIrrKlangDevice();
	this->Effects = createIrrKlangDevice();
	
	muted = true;
	volume = 0.2f;

	if(!muted) Music->setSoundVolume(volume);
	else Music->setSoundVolume(0.0f);

	Music->play2D("Res/music.flac", true);
}

void Audio::playEffect(std::string effect)
{
	std::string path = "Res/" + effect + ".wav";
	Effects->setSoundVolume(volume);
	Effects->play2D(path.c_str(), false);
}

void Audio::increaseVolume()
{
	if (volume < 1.0f)
	{
		volume += 0.1f;
		if(!muted) Music->setSoundVolume(volume);
		Effects->setSoundVolume(volume);
	}
}

void Audio::decreaseVolume()
{
	if (volume > 0)
	{
		volume -= 0.1f;
		if(!muted) Music->setSoundVolume(volume);
		Effects->setSoundVolume(volume);
	}
}

void Audio::muteMusic()
{
	if (!muted)
	{
		Music->setSoundVolume(0.0f);
		muted = true;
	}
	else
	{
		Music->setSoundVolume(volume);
		muted = false;
	}
}

float Audio::getVolume()
{
	return this->volume;
}

