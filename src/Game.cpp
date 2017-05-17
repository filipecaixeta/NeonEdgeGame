#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>
#include <menu/MainMenu.h>

Game* Game::instance = nullptr;

Game::Game(std::string title) {
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

    SDL_Point screenSize = GetFullScreenSize();

    int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenSize.x, screenSize.y, flags);
	if(!window) {
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

    // Antialiasing
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    SetScreenSize(screenSize);
    setFullScreen(false);

	storedState = nullptr;
	AddState(new MainMenu());
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

void Game::UpdateState()
{
	storedState = stateStack.top();
	storedState->LoadAssets();
}

void Game::AddState(State* state) {
	stateStack.emplace(state);
}

void Game::RemoveState() {
	stateStack.pop();
	delete storedState;
}

void Game::CalculateDeltaTime() {
	dt = SDL_GetTicks() - frameStart;
    frameStart = frameStart + dt;
}

SDL_Point Game::GetFullScreenSize()
{
    const SDL_Point res21x9 = {1792,768}; // 21/9 = 2.33
    const SDL_Point res16x9 = {1360,768}; // 16/9 = 1.78
    const SDL_Point res4x3 = {1024,768}; // 4/3 = 1.33

    SDL_Rect r;
    if (SDL_GetDisplayBounds(0, &r) != 0)
    {
        return res4x3;
    }
    if (((float)r.w/(float)r.h)>=2.3)
    {
        // 21x9
        return res21x9;
    }
    else if (((float)r.w/(float)r.h)>=1.6)
    {
        // 16x9 16x10
        return res16x9;
    }
    else
    {
        // 4x3 5x4 3x2
        return res4x3;
    }
}

SDL_Point Game::GetScreenSize()
{
    return screenSize;
}

void Game::setFullScreen(bool b)
{
    fullScreen = b;
    SDL_SetWindowFullscreen(window,(fullScreen?SDL_WINDOW_FULLSCREEN_DESKTOP:0));
}

bool Game::isFullScreen()
{
    return fullScreen;
}

void Game::SetScreenSize(SDL_Point size)
{
    screenSize = size;
    SDL_RenderSetLogicalSize(renderer, size.x, size.y);
}

int Game::GetDeltaTime() {
	return dt;
}

void Game::Run() {
	storedState = stateStack.top();
	storedState->LoadAssets();
	while(!InputManager::GetInstance().QuitRequested()) {
		while(storedState->QuitRequested() == false &&
			  InputManager::GetInstance().QuitRequested() == false &&
			  storedState == stateStack.top())
		{
			CalculateDeltaTime();
			if(SDL_RenderClear(renderer))
				printf("SDL_RenderClear failed: %s\n", SDL_GetError());
			InputManager::GetInstance().Update();
			storedState->Update();
			storedState->Render();
			SDL_RenderPresent(renderer);
			SDL_Delay(33);
		}
		if (storedState != stateStack.top())
		{
			UpdateState();
		}
		else if(storedState->QuitRequested())
		{
			RemoveState();
			if (stateStack.size()==0)
				break;
			storedState = stateStack.top();
		}
	}
}
