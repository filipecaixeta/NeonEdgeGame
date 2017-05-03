#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable = std::unordered_map<std::string, SDL_Texture*>();
std::unordered_map<std::string, Mix_Music*> Resources::musicTable = std::unordered_map<std::string, Mix_Music*>();
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable = std::unordered_map<std::string, Mix_Chunk*>();
std::unordered_map<std::string, TTF_Font*> Resources::fontTable = std::unordered_map<std::string, TTF_Font*>();

std::string Resources::BASENAME = "resources/";
std::string Resources::BASENAME_IMAGE = "resources/img/";
std::string Resources::BASENAME_MUSIC = "resources/audio/";
std::string Resources::BASENAME_SOUND = "resources/audio/";
std::string Resources::BASENAME_FONT = "resources/font/";

SDL_Texture* Resources::GetImage(std::string file,bool forceDuplicate=false) {
    std::string fileKey = file;
    if (forceDuplicate)
        while(imageTable.count(fileKey))
            fileKey += "*";
    if(!imageTable.count(fileKey))
        imageTable.emplace(fileKey, IMG_LoadTexture(Game::GetInstance().GetRenderer(), (Resources::BASENAME_IMAGE+file).c_str()));
    if(imageTable.at(fileKey) == nullptr) {
		printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
	}
    return imageTable.at(fileKey);
}

void Resources::ClearImages() {
	for(auto& i: imageTable)
		SDL_DestroyTexture(i.second);
	imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
	if(!musicTable.count(file))
        musicTable.emplace(file, Mix_LoadMUS((Resources::BASENAME_MUSIC+file).c_str()));
	if(musicTable.at(file) == nullptr) {
		printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return musicTable.at(file);
}

void Resources::ClearMusics() {
	for(auto& i: musicTable)
		Mix_FreeMusic(i.second);
	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
	if(!soundTable.count(file))
        soundTable.emplace(file, Mix_LoadWAV((Resources::BASENAME_SOUND+file).c_str()));
	if(soundTable.at(file) == nullptr) {
		printf("Mix_LoadWAV failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return soundTable.at(file);
}

void Resources::ClearSounds() {
	for(auto& i: soundTable)
		Mix_FreeChunk(i.second);
	soundTable.clear();
}

TTF_Font* Resources::GetFont(std::string file, int fontSize) {
	if(!fontTable.count(file))
        fontTable.emplace(file, TTF_OpenFont((Resources::BASENAME_FONT+file).c_str(), fontSize));
	if(fontTable.at(file) == nullptr) {
		printf("TTF_OpenFont failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return fontTable.at(file);
}

void Resources::ClearFonts() {
	for(auto& i: fontTable)
		TTF_CloseFont(i.second);
	fontTable.clear();
}
