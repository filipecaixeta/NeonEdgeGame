#include "Text.h"
#include "Game.h"

Text::Text() {

}

Text::Text(std::string fontFile, int fontSize, TextStyle style, SDL_Color color, std::string text, int x, int y) {
	font = Resources::GetFont(fontFile, fontSize);
	Text::fontSize = fontSize;
	Text::style = style;
	Text::color = color;
	Text::text = text;
	box.x = x;
	box.y = y;
	texture = RemakeTexture();
	if(!texture)
		printf("fuck");
}

Text::~Text() {
	font = nullptr;
	if(texture)
		SDL_DestroyTexture(texture);
	texture = nullptr;
	if(surface)
		SDL_FreeSurface(surface);
	surface = nullptr;
}

void Text::Render(int cameraX, int cameraY) {
	SDL_Rect* dstRect = new SDL_Rect {(int)box.x - cameraX, (int)box.y - cameraY, (int)box.w, (int)box.h};
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture,
				   nullptr, dstRect);
	delete dstRect;
}

void Text::SetFontSize(int fontSize) {
	Text::fontSize = fontSize;
	texture = RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	Text::style = style;
	texture = RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	Text::color = color;
	texture = RemakeTexture();
}

void Text::SetText(std::string text) {
	Text::text = text;
	texture = RemakeTexture();
}

void Text::SetPos(int x, int y, bool centerX, bool centerY) {
	if(centerX)
		box.x = x - (box.w/2);
	else
		box.x = x;
	if(centerY)
		box.y = y - (box.h/2);
	else
		box.y = y;
}

SDL_Texture* Text::RemakeTexture() {
	SDL_Texture* newTexture;
	if(surface)
		SDL_FreeSurface(surface);
	if(style == SOLID) {
		surface = TTF_RenderText_Solid(font, text.c_str(), color);
	}
	if(style == SHADED) {
		surface = TTF_RenderText_Shaded(font, text.c_str(), color, SDL_Color {0, 0, 0, 0});
	}
	if(style == BLENDED) {
		surface = TTF_RenderText_Blended(font, text.c_str(), color);
	}
	box.w = surface->w;
	box.h = surface->h;
	newTexture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_FreeSurface(surface);
	return newTexture;
}
