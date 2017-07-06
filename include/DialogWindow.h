#ifndef DIALOGWINDOW_H_
#define DIALOGWINDOW_H_

#include <string>
#include <vector>

#include "Window.h"
#include "Sprite.h"
#include "Text.h"

class DialogWindow: public Window{
public:
	DialogWindow(int posX, int posY, std::string texto, std::string charName, std::string spriteRetrato);
	void Update(float dt);
	void Render(int cameraX = 0, int cameraY = 0);

private:
	std::vector<SDL_Texture*> textArray;
    SDL_Texture* nameTexture;
    Sprite* characterName;
	std::vector<Sprite*> dialog;
	SDL_Color fontColor = {255,255,255,255};
	int fontSize = 24;
	std::string fontName;
    Sprite face;

};

#endif
