#include "DialogWindow.h"

DialogWindow::DialogWindow(int posX, int posY, int w, int h){
	sp = Sprite("window.png");

	box.x = posX;
	box.y = posY;
	box.w = w;
	box.h = h;
}

void DialogWindow::Update(float dt){

}

void DialogWindow::RenderPiece(int posx, int posy, int x, int y, int w, int h){
	sp.SetClip(x, y, w, h);
	sp.Render(posx, posy);
}

void DialogWindow::Render(int cameraX, int cameraY){
	int sizex = (box.w - box.x)/WINDOWPIECE;
	int sizey = (box.h - box.y)/WINDOWPIECE;

	for(int i = 0; i < sizex; i++){
		for(int j = 0; j < sizey; j++){
			if(i == 0 && j == 0)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 0, 0, 32, 32);
			else if(i == 0 && j == sizey - 1)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 0, 32, 32, 64);
			else if(i == sizex - 1 && j == 0)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 32, 0, 64, 32);
			else if(i == sizex - 1 && j == sizey - 1)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 32, 32, 64, 64);
			else if(i == 0 && j < sizey - 1)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 0, 16, 32, 48);
			else if(i < sizex - 1 && j == 0)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 16, 0, 48, 32);
			else if(i == sizex - 1 && j < sizey - 1)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 32, 16, 64, 48);
			else if(i < sizex - 1 && j == sizey - 1)
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 16, 32, 48, 64);
			else
				RenderPiece(box.x + i*WINDOWPIECE - cameraX, box.y + j*WINDOWPIECE - cameraY, 16, 16, 48, 48);
		}
	}
}