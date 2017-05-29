#ifndef DIALOGWINDOW_H_
#define DIALOGWINDOW_H_

#include <string>
#include <vector>

#include "Window.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"

class DialogWindow: public Window{
public:
	DialogWindow(int posX, int posY, int w, int h, std::string texto);
	void Update(float dt);
	void Render(int cameraX = 0, int cameraY = 0);

private:
	void RenderPiece(int posx, int posy, int x, int y, int w, int h);
	std::vector<SDL_Texture*> textArray;
	std::vector<Sprite*> dialog;
	SDL_Color fontColor = {255,255,255,255};
	int fontSize = 24;
	std::string fontName;
	Button okay;
};

#endif
