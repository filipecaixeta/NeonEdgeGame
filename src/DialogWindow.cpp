#include "DialogWindow.h"
#include "Game.h"
#include <iostream>

DialogWindow::DialogWindow(int posX, int posY, int w, int h, std::string texto,std::string nomePersonagem,std::string facePersonagem){
	fontName = "Raleway-Light.ttf";
	sp = Sprite("window.png");
    face = Sprite(facePersonagem.c_str());

	box.x = posX;
	box.y = posY;
	box.w = w;
	box.h = h;

	textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,texto, w - posX));
	dialog.emplace_back(new Sprite(textArray.at(0), 1, 0, true));
    characterNameArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,nomePersonagem,w-posX));
    characterName.emplace_back(new Sprite(characterNameArray.at(0),1,0,true));
}

void DialogWindow::Update(float dt){
}

void DialogWindow::Render(int cameraX, int cameraY){
	int sizex = (box.w - box.x)/WINDOWPIECE;
	int sizey = (box.h - box.y)/WINDOWPIECE;

	for(int i = 0; i < sizex; i++)
	{
		for(int j = 0; j < sizey; j++)
		{
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
	for(unsigned int i = 0; i < dialog.size(); i++)
		dialog.at(i)->Render(box.x + 4 - cameraX, box.y + 4 - cameraY);
    for(unsigned int j = 0; j < characterName.size();j++)
    {
        characterName.at(j)->Render(box.x-cameraX,box.y-cameraY);
    }


}
