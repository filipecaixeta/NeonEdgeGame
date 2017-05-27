#include "Text.h"
#include "Game.h"

SDL_Texture* Text::GetText(std::string fontFile, int fontSize,
						   SDL_Color textColor, std::string text, int lineWidth)
{
	TTF_Font* font = Resources::GetFont(fontFile,fontSize);
	SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor,lineWidth);
	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
	SDL_FreeSurface(surface);
	return texture;
}
