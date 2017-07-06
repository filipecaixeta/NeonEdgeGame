#include "DialogWindow.h"
#include "Game.h"
#include <iostream>

DialogWindow::DialogWindow(int posX, int posY, std::string texto,std::string charName, std::string spriteRetrato){
	fontName = "Sabo-Filled.ttf";
	sp = Sprite("window.png");
    if(!spriteRetrato.empty())
    	face = new Sprite(spriteRetrato.c_str(), 8, 80, false, true);
    else
    	face = nullptr;

	box.x = posX;
	box.y = posY;
	box.w = face->GetWidth() + sp.GetWidth();
	box.h = face->GetHeight();

	textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,texto, sp.GetWidth()));
	dialog.emplace_back(new Sprite(textArray.at(0), 1, 0, true));
    nameTexture = Text::GetText(fontName,fontSize,fontColor,charName, sp.GetWidth());
    characterName = new Sprite(nameTexture,1,0,true);
}

void DialogWindow::Update(float dt)
{
    face->Update(dt);
}

void DialogWindow::Render(int cameraX, int cameraY){
	if(face != nullptr)
		face->Render(box.x, box.y);
	sp.Render(box.x + face->GetWidth(), box.y);
	for(unsigned int i = 0; i < dialog.size(); i++)
		dialog.at(i)->Render(372, 547);
    if(face!= nullptr)
    	characterName->Render(367, 512);
}
