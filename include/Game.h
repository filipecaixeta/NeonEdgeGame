#ifndef GAME_H_
#define GAME_H_

#include "TitleState.h"
#include "StageState.h"
#include "EndState.h"
#include <stack>

class Game {
private:
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;
	std::stack<State*> stateStack;
	int frameStart = 0;
	int dt = 0;

	void CalculateDeltaTime();
public:
	Game(std::string title, int width, int height);
	~Game();
	static Game& GetInstance();
	SDL_Renderer* GetRenderer();
	State* GetCurrentState();
	void AddState(State* state);
	void RemoveState();
	int GetDeltaTime();
	void Run();
};

#endif /* GAME_H_ */
