#include "DialogWindow.h"

DialogWindow::DialogWindow(int posX, int posY, int w, int h, std::string texto){
	sp = Sprite("window.png");

	box.x = posX;
	box.y = posY;
	box.w = w;
	box.h = h;

	dialog = Text("Raleway-Light.ttf", 12, Text::BLENDED, SDL_Color {255, 255, 255}, texto, box.x, box.y);
}

void DialogWindow::Update(float dt){

}

void DialogWindow::Render(int cameraX, int cameraY){
	Window::Render();
	dialog.Render(cameraX, cameraY);
}