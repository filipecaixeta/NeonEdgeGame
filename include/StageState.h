#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include <memory>
#include <string>
#include <utility>

#include "State.h"
#include "Lancelot.h"
#include "Gallahad.h"
#include "Notfredo.h"
#include "Window.h"
#include "LoadingBar.h"
#include "menu/MenuState.h"

class StageState : public State
{
private:
	std::string mode;
	TileSet* tileSet;
	bool paused;

	TileMap* tileMap;
	static GameObject* player;
	static std::vector<GameObject*> objectArray;
	std::vector<std::unique_ptr<Window>> windowArray;
	std::unordered_map<int, TileMap*> roomTable;
	int** roomArray;
	std::vector<int> roomOrder;
	LoadingBar healthBar;
	State* inGameMenu;

public:
	StageState(std::string mode_, int sizeX = 10, int sizeY = 10);
	~StageState();

	static GameObject* GetPlayer();
	static void AddObject(GameObject* ptr);
	static void AddObjectAsFirst(GameObject* ptr);
	static void RemoveObject(GameObject* ptr);
	void AddWindow(Window* ptr);
	void RemoveWindow(Window* ptr);

	void Pause();
	void Resume();
	void LoadAssets();
	void Update();
	void Render();
	bool QuitRequested();
	bool Is(std::string type);
	StageState* get();
	void HandleInput();
	void UpdateGame();
};

#endif /* STAGESTATE_H_ */
