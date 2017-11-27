#include "Music.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <assert.h>

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
		assert(file != EMPTY_STRING);
    Open(file);
}

Music::~Music() {
    music = nullptr;
}

void Music::Open(std::string file) {
		assert(file != EMPTY_STRING);
    music = Resources::GetMusic(file);
    if (!IsOpen()) {
			  assert(IsOpen() != true);
        printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void Music::Play(int times) {
	  assert(times >= INT_SIZE_MIN && times <= INT_SIZE_MAX);
    Mix_PlayMusic(music, times);
}

void Music::Stop() {
    Mix_FadeOutMusic(FADE_OUT_MUSIC_TIMING);
}

bool Music::IsOpen() {
    return (!music) ? false : true;
}
