#include "Cutscene.h"

Cutscene::Cutscene(int index){
	CutsceneObject aux;

	switch(index){
		case 0:
			aux = AddCutsceneObject("TurretIdle.png", 30, 30);
			objs.emplace_back(aux);

			textBox = new DialogWindow(100, 100, "hauheuaehuhaeuhae", "Lancelot", "retrato_lancelot.png");
		break;
	}
}

Cutscene::~Cutscene(){

}


void Cutscene::LoadAssets(){

}

void Cutscene::Update(float dt){
	for(int i = 0; i < objs.size(); i++){
		objs.at(i).sp->Update(dt);
	}
}

void Cutscene::Render(){
	for(int i = 0; i < objs.size(); i++){
		objs.at(i).sp->Render(objs.at(i).box.x, objs.at(i).box.y);
	}

	textBox->Render();
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