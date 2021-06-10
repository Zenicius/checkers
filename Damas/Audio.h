#pragma once
#include <string>
#include <irrklang/irrKlang.h>

using namespace irrklang;

class Audio
{
	private:
		ISoundEngine* Music;
		ISoundEngine* Effects;
		ik_f32 volume;
		bool muted;
	public:
		Audio();
		void playEffect(std::string effect);
		void increaseVolume();
		void decreaseVolume();
		void muteMusic();
		float getVolume();
};

