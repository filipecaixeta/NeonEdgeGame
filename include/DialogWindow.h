#ifndef DIALOGWINDOW_H_
#define DIALOGWINDOW_H_

#include "Window.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <string>

class DialogWindow: public Window{
public:
	DialogWindow(int posX, int posY, int w, int h, std::string texto);
	void Update(float dt);
	void Render(int cameraX = 0, int cameraY = 0);

private:
	void RenderPiece(int posx, int posy, int x, int y, int w, int h);
	Text dialog;
	Button okay;
};

#endif