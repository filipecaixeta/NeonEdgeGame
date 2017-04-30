#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>

class Resources {
private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
	static std::unordered_map<std::string, TTF_Font*> fontTable;

    static std::string BASENAME;
    static std::string BASENAME_IMAGE;
    static std::string BASENAME_MUSIC;
    static std::string BASENAME_SOUND;
    static std::string BASENAME_FONT;

public:
	static SDL_Texture* GetImage(std::string file);
	static void ClearImages();
	static Mix_Music* GetMusic(std::string file);
	static void ClearMusics();
	static Mix_Chunk* GetSound(std::string file);
	static void ClearSounds();
	static TTF_Font* GetFont(std::string file, int fontSize);
	static void ClearFonts();
};

#endif /* RESOURCES_H_ */
