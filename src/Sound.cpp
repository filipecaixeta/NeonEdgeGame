#include "Sound.h"
#include <cstdio>
#include <cstdlib>

Sound::Sound()
{
	chunk = nullptr;
	channel = -1;
}

Sound::Sound(std::string file)
{
	chunk = nullptr;
	Open(file);
}

Sound::~Sound() {
	chunk = nullptr;
}

void Sound::Open(std::string file) {
	if (FILE *f = std::fopen((Resources::BASENAME_SOUND+file).c_str(), "r"))
	{
		fclose(f);
		chunk = Resources::GetSound(file);
		if(!IsOpen()) {
			printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}
}

void Sound::Play(int times) {
	if (IsOpen())
	{
		channel = Mix_PlayChannel(-1, chunk, times);
	}
}

bool Sound::IsPlaying()
{
	if (channel>=0)
		return Mix_Playing(channel);
	else
		return false;
}

void Sound::Stop() {
	Mix_HaltChannel(channel);
}

bool Sound::IsOpen() {
	return (!chunk) ? false : true;
}

