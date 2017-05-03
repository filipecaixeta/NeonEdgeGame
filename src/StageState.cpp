#include "StageState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"

TileMap* StageState::tileMap;
std::vector<std::unique_ptr<GameObject>> StageState::objectArray;

StageState::StageState() {
	srand(time(NULL));
    tileSet = new TileSet(64, 64, "tileset3d2.png", 9, 9);
	tileMap = new TileMap("resources/map/tileMap.txt", tileSet);
	objectArray = std::vector<std::unique_ptr<GameObject>>();
	AddObject(new Godofredo(66, 1280));
	AddObject(new Notfredo(800, 1280));
	Camera::GetInstance().Follow(Godofredo::player);
}

StageState::~StageState() {
	music.Stop();
	objectArray.clear();
	delete tileMap;
}

void StageState::AddObject(GameObject* ptr) {
	objectArray.emplace_back(ptr);
}

void StageState::AddObjectAsFirst(GameObject* ptr) {
	objectArray.emplace(objectArray.begin(), ptr);
}

void StageState::RemoveObject(GameObject* ptr) {
	for(unsigned i = 0; i < objectArray.size(); i++) {
		if(ptr == objectArray.at(i)->get()) {
			objectArray.erase(objectArray.begin()+i);
			break;
		}
	}
}

bool StageState::IsColliding(Rect a, Rect b) {
	return (((a.x+a.w >= b.x) && (a.x <= b.x+b.w)) && ((a.y+a.h >= b.y) && (a.y <= b.y+b.h)));
}

TileMap* StageState::GetTileMap() {
	return tileMap;
}

void StageState::Pause() {
	paused = true;
}

void StageState::Resume() {
	paused = false;
}

void StageState::LoadAssets() {
    music.Open("stageState.ogg");
    bg.Open("LancelotIdleLeft.png");
    bg.Open("LancelotIdleRight.png");
    bg.Open("LancelotRunningLeft.png");
    bg.Open("LancelotRunningRight.png");
    bg.Open("LancelotHiddenLeft.png");
    bg.Open("LancelotHiddenRight.png");
    bg.Open("LancelotRunningLeftInv.png");
    bg.Open("LancelotRunningRightInv.png");
    bg.Open("notattack.png");
    bg.Open("healthBar.png");
    bg.Open("stealthBar.png");
    bg.Open("NotfredoIdleLeft.png");
    bg.Open("NotfredoIdleRight.png");
    bg.Open("NotfredoRunningLeft.png");
    bg.Open("NotfredoRunningRight.png");
    bg.Open("tileset3d2.png");
	music.Play(-1);
}

void StageState::Update() {
	if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE))
		quitRequested = true;
		Game::GetInstance().RemoveState();
        Game::GetInstance().AddState(new MainMenuState());
	if(InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
		if(paused)
			Resume();
		else
			Pause();
	}
	if(!paused){
		for(unsigned i = 0; i < objectArray.size(); i++) {
			objectArray.at(i)->Update(Game::GetInstance().GetDeltaTime());
		}
		for(unsigned i = 0; i < objectArray.size(); i++) {
			for(unsigned j = i+1; j < objectArray.size(); j++) {
				if(objectArray.at(j)->get()->Is("Animation")) {

				}
				else if(IsColliding(objectArray.at(i)->get()->box, objectArray.at(j)->get()->box)) {
					objectArray.at(i)->get()->NotifyCollision(objectArray.at(j)->get());
					objectArray.at(j)->get()->NotifyCollision(objectArray.at(i)->get());
				}
			}
		}
		for(unsigned i = 0; i < objectArray.size(); i++) {
			if(objectArray.at(i)->get()->IsDead()) {
				if(objectArray.at(i)->get() == Camera::GetInstance().GetFocus()) {
					Camera::GetInstance().Unfollow();
				}
				objectArray.erase(objectArray.begin()+i);
			}
		}
		Camera::GetInstance().Update(Game::GetInstance().GetDeltaTime());
	}
}

void StageState::Render() {
	tileMap->RenderLayer(0, Camera::GetInstance().pos.x, Camera::GetInstance().pos.y);
	for(unsigned int i = 0; i < objectArray.size(); i++)
		objectArray.at(i)->get()->Render();
	tileMap->RenderLayer(1, Camera::GetInstance().pos.x, Camera::GetInstance().pos.y);
}

bool StageState::QuitRequested() {
	return quitRequested;
}

bool StageState::Is(std::string type) {
	return (type == "Stage");
}

StageState* StageState::get() {
	return this;
}
