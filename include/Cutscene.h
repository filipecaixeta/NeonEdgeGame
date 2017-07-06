#ifndef CUTSCENE_H_
#define CUTSCENE_H_

#include "State.h"
#include "Sprite.h"
#include "Rect.h"
#include "DialogWindow.h"
#include <vector>
#include <string>

struct CutsceneObject
{
	Sprite* sp;
	Rect box;
};

class Cutscene : public State{
private:
	std::vector<CutsceneObject> objs;
	std::vector<DialogWindow*> textBox;
	std::vector<SDL_Texture*> textArray;
	std::vector<Sprite*> dialog;
	SDL_Color fontColor = {255,255,255,255};
	int fontSize = 16;
	std::string fontName;
	int index;
	bool textOnly;
	bool Next();

public:
	Cutscene(int index, bool textOnly = false);
	~Cutscene();
	void LoadAssets();
	void Update();
	void Render();
	bool Is(std::string type);
    CutsceneObject AddCutsceneObject(std::string sprite, int x, int y,bool mirror);
};

#endif
