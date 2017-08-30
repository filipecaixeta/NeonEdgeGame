// Copyright 2013 Thomas Park.

#include "EndState.h"
#include "Game.h"
#include "InputManager.h"

EndState::EndState(StateData results) {
    if (results.playerVitory) {
        bg = Sprite("win.jpg");
    } else {
        bg = Sprite("lose.jpg");
    }
}

EndState::~EndState() {
}

void EndState::LoadAssets() {
}

void EndState::Update() {
    if (InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
        quitRequested = true;
        Game::GetInstance().RemoveState();
        Game::GetInstance().AddState(new StageState("Lancelot"));
    }
}

void EndState::Render() {
    bg.Render(0, 0);
}

bool EndState::QuitRequested() {
    return quitRequested;
}

bool EndState::Is(std::string type) {
    return (type == "End");
}

EndState* EndState::get() {
    return this;
}
