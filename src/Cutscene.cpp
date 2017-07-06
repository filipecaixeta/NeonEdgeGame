#include "Cutscene.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>

Cutscene::Cutscene(int index){
	CutsceneObject aux;
	std::string vazia = std::string();
	fontName = "Sabo-Filled.ttf";

	switch(index){
		case 0:
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"\"Only the rightful king of the britains can pull the sword from the stone.\"", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"With the newfound gift of immortality, King Arthur brought peace to the whole continent.", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"A new age of technological advancements and prosperity was known far and wide, with the Knights of The Round Table helping the king shape a brighter future.", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"But now ...", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"The original Knights are long gone. An elite soldier squad took upon their place and their names, no longer acting as counselors, but as enforcers of the king and the empire.", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"I, Lorran Danton, am the latest knight to hold the title of Lancelot, and with an unwavering faith on King Arthur and his actions I do my job, but i can only hope I'm doing it for the greater good...", 800));
			
			for(int i = 0; i < textArray.size(); i++){
				dialog.emplace_back(new Sprite(textArray.at(i), 1, 0, true));
			}
		break;
	}
}

Cutscene::~Cutscene(){

}


void Cutscene::LoadAssets(){

}

void Cutscene::Update(){
	for(int i = 0; i < objs.size(); i++){
		objs.at(i).sp->Update(Game::GetInstance().GetDeltaTime());
	}

	if(!textBox.empty()){
		textBox.at(0)->Update(Game::GetInstance().GetDeltaTime());
	}

	if(Next()){
		textBox.erase(textBox.begin());
		if(textBox.empty()){
			Game::GetInstance().AddState(new StageState("Lancelot"));
			quitRequested = true;
		}
	}
}

void Cutscene::Render(){
	for(int i = 0; i < objs.size(); i++){
		objs.at(i).sp->Render(objs.at(i).box.x, objs.at(i).box.y);
	}

	for(int i = 0; i < dialog.size(); i++){
		dialog.at(i)->Render(100, 100 + i*108);
	}

	if(!textBox.empty())
		textBox.at(0)->Render();
}

bool Cutscene::Is(std::string type){
	return true;
}

CutsceneObject Cutscene::AddCutsceneObject(std::string sprite, int x, int y){
	CutsceneObject aux;
	aux.sp = new Sprite(sprite);
	aux.box.x = x;
	aux.box.y = y;
	aux.box.w = aux.sp->GetWidth();
	aux.box.h = aux.sp->GetHeight();

	return aux;
}

bool Cutscene::Next(){
	if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
		return true;
	}
	else return false;
}