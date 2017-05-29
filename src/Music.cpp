#include "Music.h"
#include <cstdio>
#include <cstdlib>

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) {
	music = nullptr;
	Open(file);
}

Music::~Music() {
	music = nullptr;
}

void Music::Open(std::string file) {
	music = Resources::GetMusic(file);
	if(!IsOpen()) {
		printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void Music::Play(int times) {
	Mix_PlayMusic(music, times);
}

void Music::Stop() {
	Mix_FadeOutMusic(1000);
}

bool Music::IsOpen() {
	return (!music) ? false : true;
}

