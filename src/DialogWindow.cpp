#include "DialogWindow.h"
#include "Game.h"
#include <iostream>

DialogWindow::DialogWindow(int posX, int posY, int w, int h, std::string texto){
	fontName = "Raleway-Light.ttf";
	sp = Sprite("window.png");

	box.x = posX;
	box.y = posY;
	box.w = w;
	box.h = h;

	//dialog = Text("Raleway-Light.ttf", 12, Text::BLENDED, SDL_Color {255, 255, 255}, texto, box.x, box.y);

	text = Resources::GetText(Game::GetInstance().GetRenderer(), texto, fontName, fontSize, fontColor);
	dialog = new Sprite(text, 1, 0, true);
}

void DialogWindow::Update(float dt){

}

void DialogWindow::Render(int cameraX, int cameraY){
	std::cout << "renderizou a DialogWindow\n";
	int sizex = (box.w - box.x)/WINDOWPIECE;
	int sizey = (box.h - box.y)/WINDOWPIECE;

	for(int i = 0; i < sizex; i++){
		for(int j = 0; j < sizey; j++){
			if(i == 0 && j == 0)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 0, 0, 32, 32);
			else if(i == 0 && j == sizey - 1)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 0, 32, 32, 64);
			else if(i == sizex - 1 && j == 0)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 32, 0, 64, 32);
			else if(i == sizex - 1 && j == sizey - 1)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 32, 32, 64, 64);
			else if(i == 0 && j < sizey - 1)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 0, 16, 32, 48);
			else if(i < sizex - 1 && j == 0)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 16, 0, 48, 32);
			else if(i == sizex - 1 && j < sizey - 1)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 32, 16, 64, 48);
			else if(i < sizex - 1 && j == sizey - 1)
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 16, 32, 48, 64);
			else
				Window::RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 16, 16, 48, 48);
		}
	}
	dialog->Render(box.x - cameraX, box.y - cameraY);
}
