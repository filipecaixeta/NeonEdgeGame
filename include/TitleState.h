#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "Timer.h"

class TitleState : public State {
private:
	Sprite bg2 = Sprite();
	Timer bgTimer;
	bool bgBool;

public:
	TitleState();
	~TitleState();
	void LoadAssets();
	void Update();
	void Render();
	bool QuitRequested();
	bool Is(std::string type);
	TitleState* get();
};

#endif /* TITLESTATE_H_ */
