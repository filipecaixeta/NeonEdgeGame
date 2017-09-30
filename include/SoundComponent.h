#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include <unordered_map>
#include <string>

#include "Sound.h"

#define SOUND_STOP 1
#define SOUND_PLAY 2
#define SOUND_REPEAT 4
#define SOUND_PLAY_ONCE 8

class SoundComponent
{
public:
	SoundComponent(std::string playerName);
	void SoundBomb(int options=SOUND_PLAY_ONCE);
	void SoundCrouching(int options=SOUND_PLAY_ONCE);
	void SoundJump(int options=SOUND_PLAY_ONCE);
	void SoundAttack(int options=SOUND_PLAY_ONCE);
	void SoundDie(int options=SOUND_PLAY_ONCE);
	void SoundDamage(int options=SOUND_PLAY_ONCE);
	void SoundFlying(int options=SOUND_REPEAT);
	void SoundItem(int options=SOUND_PLAY_ONCE);
	void SoundPlay(std::string soundName, int options);

	std::unordered_map<std::string,Sound> sounds;
};

#endif // SOUNDCOMPONENT_H
