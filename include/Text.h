#ifndef TEXT_H_
#define TEXT_H_

#include "Resources.h"
#include "Game.h"
#include <SDL.h>

namespace Text
{
	SDL_Texture* GetText(std::string fontFile, int fontSize,
						 SDL_Color textColor, std::string text, int lineWidth=500);
}

#endif /* TEXT_H_ */
