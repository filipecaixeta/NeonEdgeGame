#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <unordered_map>
#define clamp(N,L,U) N=std::max(L,std::min(N,U))

class Resources
{
private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable; // Variable to store SDL_Textures in a dictionary.
	static std::unordered_map<std::string, SDL_Surface*> surfaceTable; // Variable to store SDL_Surface in a dictionary.
	static std::unordered_map<std::string, Mix_Music*> musicTable; // Variable to store Mix_music in a dictionary.
	static std::unordered_map<std::string, Mix_Chunk*> soundTable; // Variable to store SDL_Textures in a dictionary.
	static std::unordered_map<std::string, TTF_Font*> fontTable; // Variable to store SDL_Textures in a dictionary.
	static std::unordered_map<std::string, SDL_Texture*> textTable; // Variable to store SDL_Textures in a dictionary.

public:
	static std::string BASENAME; // Variable to store a path to the folder of the resources.
	static std::string BASENAME_IMAGE; // Variable to store a path to the folder of the images.
	static std::string BASENAME_MUSIC; // Variable to store a path to  the folder that contains music files.
	static std::string BASENAME_SOUND; // Variable to store a path to  the folders that contains all sounds of the game.
	static std::string BASENAME_FONT; // Variable to store a path of the folder that contais the characters fonts of the game.

	static SDL_Texture* GetImage(std::string file,bool forceDuplicate);
	static void ClearImages();
	static SDL_Surface* GetSurface(std::string file);
	static void ClearSurface();
	static Mix_Music* GetMusic(std::string file);
	static void ClearMusics();
	static Mix_Chunk* GetSound(std::string file);
	static void ClearSounds();
	static TTF_Font* GetFont(std::string file, int fontSize);
	static void ClearFonts();
};

#endif /* RESOURCES_H_ */
