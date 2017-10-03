/**
    Copyright (c) 2017 Neon Edge Game.
    File Name: EndState.cpp
    Header File Name: EndState.h
    Class Name: EndState
    Objective: its manages player at the end of current map.

*/

#include "EndState.h"
#include "Game.h"
#include "InputManager.h"

/**
    Objective: it constructs Gallahad graphics component object.
    @param StateData results - final result of player on current map.
    @return none.

*/
EndState::EndState(StateData results) {
    // It verifies if the player won at the end of the map
    if (results.playerVitory) {
        // If yes, it turns the sprite picture to win to be shown on the screen.
        bg = Sprite("win.jpg");
    } else {
        // Else, it turns the sprite picture to lose to be shown on the screen.
        bg = Sprite("lose.jpg");
    }
}

/**
    Objective: it destroys gallahad graphics component object.
    @param none.
    @return none.

*/
EndState::~EndState() {
}

/**
    Objective: it does nothing.
    @param none.
    @return none.

*/
void EndState::LoadAssets() {
}

/**
    Objective: it updates the character when there is a map exchange.
    @param none.
    @return none.

*/
void EndState::Update() {
    // It verifies the pressed key.
    if (InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
        quitRequested = true;  // It turns the quit requested in true to quit of current map.
        Game::GetInstance().RemoveState();  // Remove the current character.
        Game::GetInstance().AddState(new StageState("Lancelot"));  // Create the new character
                                                                   // to play with it.
    }
}

/**
    Objective: it renders position of sprite to position 0, 0 of map.
    @param none.
    @return none.

*/
void EndState::Render() {
    bg.RenderTexture(0, 0);
}

/**
    Objective: it verifies if quit was requested to quit the current map.
    @param none.
    @return bool quitRequested - variable to store quit option.

*/
bool EndState::QuitRequested() {
    return quitRequested;  // It returns the quit option.
}

/**
    Objective: it verifies if the player ends the map.
    @param string type - place where player is.
    @return bool 'type == "End"' - showing if player is at the end of map.

*/
bool EndState::Is(std::string type) {
    return (type == "End");  // True when player ends map.
}

/**
    Objective: it gets object of end state.
    @param none.
    @return EndState 'this' - the end state object.

*/
EndState * EndState::get() {
    return this;
}
