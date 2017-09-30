/**
    Copyright 2017 Neon Edge Game
    File Name: Game.cpp
    Header File Name: Game.h
    Class Name: Game
    Objective: The objective of this class is to manage the resorces of the engine and provide them to the game.

*/

#include <iostream>
#include <cstdio>
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "menu/MainMenu.h"
#include "Resources.h"

Game* Game::instance = nullptr; // initiate pointing to nullptr for improve debuging.

/**
    Objective: The objective osf this funtion is construct the class game, iniciating the sdl libraries.
    @param: String title - responsable to the game window title.
    @return: the instace of the class Game.

*/
Game::Game(std::string title) {
    //Check the the existence of others game instances.
    if (instance) {
        printf("Multiple Instances\n");
        exit(EXIT_FAILURE);
    } else {
        instance = this;
    }

    //Try to Initiate SDL_VIDEO SDL_AUDIO AND SDL_TIMER.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf("SDL_Init failed\n");
        exit(EXIT_FAILURE);
    }

    //Try to Initiate libraries of image formats.
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF )) {
        printf("IMG_Init failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Try to Initiate SDL_MIX.
    if (!Mix_Init(MIX_INIT_OGG)) {
        printf("Mix_Init failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Try to open a chanell for the SDL_Mixing librarie.
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        printf("Mix_OpenAudio failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Try to init ttf library.
    if (TTF_Init()) {
        printf("TTF_Init failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    fps = 60; // Frames per second of the game.
    nextTime_ = 0;// Variable to get a time step.

    SDL_Point screenSize = GetFullScreenSize();// Get the screen size.

    int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;//get flags for library opengl and alow high dpi.

    //Create window with some expecifications.
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screenSize.x, screenSize.y, flags);

    //Check if window has created.
    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//Create render and set the type of it.

    //Check if the render was created.
    if (!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Configure the Antialiasing.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    //Configure some aspects of screen.
    SetScreenSize(screenSize);
    setFullScreen(false);

    //Configure initial game state.
    storedState = nullptr;
    AddState(new MainMenu());
}

/**
    Function Objective: Destroct the class Game, delocalizing some memory used in the class and shutdown dependent libraries.
    @param None.
    @return: Return free memory to the system.

*/
Game::~Game() {
    storedState = nullptr;

    // Clear all states in the state stack.
    for (unsigned i = 0; i < stateStack.size(); i++) {
        delete stateStack.top();
        stateStack.pop();
    }

    //Clear all resources used in the game.
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();

    //Call destructor of Camera and InputManager
    Camera::CheckInstance().~Camera();
    InputManager::GetInstance().~InputManager();

    //Shutdown libraries.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

/**
    Objective: Return the game instance
    @param None.
    @return Game* instance - A pointer to the game instance.

*/
Game& Game::GetInstance() {
    return *instance;
}

/**
    Objective: Return the render instance.
    @param None.
    @return SDL_Renderer* renderer.

*/
SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

/**
    Objective: Return the current game state.
    @param None.
    @return: State* state - pointer to the current state.

*/
State* Game::GetCurrentState() {
    return storedState;
}

/**
    Objective: Change the current state.
    @param None.
    @return: void

*/
void Game::UpdateState() {
    storedState = stateStack.top();
    storedState->LoadAssets();
}

/**
    Objective: Load the configuration of the game.
    @param None.
    @return: void

*/
void Game::LoadConfigurations() {
    // TODO: Check why this funciton is commented.
    /*
        Load Game::screenSize
        Load Game::fps
        Load Game::fullScreenMode
        Load inputmanager::translationTable
    */
}


/**
  Objective: Save the new configuration.
  @param None.
  @return: Void.

*/
void Game::SaveConfigurations() {
    // TODO: Check why this funciton is commented.
    /*
        Save Game::screenSize
        Save Game::fps
        Save Game::fullScreenMode
        Save inputmanager::translationTable
    */
}

/**
  Objective: Add a new state to the stack of states.
  @param: State* state - pointer to the new state.
  @return: void.

*/
void Game::AddState(State* state) {
    stateStack.emplace(state);
}

/**
  Objective: Remove the top state form the stack of states.
  @param None.
  @return void.

*/
void Game::RemoveState() {
    stateStack.pop();
    delete storedState;
}

/**
  Objective: Calculate the diference of time passed per frame.
  @param None
  @return: void.

*/
void Game::CalculateDeltaTime() {
    dt = SDL_GetTicks() - frameStart;
    frameStart = frameStart + dt;
}

/**
  Objective: Return the actual size of the window.
  @param None
  @return: SDL_point 'size'(return the actual dimension of the screen).

*/
SDL_Point Game::GetFullScreenSize() {
    SDL_Rect r;
    if (SDL_GetDisplayBounds(0, &r) != 0) {
        return res4x3;
    }
    if (((float)r.w / (float)r.h) >= 2.3) {
        // 21x9
        return res21x9;
    } else if (((float)r.w / (float)r.h) >= 1.6) {
        // 16x9 16x10
        return res16x9;
    } else {
        // 4x3 5x4 3x2
        return res4x3;
    }
}

/**
  Objective: Return the size of the window.
  @param None
  @return SDL_point screenSize.

*/
SDL_Point Game::GetScreenSize() {
    return screenSize;
}

/**
  Objective: Set FullScreen for the game window.
  @param None
  @return Void.

*/
void Game::setFullScreen(bool b) {
    fullScreen = b;
    SDL_SetWindowFullscreen(window, (fullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
}

/**
  Function objective: Check if Screen is in full screen mode.
  @param None
  @return bool FullScreen

*/
bool Game::isFullScreen() {
    return fullScreen;
}

/**
  Objective: Set the game screen size.
  @param SDL_Point size - the size to be scalable.
  @return None.

*/
void Game::SetScreenSize(SDL_Point size) {
    screenSize = size;
    SDL_SetWindowSize(window, size.x, size.y);
    SDL_RenderSetLogicalSize(renderer, size.x, size.y);
}

/**
  Objective: Retunrn the diference of time per frame.
  @param None
  @return: int dt - time in micro seconds.

*/
int Game::GetDeltaTime() {
    return dt;
}

/**
  Objective:Return the time left to end the frame
  @param None
  @return: Uint32 time (0 if the time is more then the desirable, and just the time if not.)

*/
Uint32 Game::timeLeft() {
    Uint32 now;
    now = SDL_GetTicks();
    if (nextTime_ <= now) {
        return 0;
    } else {
        return nextTime_ - now;
    }
}

/**
  Objective: Start the game main loop and manage the games resources.
  @param None.
  @return: void.

*/
void Game::Run() {
    storedState = stateStack.top();// Get the top state.
    storedState->LoadAssets();// Load resources of the current state.
    nextTime_ = SDL_GetTicks() + 1000.0 / fps;// set frame rate

    //Start main loop.
    while (!InputManager::GetInstance().QuitRequested()) {
        //Quit the game if catch a quit request.
        while (storedState->QuitRequested() == false &&
                InputManager::GetInstance().QuitRequested() == false &&
                storedState == stateStack.top()) {
            CalculateDeltaTime();//Calculate the times between frames

            //Clear the render screen.
            if (SDL_RenderClear(renderer)) {
                printf("SDL_RenderClear failed: %s\n", SDL_GetError());
            }
            InputManager::GetInstance().Update();//Get all inputs.

            //Update the scene and re-draw screen.
            storedState->Update();
            storedState->Render();
            SDL_RenderPresent(renderer);

            // Apply fps
            SDL_Delay(timeLeft());
            nextTime_ += 1000 / fps;
        }

        //Check change of the current state.
        if (storedState != stateStack.top()) {
            UpdateState();
        } else if (storedState->QuitRequested()) { //Check  for a quit request.
            RemoveState();
            if (stateStack.size() == 0) {
                break;
            }
            storedState = stateStack.top();
        }
    }
}
