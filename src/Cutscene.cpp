#include "Cutscene.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>

Cutscene::Cutscene(int index, bool textOnly){
	this->index = index;
	CutsceneObject aux;
	std::string vazia = std::string();
	fontName = "Sabo-Filled.ttf";
	this->textOnly = textOnly;

	switch(index){
		case 0:
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"Only the rightful king of the britains can pull the sword from the stone.", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"With the newfound gift of immortality, King Arthur brought peace to the whole continent.", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"A new age of technological advancements and prosperity was known far and wide, with the Knights of The Round Table helping the king shape a brighter future.", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"But now ...", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"The original Knights are long gone. An elite soldier squad took upon their place and their names, no longer acting as counselors, but as enforcers of the king and the empire.", 800));
			textArray.emplace_back(Text::GetText(fontName,fontSize,fontColor,"I, Lorran Danton, am the latest knight to hold the title of Lancelot, and with an unwavering faith on King Arthur and his actions I do my job, but i can only hope Im doing it for the greater good...", 800));
			
			for(int i = 0; i < textArray.size(); i++){
				dialog.emplace_back(new Sprite(textArray.at(i), 1, 0, true));
			}
		break;

        case 1:
			AddCutsceneObject("Introducao.png",0,0,false,100,8);
			textBox.emplace_back(new DialogWindow(58,514,"Lancelot, I have an urgent task for you: the Empire Guard is reporting a rogue A.I. breakout in Crusallias City, Sector 7. I need you on-site to find the source and destroy it.","King Arthur","retrato_arthur.png"));
			textBox.emplace_back(new DialogWindow(58,514,"W-What?! Crusallias is the biggest city on Aragon! Were there casualties? Is the guard caring for the population?","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"It doesnt matter, soldier. The source of the breakout is of utmost importance to the mission, we cant let it stage any other attack against the empire.","King Arthur","retrato_arthur.png"));
			textBox.emplace_back(new DialogWindow(58,514,"...Right. I am on my way, Your Highness.","Lancelot","retrato_lancelot.png"));
        break;

        case 2:
            AddCutsceneObject("Cutscene1.png",0,0,false);
			AddCutsceneObject("LancelotIdle.png",25,400,false,80,8);
			AddCutsceneObject("GallahadIdle.png",375,400,true,80,8);
			textBox.emplace_back(new DialogWindow(58,514,"Knight Galahad? What are you doing here?","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"Calm down, rookie. Im not here to steal your mission or anything. I have more important things to do, like warning you about what happened to these drones.","Galahad","retrato_galahad.png"));
			textBox.emplace_back(new DialogWindow(58,514,"What do you mean? This better not be another one of your tricks.","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"Heh, if only. You were told the bots are going rogue right? Well, they are not. Someone gave them orders to do this, and they came from the Avalon Space Station. Im going to investigate it further.","Galahad","retrato_galahad.png"));
			textBox.emplace_back(new DialogWindow(58,514,"Well, this doesnt make any sense. The only ones who can send out orders from the station are the Knights and King Arthur himself. And every knight except me was assigned to a mission this past week.","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"And Im speaking with you right now, so I guess you have your answer. Ill get going, Lancelot. Do what you must.","Galahad","retrato_galahad.png"));
			textBox.emplace_back(new DialogWindow(58,514,"...","Lancelot","retrato_lancelot.png"));
        break;

        case 3:
            AddCutsceneObject("galahad-sozinha.png",0,0,false);
			AddCutsceneObject("GalahadIdle.png",75,100,false);
			textBox.emplace_back(new DialogWindow(58,514,"The data is mine, now let me see... Wait, what? The logs date back to more than a year ago... They talk about an inaccessible area in Crusallias, and the former Knight Lancelot being killed in action... by a rogue A.I.? This is worse than I imagined, I must investigate the area and call for reinforcements... If someone is behind this, it means Danton... heck, the whole continent should be in danger.","Galahad","retrato_galahad.png"));
        break;

        case 4:
			AddCutsceneObject("GalahadIdle.png",75,100,false);
            AddCutsceneObject("galahad-stage-3.png",0,0,false);
			textBox.emplace_back(new DialogWindow(58,514,"This is the place. I must find out what happened here.","Galahad","retrato_galahad.png"));
        break;

        case 5:
            AddCutsceneObject("galahad-stage-end.png",0,0,false);
			AddCutsceneObject("GalahadIdle.png",175,100,false);
			textBox.emplace_back(new DialogWindow(58,514,"Great, now that i have taken care of the big guy I can hack the local mainframe and learn the truth.","Galahad","retrato_galahad.png"));
			textBox.emplace_back(new DialogWindow(58,514,"...No...","Galahad","retrato_galahad.png"));
			textBox.emplace_back(new DialogWindow(58,514,"I must tell Lancelot about this. The A.I. were ordered to kill by the king himself, It seems like the data I found on the station was true... Arthur sent his knight to die.","Galahad","retrato_galahad.png"));
        break;

        case 6:
			textBox.emplace_back(new DialogWindow(58,514,"Someone is calling me? ...Galahad? What Happened?","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"What...no... I will only believe if i hear it from the king himself.","Lancelot","retrato_lancelot.png"));
        break;

        case 7:
            AddCutsceneObject("lancelot-vs-arthur.png",0,0,false);
			AddCutsceneObject("ArthurIdle.png",75,100,false);
			AddCutsceneObject("LancelotIdle.png",175,100,true);
			textBox.emplace_back(new DialogWindow(58,514,"YOUR HIGHNESS!","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"So, Lancelot, Galahad told you about her little discovery, I suppose? Ive heard everything when I intercepted your communications channel just a moment ago.","King Arthur","retrato_arthur.png"));
			textBox.emplace_back(new DialogWindow(58,514,"W-what? you were spying on us? But if you already know what Im talking about then I need an answer!","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"The only answer you need, soldier, is that I dont tolerate non-believers on my kingdom, doubting my righteousness as the king... Be it you, Galahad, or your predecessor.","King Arthur","retrato_arthur.png"));
			textBox.emplace_back(new DialogWindow(58,514,"So, you killed him.. I believed in you Arthur! I thought we were making a brighter future for everyone. Not feeding them lies! I dont care if you are immortal, I will stop you!","Lancelot","retrato_lancelot.png"));
			textBox.emplace_back(new DialogWindow(58,514,"Danton, you dare to raise your blade against me and the whole kingdom will hunt you down, like the vermin you are! That other traitor, Galahad, is already being dealt with by Knight Mordred. You stand no chance.","King Arthur","retrato_arthur.png"));
			textBox.emplace_back(new DialogWindow(58,514,"En guarde...tyrant.","Lancelot","retrato_lancelot.png"));
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
		if(textOnly == false){
			textBox.erase(textBox.begin());
			if(textBox.empty()){
				if(index == 1)
				{
					//Game::GetInstance().RemoveState();
					Game::GetInstance().AddState(new StageState("cidadeLancelot"));
				}
				if(index == 2)
				{
					//Game::GetInstance().RemoveState();
					Game::GetInstance().AddState(new StageState("naveGalahad"));
				}
				quitRequested = true;
			}
		}
		else{
			dialog.erase(dialog.begin());
			if(dialog.empty()){
				if(index == 0)
				{
					//Game::GetInstance().RemoveState();
					Game::GetInstance().AddState(new Cutscene(1, false));
				}
				quitRequested = true;
			}
		}
	}
}

void Cutscene::Render(){
	for(int i = 0; i < objs.size(); i++){
		objs.at(i).sp->Render(objs.at(i).box.x, objs.at(i).box.y);
	}

	if(!dialog.empty()){
		dialog.at(0)->Render(150,400);
	}

	if(!textBox.empty())
		textBox.at(0)->Render();
}

bool Cutscene::Is(std::string type){
	return true;
}

void Cutscene::AddCutsceneObject(std::string sprite, int x, int y,bool mirror, float frameTime, int frameCount){
	CutsceneObject* aux = new CutsceneObject();
	aux->sp = new Sprite(sprite, frameCount, frameTime, false, false);
    aux->sp->Mirror(mirror);
	Vec2 center = CenterVertical(975)+CenterHorizontal(633);
	std::cerr << center <<std::endl;
	aux->box.x = x+center.x;
	aux->box.y = y+center.y;
	aux->box.w = aux->sp->GetWidth();
	aux->box.h = aux->sp->GetHeight();

	objs.emplace_back(*aux);
}

bool Cutscene::Next(){
	if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
		return true;
	}
	else return false;
}
