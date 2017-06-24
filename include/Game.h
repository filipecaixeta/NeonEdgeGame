#ifndef GAME_H_
#define GAME_H_

#include <stack>
#include "StageState.h"

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
	Uint32 nextTime_;

	void CalculateDeltaTime();
    SDL_Point GetFullScreenSize();

public:
	const SDL_Point res21x9 = {1792,768}; // 21/9 = 2.33
	const SDL_Point res16x9 = {1360,768}; // 16/9 = 1.78
	const SDL_Point res4x3 = {1024,768}; // 4/3 = 1.33
	int fps;

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
	void UpdateState();

	void LoadConfigurations();
	void SaveConfigurations();
	Uint32 timeLeft();
};

#endif /* GAME_H_ */
