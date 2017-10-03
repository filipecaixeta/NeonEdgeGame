#ifndef MUSIC_H_
#define MUSIC_H_

#include "Resources.h"
#include <string>

class Music {
private:
    Mix_Music* music;

public:
    Music();
    Music(std::string file);
    ~Music();
    void Open(std::string file);
    void Play(int times);
    void Stop();
    bool IsOpen();
};

#endif /* MUSIC_H_ */
