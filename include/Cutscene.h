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
	std::vector<CutsceneObject*> objs;
	DialogWindow* textBox;

public:
	Cutscene(int index);
	~Cutscene();
	void LoadAssets();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif