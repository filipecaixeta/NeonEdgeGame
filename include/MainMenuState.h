#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "State.h"
#include "Timer.h"

class MainMenuState : public State {
private:
	Sprite bg2 = Sprite();
	Timer bgTimer;
	bool bgBool;

public:
    MainMenuState();
    ~MainMenuState();
	void LoadAssets();
	void Update();
	void Render();
	bool QuitRequested();
	bool Is(std::string type);
    MainMenuState* get();
    void LoadFase1();
};

#endif /* MAINMENUSTATE_H_ */
