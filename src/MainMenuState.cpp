/**
  * Copyright (c) 2017 Neon Edge
  * File Name: MainMenuState.cpp
  * Header File Name: MainMenuState.h
  * Class Name: MainMenuState
  * Objective: Class responsible for the state of main menu.

*/

#include "MainMenuState.h"
#include "Game.h"
#include "InputManager.h"
#include "Logger.h"

#include <assert.h>

/**
  * Objective: This function is used to apply the routine of components in Menu.
  *
	* @param - none.
  * @return - none.

*/
MainMenuState::MainMenuState() {
	bg2.Open("title2.png");
	Log::instance.info("[Main Menu State] opened the title2.png in backgroud2");

	bg.Open("title1.png");
	Log::instance.info("[Main Menu State] opened the title1.png in backgroud");

	bgTimer = Timer(500);
	bgTimer.Start();
	Log::instance.info("[Main Menu State] The background Timer was started");

	bgBool = true;
}

/**
  * Objective: This function destroy the main menu state.
	*
  * @param - none.
  * @return - none.

*/
MainMenuState::~MainMenuState() {

}

/**
  * Objective: This method is resposible to call and Load the fase 1.
  *
	* @param - none.
  * @return - none.

*/
void MainMenuState::LoadAssets() {
	LoadFase1();
	Log::instance.info("[Main Menu State] The Fase1 was loaded");
}

void MainMenuState::LoadFase1() {

}

/**
  * Objective: This method is resposible to makes the control of the main menu state.
  *
	* @param - none.
  * @return - none.

*/
void MainMenuState::Update() {

    // Restraint the objects that will be instantiated in their respective events.
		if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        quitRequested = true;
				Game::GetInstance().RemoveState();  // Remove the current state.
				Game::GetInstance().AddState(new StageState("Lancelot"));  // Initializing the stage of Lancelot character.
		} else {
			// It does nothing.
		}
    // Restrain the control to end main menu by the key 'q'
    if(InputManager::GetInstance().KeyPress((int)'q')) {
		    quitRequested = true;  //Set to truth the variable that is responsible to receive the request of player about the intention go out of Menu.
				Game::GetInstance().RemoveState();
		} else {
			// It does nothing.
		}
    // Makes the controls of fullScreen by the key 'f'
		if (InputManager::GetInstance().KeyPress((int)'f')) {
		    bool fs = Game::GetInstance().isFullScreen();
				Game::GetInstance().setFullScreen(!fs);
		} else {
			// It does nothing.
		}
	  if (bgTimer.IsRunning()) {
		    bgTimer.Update(Game::GetInstance().GetDeltaTime());
    }
		else {
		    bgTimer.Start();
		    bgBool = !bgBool;
	  }
}

/**
  * Objective: This function is resposible to render the background of main menu.
  *
	* @param - none.
  * @return - none.

*/
void MainMenuState::Render() {

  // Invoke the backgrounds render
	if (bgBool) {
	    bg.Render(0, 0); // Set the position that the background will be rendering.
			Log::instance.info("[Main Menu State] The position of the background was setted");
	} else {
	    // It does nothing.
	}
	bg2.Render(0, 160);
}

/**
  * Objective: This function is resposible to take the request about the end of main menu.
  *
	* @param - none.
  * @return bool quitRequested - The data that inform the end state request.

*/
bool MainMenuState::QuitRequested() {
    assert(quitRequested == true || quitRequested == false);
		// It returns the quit option.
	  return quitRequested;
}

/**
  * Objective: This function confers the type of state.
  *
	* @param - none.
  * @return bool (type == "Title") - Return true if the type is "Title".

*/
bool MainMenuState::Is(std::string type) {
	assert(type != " ");
	return (type == "Title");
}

/**
  * Objective: This function is resposible to return the MainMenuState object.
  *
	* @param - none.
  * @return MainMenuState* this - Return the own object of the class.

*/
MainMenuState* MainMenuState::get() {
	return this;
}
