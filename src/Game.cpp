/**
 * Copyright 2017 Neon Edge Game
 * File Name: Game.cpp
 * Header File Name: Game.h
 * Class Name: Game
 * Objective: it manages the resorces of the engine and provide them to the game.
 */

#include <iostream>
#include <assert.h>
#include <cstdio>
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "menu/MainMenu.h"
#include "Resources.h"

Game *Game::instance = nullptr;  // Initiation pointing to nullptr for improve debuging.

/**
 * Objective: it constructs the Game object.
 *
 * @param String title - responsable to the game window title.
 * @return instace of Game.
 */
Game::Game(std::string title) {
    assert(title[0] != '\0');

    // Check the the existence of others game instances.
    if (instance) {
        printf("Multiple Instances\n");
        exit(EXIT_FAILURE);
    } else {
        instance = this;
    }

    // Try to Initiate SDL_VIDEO SDL_AUDIO AND SDL_TIMER.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf("SDL_Init failed\n");
        exit(EXIT_FAILURE);
    } else {
        // It does nothing.
    }

    // Try to Initiate libraries of image formats.
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF )) {
        printf("IMG_Init failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        // It does nothing.
    }

    // Try to Initiate SDL_MIX.
    if (!Mix_Init(MIX_INIT_OGG)) {
        printf("Mix_Init failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        // It does nothing.
    }

    // Try to open a chanell for the SDL_Mixing librarie.
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        printf("Mix_OpenAudio failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        // It does nothing.
    }

    // Try to init ttf library.
    if (TTF_Init()) {
        printf("TTF_Init failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        // It does nothing.
    }

    SDL_Point screenSize = GetFullScreenSize();  // Get the screen size.

    // Get flags for library opengl and alow high dpi.
    int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

    // Create window with some expecifications.
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screenSize.x, screenSize.y, flags);

    // Check if window has created.
    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        // It does nothing.
    }

    // Create render and set the type of it.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Check if the render was created.
    if (!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        // It does nothing.
    }

    // Configure the Antialiasing.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    // Configure some aspects of screen.
    SetScreenSize(screenSize);
    setFullScreen(false);

    // Configure initial game state.
    storedState = nullptr;
    AddState(new MainMenu());
}

