#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"

TitleState::TitleState() {
	bg2.Open("resources/img/title2.png");
	bgTimer = Timer(500);
	bgTimer.Start();
	bgBool = true;
}

TitleState::~TitleState() {

}

void TitleState::LoadAssets() {
	music.Open("resources/audio/stageState.ogg");
	bg.Open("resources/img/LancelotIdleLeft.png");
	bg.Open("resources/img/LancelotIdleRight.png");
	bg.Open("resources/img/LancelotRunningLeft.png");
	bg.Open("resources/img/LancelotRunningRight.png");
	bg.Open("resources/img/LancelotHiddenLeft.png");
	bg.Open("resources/img/LancelotHiddenRight.png");
	bg.Open("resources/img/LancelotRunningLeftInv.png");
	bg.Open("resources/img/LancelotRunningRightInv.png");
	bg.Open("resources/img/notattack.png");
	bg.Open("resources/img/healthBar.png");
	bg.Open("resources/img/stealthBar.png");
	bg.Open("resources/img/NotfredoIdleLeft.png");
	bg.Open("resources/img/NotfredoIdleRight.png");
	bg.Open("resources/img/NotfredoRunningLeft.png");
	bg.Open("resources/img/NotfredoRunningRight.png");
	bg.Open("resources/img/tileset3d2.png");
	bg.Open("resources/img/title1.png");
}

void TitleState::Update() {
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		quitRequested = true;
		Game::GetInstance().RemoveState();
		Game::GetInstance().AddState(new StageState());
	}
	if(bgTimer.GetTime() < bgTimer.GetLimit()) {
		bgTimer.Update(Game::GetInstance().GetDeltaTime());
	}else{
		bgTimer.Start();
		bgBool = !bgBool;
	}

}

void TitleState::Render() {
	if(bgBool)
		bg.Render(0, 0);
	bg2.Render(0, 160);
}

bool TitleState::QuitRequested() {
	return quitRequested;
}

bool TitleState::Is(std::string type) {
	return (type == "Title");
}

TitleState* TitleState::get() {
	return this;
}

