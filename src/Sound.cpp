/*
  Copyright 2017 Neon Edge Game
  File Name: Sound.cpp
  Header File Name: Sound.h
  Class Name: Sound
  Objective: class responsible for opening audio files.
*/

#include "Sound.h"
#include <cstdio>
#include <cstdlib>

/*
  Function Objective: Construction method.
  param: No parameters.
  return: No return.
*/
Sound::Sound() {
    // Initializes variables.
    chunk = nullptr;
    channel = -1;
}

/*
  Function Objective: Construction method (overwrite).
  param: Receives a string with the audio name to open.
  return: No return.
*/
Sound::Sound(std::string file) {
    chunk = nullptr; // Initializes pointer pointing to null to facilitate debugging.
    Open(file);  // Opens audio file.
}

/*
  Function Objective: Destructor method.
  param: No parameter.
  return: No return.
*/
Sound::~Sound() {
    chunk = nullptr;
}

/*
  Function Objective: Test the audio opening of the game.
  param: No parameter.
  return: No return.
*/
void Sound::Open(std::string file) {
    // Checks if file opening worked.
    if (FILE *f = std::fopen((Resources::BASENAME_SOUND+file).c_str(), "r")) {
        fclose(f); // Close file.
        chunk = Resources::GetSound(file); // Returns pointer to audio file.

            // Checks whether the audio file (chunk pointer) is different from null.
            if (!IsOpen()) {
                printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
    }
}

/*
  Function Objective: Determines the audio that should be started, its runtime and channel.
  param: Audio runtime.
  return: No return.
*/
void Sound::Play(int times) {
  if (IsOpen()) {
      channel = Mix_PlayChannel(-1, chunk, times);
  }
}

/*
  Function Objective: Checks channel usage for sound effect execution.
  param: No parameter.
  return: Returns true for audio being executed and false if there is no running execution on the channel.
*/
bool Sound::IsPlaying() {
    // Checks if it has an audio effect running.
    if (channel >= 0) {
        return Mix_Playing(channel);
    } else {
        return false;
    }
}

/*
  Function Objective: Stop running channel.
  param: No parameter.
  return: No return.
*/
void Sound::Stop() {
    Mix_HaltChannel(channel);
}

/*
  Function Objective: Checks pointer to audio file.
  param: No parameter.
  return: Returns true for pointer to non-null audio file and false to null.
*/
bool Sound::IsOpen() {
    // Checks whether the pointer to the audio points to null.
    if (!chunk){
        return false;
    } else {
        return true;
    }
}