Game::~Game() {
    storedState = nullptr;

    // Clear all states in the state stack.
    for (unsigned i = 0; i < stateStack.size(); i++) {
        delete stateStack.top();
        stateStack.pop();
    }

    // It cleans all resources used in the game.
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();

    // It calls destructor of Camera and InputManager
    Camera::CheckInstance().~Camera();
    InputManager::GetInstance().~InputManager();

    // It shutdown libraries.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

/**
 * Objective: It gets game instance
 *
 * @param none.
 * @return Game* instance - A pointer to the game instance.
 */
Game & Game::GetInstance() {
	assert (instance != nullptr);
    return *instance;
}

/**
 * Objective: Return the render instance.
 *
 * @param none.
 * @return SDL_Renderer* renderer.
 */
SDL_Renderer * Game::GetRenderer() {
	assert (renderer != nullptr);
	return renderer;
}

/**
 * Objective: Return the current game state.
 *
 * @param none.
 * @return State* state - pointer to the current state.
 */
State * Game::GetCurrentState() {
    return storedState;
}

/**
 * Objective: Change the current state.
 *
 * @param none.
 * @return none.
 */
void Game::UpdateState() {
    storedState = stateStack.top();
    storedState->LoadAssets();
}

/**
 * Objective: It does nothing.
 *
 * @param none.
 * @return none.
 */
void Game::LoadConfigurations() {
}


/**
 * Objective: It does nothing.
 *
 * @param none.
 * @return none.
 */
void Game::SaveConfigurations() {
}

/**
 * Objective: Add a new state to the stack of states.
 *
 * @param State* state - pointer to the new state.
 * @return none.
 */
void Game::AddState(State *state) {
    assert(state != nullptr);

    stateStack.emplace(state);

    assert(state != nullptr);
}

/**
 * Objective: Remove the top state form the stack of states.
 *
 * @param none.
 * @return none.
 */
void Game::RemoveState() {
    stateStack.pop();
    delete storedState;
}

/**
 * Objective: Calculate the diference of time passed per frame.
 *
 * @param none.
 * @return none.
 */
void Game::CalculateDeltaTime() {
    deltaTime = SDL_GetTicks() - frameStart;
    frameStart = frameStart + deltaTime;
}

/**
 * Objective: Return the actual size of the window.
 *
 * @param none.
 * @return SDL_point 'size'(return the actual dimension of the screen).
 */
SDL_Point Game::GetFullScreenSize() {
	SDL_Point resolution;
	SDL_Rect rectangle;
    rectangle.x = 0.0f;
    rectangle.y = 0.0f;
    rectangle.w = 0.0f;
    rectangle.h = 0.0f;

    if (SDL_GetDisplayBounds(0, &rectangle) != 0) {
        resolution = resolution_4x3;
    } else {
        // It does nothing.
    }

    if (((float)rectangle.w / (float)rectangle.h) >= 2.3) {
        // 21x9
        resolution = resolution_21x9;
    } else if (((float)rectangle.w / (float)rectangle.h) >= 1.6) {
        // 16x9 16x10
        resolution = resolution_16x9;
    } else {
        // 4x3 5x4 3x2
        resolution = resolution_4x3;
    }

	assert(&resolution != nullptr);
	return resolution;
}

/**
 * Objective: Return the size of the window.
 *
 * @param none.
 * @return SDL_point screenSize.
 */
SDL_Point Game::GetScreenSize() {
	assert(&screenSize != nullptr);
	return screenSize;
}

/**
 * Objective: Set FullScreen for the game window.
 *
 * @param none.
 * @return none.
 */
void Game::setFullScreen(bool isFullScreen) {
    assert(isFullScreen == true || isFullScreen == false);

    fullScreen = isFullScreen;
    int fullScreenMode = 0;
    if (fullScreen) {
        fullScreenMode = SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else {
        fullScreenMode = 0;
    }

    SDL_SetWindowFullscreen(window, fullScreenMode);
}

/**
 * Objective: Check if Screen is in full screen mode.
 *
 * @param none.
 * @return bool FullScreen
 */
bool Game::isFullScreen(){
	assert(!fullScreen || fullScreen);
    return fullScreen;
}

/**
 * Objective: Set the game screen size.
 *
 * @param SDL_Point size - the size to be scalable.
 * @return none.
 */
void Game::SetScreenSize(SDL_Point size) {
    assert(INT_MIN_SIZE <= size.x && size.x <= INT_MAX_SIZE ||
           INT_MIN_SIZE <= size.y && size.y <= INT_MAX_SIZE);

    screenSize = size;
    SDL_SetWindowSize(window, size.x, size.y);
    SDL_RenderSetLogicalSize(renderer, size.x, size.y);
}

/**
 * Objective: Retunrn the diference of time per frame.
 *
 * @param none.
 * @return int deltaTime - time in micro seconds.
 */
int Game::GetDeltaTime() {
	assert(deltaTime > 0);
	return deltaTime;
}

/**
 * Objective:Return the time left to end the frame
 *
 * @param none.
 * @return Uint32 time (0 if the time is more then the desirable, and just the time if not.)
 */
Uint32 Game::timeLeft() {
	Uint32 timeLeft = 0;
	Uint32 now = SDL_GetTicks();

	if (nextTime_ > now) {
        timeLeft = nextTime_ - now;
    }

	assert(timeLeft > 0);
	return timeLeft;
}

/**
 * Objective: Start the game main loop and manage the games resources.
 *
 * @param none.
 * @return none.
 */
void Game::Run() {
    // Start main loop.
    while (!InputManager::GetInstance().QuitRequested()) {
    storedState = stateStack.top();  // Get the top state.
    storedState->LoadAssets();  // Load resources of the current state.
        // Quit the game if catch a quit request.
        while (storedState->QuitRequested() == false &&
               InputManager::GetInstance().QuitRequested() == false &&
               storedState == stateStack.top()) {
            CalculateDeltaTime();  // Calculate the times between frames

            // Clear the render screen.
            if (SDL_RenderClear(renderer)) {
                printf("SDL_RenderClear failed: %s\n", SDL_GetError());
            } else {
                // It does nothing.
            }
            InputManager::GetInstance().Update();  // Get all inputs.

            // Update the scene and re-draw screen.
            storedState->Update();
            storedState->Render();
            SDL_RenderPresent(renderer);

            nextTime_ = SDL_GetTicks() + 1000.0 / framesPerSecond;  // set frame rate.

            // Apply framesPerSecond
            SDL_Delay(timeLeft());
            nextTime_ += 1000 / framesPerSecond;
        }

        // Check change of the current state.
        if (storedState != stateStack.top()) {
            UpdateState();
        } else if (storedState->QuitRequested()) {  // Check  for a quit request.
            RemoveState();
            if (stateStack.size() == 0) {
                break;
            } else {
                // It does nothing.
            }
            storedState = stateStack.top();
        }
    }
}
