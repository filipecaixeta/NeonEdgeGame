#ifndef MUSIC_H_
#define MUSIC_H_

#include "Resources.h"
#include <string>

#define FADE_OUT_MUSIC_TIMING 1000
#define EMPTY_STRING ""
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

class Music {
private:
    Mix_Music* music;
    bool IsOpen();

public:
    Music();
    Music(std::string file);
    ~Music();
    void Open(std::string file);
    void Play(int times);
    void Stop();
};

#endif /* INCLUDE_MUSIC_H_ */
