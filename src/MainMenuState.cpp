#include "MainMenuState.h"
#include "Game.h"
#include "InputManager.h"

MainMenuState::MainMenuState() {
    bg2.Open("title2.png");
    bg.Open("title1.png");
    bgTimer = Timer(500);
	bgTimer.Start();
	bgBool = true;
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::LoadAssets() {
    LoadFase1();
}

void MainMenuState::LoadFase1() {

}

void MainMenuState::Update() {
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		quitRequested = true;
		Game::GetInstance().RemoveState();
		Game::GetInstance().AddState(new StageState());
	}
    if(InputManager::GetInstance().KeyPress((int)'q')) {
        quitRequested = true;
        Game::GetInstance().RemoveState();
    }
    if(InputManager::GetInstance().KeyPress((int)'f')) {
        bool fs = Game::GetInstance().isFullScreen();
        Game::GetInstance().setFullScreen(!fs);
    }
	if(bgTimer.isRunning()) {
		bgTimer.Update(Game::GetInstance().GetDeltaTime());
	}else{
		bgTimer.Start();
		bgBool = !bgBool;
	}
}

void MainMenuState::Render() {
	if(bgBool)
		bg.Render(0, 0);
	bg2.Render(0, 160);
}

bool MainMenuState::QuitRequested() {
	return quitRequested;
}

bool MainMenuState::Is(std::string type) {
	return (type == "Title");
}

MainMenuState* MainMenuState::get() {
	return this;
}
