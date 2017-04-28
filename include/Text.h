#ifndef TEXT_H_
#define TEXT_H_

#include "Resources.h"
#include "Rect.h"

class Text {
public:
	enum TextStyle {SOLID, SHADED, BLENDED};

	Text();
	Text(std::string fontFile, int fontSize, TextStyle style, SDL_Color color, std::string text, int x = 0, int y = 0);
	~Text();
	void Render(int cameraX = 0, int cameraY = 0);
	void SetFontSize(int fontSize);
	void SetStyle(TextStyle style);
	void SetColor(SDL_Color color);
	void SetText(std::string text);
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);

private:
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = nullptr;
	TTF_Font* font = nullptr;
	int fontSize = 0;
	TextStyle style = SOLID;
	SDL_Color color = SDL_Color {0, 0, 0};
	std::string text = "";
	Rect box;

	SDL_Texture* RemakeTexture();
};

#endif /* TEXT_H_ */
