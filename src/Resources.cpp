 /**
Copyright (c) 2017 Neon Edge Game.
File Name: Resources.cpp
Header File Name: Resources.h
Class Name: Resources
Objective: Class responsable to manager the games resources.

*/
#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include "Resources.h"
#include "Game.h"
#include "Logger.h"

// Inicializate unordered_maps.
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable = std::unordered_map<std::string, SDL_Texture*>();
std::unordered_map<std::string, SDL_Surface*> Resources::surfaceTable = std::unordered_map<std::string, SDL_Surface*>();
std::unordered_map<std::string, Mix_Music*> Resources::musicTable = std::unordered_map<std::string, Mix_Music*>();
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable = std::unordered_map<std::string, Mix_Chunk*>();
std::unordered_map<std::string, TTF_Font*> Resources::fontTable = std::unordered_map<std::string, TTF_Font*>();

// Set the path of the resources.
std::string Resources::BASENAME = "resources/";
std::string Resources::BASENAME_IMAGE = "resources/img/";
std::string Resources::BASENAME_MUSIC = "resources/audio/music/";
std::string Resources::BASENAME_SOUND = "resources/audio/sound/";
std::string Resources::BASENAME_FONT = "resources/font/";

/**
   Objective: Get aimage that is requested.
   @param string file - name ofthe image on the unorded_map.
   @param bool forceDuplicate - force a duplication on the class. 
   @return SDL_Texture imageTable - a texture of the  sdl library.

*/

SDL_Texture* Resources::GetImage(std::string file, bool forceDuplicate = false) {
	Log::instance.info("Get image " + file);
	std::string fileKey = file;

	// if ForceDuplicate is true, the code check the numbers of instances and add one asterisk to the file.
	if (forceDuplicate){
		while(imageTable.count(fileKey)) {
			fileKey += "*";
		}
	}

	// Check the existence of a file, if not exist the code construct and insert the element on the unorded_map.
	if(!imageTable.count(fileKey)) {
		if(surfaceTable.count(file)) {
			imageTable.emplace(fileKey, SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surfaceTable[file]));
		} else {
			imageTable.emplace(fileKey, IMG_LoadTexture(Game::GetInstance().GetRenderer(), (Resources::BASENAME_IMAGE + file).c_str()));
		}
	}
	// Get a error if the SDL_Texture in the unorded_map is nullptr. 
	if(imageTable.at(fileKey) == nullptr) {
		std::string error = SDL_GetError();
		Log::instance.error("Error: " + error);
	}

	assert(imageTable.at(file) != nullptr);
	return imageTable.at(fileKey);
}

/**
   Objective: Clear all image of the screen.
   @param None
   @return void

*/

void Resources::ClearImages() {
	Log::instance.info("Cleaning images");
	// Pass to all elements of the unorded_map and destroy then.
	for(auto& i : imageTable) {
		SDL_DestroyTexture(i.second);
	}
	imageTable.clear();
}

/**
   Objective: Get a surface in the unorded_map.
   @param string file - the path of the image.
   @return The asked SDL_surface.

*/
SDL_Surface *Resources::GetSurface(std::string file) {
	Log::instance.info("Get surface" + file);
	// Construct a insert the file element requested.
	if(!surfaceTable.count(file)) {
		surfaceTable.emplace(file, IMG_Load((Resources::BASENAME_IMAGE + file).c_str()));
	}

	// Put a error if fail to load the file.
	if(surfaceTable.at(file) == nullptr) {
		std::string error = SDL_GetError();
		Log::instance.error("IMG_Load failed:" + error);
		exit(EXIT_FAILURE);
	}

	assert(surfaceTable.at(file) != nullptr);
	return surfaceTable.at(file);
}

/**
   Objective: Clear the unorded_map of SDL_Surface.
   @param None
   @return void

*/
void Resources::ClearSurface() {
	Log::instance.info("Cleaning images");
	// Pass to all elements of the unorded_map and destroy then.
	for(auto& i : surfaceTable) {
		SDL_FreeSurface(i.second);
	}
	surfaceTable.clear();
}

