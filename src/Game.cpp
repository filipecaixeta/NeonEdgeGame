#include "Game.h"
#include "InputManager.h"
#include "Camera.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
	if(instance) {
		printf("Multiple Instances\n");
		exit(EXIT_FAILURE);
	}else{
		instance = this;
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("SDL_Init failed\n");
		exit(EXIT_FAILURE);
	}

	if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		printf("IMG_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(!Mix_Init(MIX_INIT_OGG)) {
		printf("Mix_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
		printf("Mix_OpenAudio failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(TTF_Init()) {
		printf("TTF_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(!window) {
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	storedState = nullptr;
	AddState(new TitleState());
}

Game::~Game() {
	storedState = nullptr;
	for(unsigned i = 0; i < stateStack.size(); i++) {
			delete stateStack.top();
			stateStack.pop();
	}
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	Resources::ClearFonts();
	Camera::GetInstance().~Camera();
	InputManager::GetInstance().~InputManager();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

Game& Game::GetInstance() {
	return *instance;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State* Game::GetCurrentState() {
	return storedState;
}

void Game::AddState(State* state) {
	stateStack.emplace(state);
}

void Game::RemoveState() {
	stateStack.pop();
}

void Game::CalculateDeltaTime() {
	dt = SDL_GetTicks() - frameStart;
	frameStart = frameStart + dt;
}

int Game::GetDeltaTime() {
	return dt;
}

void Game::Run() {
	storedState = stateStack.top();
	storedState->LoadAssets();
	while(!InputManager::GetInstance().QuitRequested()) {
		while(!storedState->QuitRequested() && !InputManager::GetInstance().QuitRequested()) {
			CalculateDeltaTime();
			if(SDL_RenderClear(renderer))
				printf("SDL_RenderClear failed: %s\n", SDL_GetError());
			InputManager::GetInstance().Update();
			storedState->Update();
			storedState->Render();
			SDL_RenderPresent(renderer);
			SDL_Delay(33);
		}
		if(storedState->QuitRequested()) {
			delete storedState;
			storedState = stateStack.top();
			storedState->LoadAssets();
		}
	}
}
