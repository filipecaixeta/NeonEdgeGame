#include "SoundComponent.h"

SoundComponent::SoundComponent(std::string playerName)
{
	sounds.emplace("Crouching",Sound("Agachamento.ogg"));
	sounds.emplace("Jump",Sound("Pulo.ogg"));
	sounds.emplace("Flying",Sound("DroneVoando.wav"));
	sounds.emplace("Attack",Sound(playerName+"Ataque.ogg"));
	sounds.emplace("Damage",Sound(playerName+"Dano.wav"));
	sounds.emplace("Die",Sound(playerName+"Morte.wav"));
	sounds.emplace("Item",Sound("Item.ogg"));
}

void SoundComponent::Play(std::string soundName, int options)
{
	if (!sounds.count(soundName) || sounds[soundName].IsPlaying())
		return;

	if (options&SOUND_STOP)
	{
		sounds[soundName].Stop();
	}
	if ((options&SOUND_PLAY) || (options&SOUND_PLAY_ONCE))
	{
		sounds[soundName].Play(0);
	}
	if ((options&SOUND_REPEAT))
	{
		sounds[soundName].Play(-1);
	}
}

void SoundComponent::Bomb(int options)
{
	Play("Bomb",options);
}

void SoundComponent::Item(int options)
{
	Play("Item",options);
}

void SoundComponent::Crouching(int options)
{
	Play("Crouching",options);
}

void SoundComponent::Jump(int options)
{
	Play("Jump",options);
}

void SoundComponent::Attack(int options)
{
	Play("Attack",options);
}

void SoundComponent::Die(int options)
{
	Play("Die",options);
}

void SoundComponent::Damage(int options)
{
	Play("Damage",options);
}

void SoundComponent::Flying(int options)
{
	Play("Flying",options);
}
