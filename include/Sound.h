#ifndef SOUND_H_
#define SOUND_H_

#include "Resources.h"
#include <string>

#define EMPTY_STRING ""
#define CHANNEL_INITIAL_VALUE -1
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

class Sound {
private:
    Mix_Chunk* chunk;
    int channel;

public:
    Sound();
    Sound(std::string file);
    ~Sound();
    void Open(std::string file);
    void SoundPlay(int times);
    void SoundStop();
    bool IsOpen();
    bool IsPlaying();
};

#endif /* SOUND_H_ */
