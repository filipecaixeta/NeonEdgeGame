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
	int const INITIAL_VALUE = 0;
	std::vector<CutsceneObject> objs;
	std::vector<DialogWindow*> textBox;
	std::vector<SDL_Texture*> textArray;
	std::vector<Sprite*> dialog;
	SDL_Color fontColor = {255,255,255,255};
	int fontSize = 16;
	std::string fontName = "";
	int index = INITIAL_VALUE;
	bool textOnly = false;
	bool Next();

public:
	Cutscene(int index, bool textOnly = false);
	~Cutscene();
	void LoadAssets();
	void Update();
	void Render();
	bool Is(std::string type);
    void AddCutsceneObject(std::string sprite, int x, int y,bool mirror, float frameTime = 0, int frameCount = 1);
};

#endif
