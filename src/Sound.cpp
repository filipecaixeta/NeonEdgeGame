/**
 * Copyright (c) 2013 Thomas Park
 * File Name: Sound.cpp
 * Header File Name: Sound.h
 * Class Name: Sound
 * Objective: Class responsible for opening audio files.
 */

#include "Sound.h"
#include <cstdio>
#include <cstdlib>
#include <assert.h>

/**
 * Objective: Construction method.
 *
 * @param - No parameters.
 * @return - none.
 */
Sound::Sound() {
    // Initializes variables.
    chunk = nullptr;
    channel = CHANNEL_INITIAL_VALUE;
}

/**
 * Objective: Construction method (overwrite).
 *
 * @param - Receives a string with the audio name to open.
 * @return - none.
 */
Sound::Sound(std::string file) {
    chunk = nullptr;  // Initializes pointer pointing to null to facilitate debugging.
    assert(file != EMPTY_STRING);
    Open(file);  // Opens audio file.
}

/**
    Objective: Destructor method.
    @param - No parameter.
    @return - none.

*/
Sound::~Sound() {
    chunk = nullptr;
}

/**
 * Objective: Test the audio opening of the game.
 *
 * @param - No parameter.
 * @return - none.
 */
void Sound::Open(std::string file) {
    // Checks if file opening worked.
    if (FILE *f = std::fopen((Resources::BASENAME_SOUND+file).c_str(), "r")) {
        assert(f != NULL);
        fclose(f); // Close file.
        chunk = Resources::GetSound(file); // Returns pointer to audio file.

            // Checks whether the audio file (chunk pointer) is different from null.
            if (!IsOpen()) {
                assert(IsOpen() == true);
                printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            } else {
                // It does nothing.
            }
    } else {
          // It does nothing.
    }
}

/**
 * Objective: Determines the audio that should be started, its runtime and channel.
 * @param - Audio runtime.
 * @return - none.
 */
void Sound::SoundPlay(int times) {
    assert(times >= INT_SIZE_MIN && times <= INT_SIZE_MAX);
    if (IsOpen()) {
        assert(IsOpen() != false);
        channel = Mix_PlayChannel(CHANNEL_INITIAL_VALUE, chunk, times);
    } else {
      // It does nothing.
    }
}

/**
 * Objective: Checks channel usage for sound effect execution.
 *
 * @param - No parameter.
 * @return - Returns true for audio being executed and false if there is no running execution on the channel.
 */
bool Sound::IsPlaying() {
    bool isPlaying = false;  // Initiates the "tapping" state as false.

    // Checks if it has an audio effect running.
    assert(channel >= INT_SIZE_MIN && channel <= INT_SIZE_MAX);
    if (channel >= 0) {
        isPlaying = Mix_Playing(channel);
    } else {
        // It does nothing.
    }
    return isPlaying;
}

/**
 * Objective: Stop running channel.
 * @param - No parameter.
 * @return - none.
 */
void Sound::SoundStop() {
    assert(channel >= INT_SIZE_MIN && channel <= INT_SIZE_MAX);
    Mix_HaltChannel(channel);
}

/**
 * Objective: Checks pointer to audio file.
 *
 * @param - No parameter.
 * @return - Returns true for pointer to non-null audio file and false to null.
 */
bool Sound::IsOpen() {
    bool statusSoundOpen = false; // Starts audio state as false (closed).

    assert(statusSoundOpen == false);
    // Checks if the audio pointer is valid.
    if (chunk) {
        statusSoundOpen = true;
    } else {
        // It does nothing.
    }
    return statusSoundOpen;
}
