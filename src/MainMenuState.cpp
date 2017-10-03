/**
    Copyright (c) 2017 Neon Edge
    File Name: MainMenuState.cpp
    Header File Name: MainMenuState.h
    Class Name: MainMenuState
    Objective: Class responsible for the state of main menu.

*/

#include "MainMenuState.h"
#include "Game.h"
#include "InputManager.h"

/**
    Objective: This function is used to apply the routine of components in Menu.
    @param - none.
    @return - none.

*/
MainMenuState::MainMenuState() {
	bg2.OpenFile("title2.png");
	bg.OpenFile("title1.png");
	bgTimer = Timer(500);
	bgTimer.Start();
	bgBool = true;
}

/**
    Objective: This function destroy the main menu state.
    @param - nome.
    @return - none.

*/
MainMenuState::~MainMenuState() {

}

/**
    Objective: This method is resposible to call and Load the fase 1.
    @param - none.
    @return - none.

*/
void MainMenuState::LoadAssets() {
	LoadFase1();
}

void MainMenuState::LoadFase1() {

}

/**
    Objective: This method is resposible to makes the control of the main menu state.
    @param - none.
    @return - none.

*/
void MainMenuState::Update() {

    // Restraint the objects that will be instantiated in their respective events.
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		quitRequested = true;
		Game::GetInstance().RemoveState();  // Remove the current state.
		Game::GetInstance().AddState(new StageState("Lancelot"));  // Initializing the stage of Lancelot character.
	}
    // Restrain the control to end main menu by the key 'q'
	if(InputManager::GetInstance().KeyPress((int)'q')) {
		quitRequested = true;  //Set to truth the variable that is responsible to receive the request of player about the intention go out of Menu.
		Game::GetInstance().RemoveState();
	}
    // Makes the controls of fullScreen by the key 'f'
	if(InputManager::GetInstance().KeyPress((int)'f')) {
		bool fs = Game::GetInstance().isFullScreen();
		Game::GetInstance().setFullScreen(!fs);
	}
	if(bgTimer.IsRunning()) {
		bgTimer.Update(Game::GetInstance().GetDeltaTime());
	}
	else {
		bgTimer.Start();
		bgBool = !bgBool;
	}
}

/**
    Objective: This function is resposible to render the background of main menu.
    @param - nome.
    @return - none.

*/
void MainMenuState::Render() {

    // Invoke the backgrounds render
	if(bgBool){
		bg.RenderTexture(0, 0); // Set the position that the background will be rendering.
	}
	bg2.RenderTexture(0, 160);
}

/**
    Objective: This function is resposible to take the request about the end of main menu.
    @param - none.
    @return bool quitRequested - The data that inform the end state request.

*/
bool MainMenuState::QuitRequested() {
	return quitRequested;
}

/**
    Objective: This function confers the type of state.
    @param - none.
    @return bool (type == "Title") - Return true if the type is "Title".

*/
bool MainMenuState::Is(std::string type) {
	return (type == "Title");
}

/**
    Objective: This function is resposible to return the MainMenuState object.
    @param - none.
    @return MainMenuState* this - Return the own object of the class.

*/
MainMenuState* MainMenuState::get() {
	return this;
}
