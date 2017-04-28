#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include "State.h"
#include "StateData.h"

class EndState : public State {
public:
	EndState(StateData results);
	~EndState();
	void LoadAssets();
	void Update();
	void Render();
	bool QuitRequested();
	bool Is(std::string type);
	EndState* get();
};

#endif /* ENDSTATE_H_ */