/**
   Objective: Get a specific music in the unorded_map.
   @param string file - name file to search.
   @return Mix_Music - the Mix_music that was search.

*/
Mix_Music* Resources::GetMusic(std::string file) {
	Log::instance.info("Get music" + file);
	// Construct a insert the music element requested.
	if(!musicTable.count(file)) {
		musicTable.emplace(file, Mix_LoadMUS((Resources::BASENAME_MUSIC + file).c_str()));
	}
	// Prints a error if fails to open file.
	if(musicTable.at(file) == nullptr) {
		std::string error = SDL_GetError();
		Log::instance.error("Mix_LoadMUS failed: " + error);
		exit(EXIT_FAILURE);
	}

	
	assert(musicTable.at(file) != nullptr);
	return musicTable.at(file);
}

/**
   Objective: Clear the unordedmap of musics.
   @param None
   @return void

*/
void Resources::ClearMusics() {
	Log::instance.info("Clear all musics");
	// Pass to all elements of the unorded_map and destroy then.
	for(auto& i : musicTable) {
		Mix_FreeMusic(i.second);
	}
	musicTable.clear();
}

/**
   Objective: Get a specific sound in the unorded_map.
   @param string file - Name of the require sound.
   @return Mix_Chunk - the instance of the Mix_check(represent a soound in SDL).

*/
Mix_Chunk* Resources::GetSound(std::string file) {
	Log::instance.info("Get sound" + file);
	// Construct a insert the sound element requested.
	if(!soundTable.count(file)) {
		soundTable.emplace(file, Mix_LoadWAV((Resources::BASENAME_SOUND + file).c_str()));
	}
	// Prints a error if fails to open file.
	if(soundTable.at(file) == nullptr) {
		std::string error = SDL_GetError();
		Log::instance.error("Mix_LoadWAV failed: " + error);
		exit(EXIT_FAILURE);
	}

	
	assert(soundTable.at(file) != nullptr);
	return soundTable.at(file);
}

/**
   Objective: Clear the unordedmap of sounds.
   @param None.
   @return void.

*/
void Resources::ClearSounds() {
	Log::instance.info("Clear all sounds");
	// Pass to all elements of the unorded_map and destroy then.
	for(auto& i : soundTable) {
		Mix_FreeChunk(i.second);
	}
	soundTable.clear();
}

/**
   Objective: Get a specific Font for visual strings in the game in the unorded_map.
   @param string file - path to the font.  
   @param int fontSize.
   @return TTF_Font - A instance of TTF_Font a graphic visualization to strings. 

*/
TTF_Font* Resources::GetFont(std::string file, int fontSize) {
	Log::instance.info("Get font: " + file);
	char vetor[5]; //vector of char to store fontSize.
	sprintf(vetor, "%d", fontSize);
	std::string key = file + vetor; // Set the key value for the unorded_map
	
	// Construct a insert the font element requested.
	if(!fontTable.count(key)) {
		fontTable.emplace(key, TTF_OpenFont((Resources::BASENAME_FONT + file).c_str(), fontSize));
	}
	// Prints a error if fails to open file.
	if(fontTable.at(key) == nullptr) {
		std::string error = SDL_GetError();
		Log::instance.error("TTF_OpenFont failed: " + error);
		exit(EXIT_FAILURE);
	}

	
	assert(fontTable.at(file) != nullptr);
	return fontTable.at(key);
}

/**
   Objective: Clear the unordedmap of TTF_Fonts
   @param None
   @return void

*/
void Resources::ClearFonts() {
	Log::instance.info("Clear all fonts");
	// Pass to all elements of the unorded_map and destroy then.
	for(auto& i : fontTable) {
		TTF_CloseFont(i.second);
	}
	fontTable.clear();
}
