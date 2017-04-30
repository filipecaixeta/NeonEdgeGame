#ifndef GAME_H_
#define GAME_H_

#include "MainMenuState.h"
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
    SDL_Point screenSize;
    bool fullScreen = 0;

	void CalculateDeltaTime();
    SDL_Point GetFullScreenSize();

public:
    Game(std::string title);
	~Game();
	static Game& GetInstance();
	SDL_Renderer* GetRenderer();
	State* GetCurrentState();
	void AddState(State* state);
	void RemoveState();
	int GetDeltaTime();
	void Run();
    void SetScreenSize(SDL_Point size);
    SDL_Point GetScreenSize();
    void setFullScreen(bool b);
    bool isFullScreen();
};

#endif /* GAME_H_ */
