#ifndef MUSIC_H_
#define MUSIC_H_

#include "Resources.h"
#include <string>

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
