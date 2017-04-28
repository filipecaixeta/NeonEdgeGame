#include "EndState.h"
#include "Game.h"
#include "InputManager.h"

EndState::EndState(StateData results) {
	if(results.playerVitory)
		bg = Sprite("resources/img/win.jpg");
	else
		bg = Sprite("resources/img/lose.jpg");
}

EndState::~EndState() {

}

void EndState::LoadAssets() {

}

void EndState::Update() {
	if(InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
		quitRequested = true;
		Game::GetInstance().RemoveState();
		Game::GetInstance().AddState(new StageState());
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
