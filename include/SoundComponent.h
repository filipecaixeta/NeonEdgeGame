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
	void Bomb(int options=SOUND_PLAY_ONCE);
	void Crouching(int options=SOUND_PLAY_ONCE);
	void Jump(int options=SOUND_PLAY_ONCE);
	void Attack(int options=SOUND_PLAY_ONCE);
	void Die(int options=SOUND_PLAY_ONCE);
	void Damage(int options=SOUND_PLAY_ONCE);
	void Flying(int options=SOUND_REPEAT);
	void Play(std::string soundName, int options);

	std::unordered_map<std::string,Sound> sounds;
};

#endif // SOUNDCOMPONENT_H
