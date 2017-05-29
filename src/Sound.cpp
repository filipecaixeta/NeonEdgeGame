#include "Sound.h"
#include <cstdio>
#include <cstdlib>

Sound::Sound() {
	chunk = nullptr;
	channel = -1;
}

Sound::Sound(std::string file) {
	chunk = nullptr;
	Open(file);
}

Sound::~Sound() {
	chunk = nullptr;
}

void Sound::Open(std::string file) {
	chunk = Resources::GetSound(file);
	if(!IsOpen()) {
		printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop() {
	Mix_HaltChannel(channel);
}

bool Sound::IsOpen() {
	return (!chunk) ? false : true;
}

