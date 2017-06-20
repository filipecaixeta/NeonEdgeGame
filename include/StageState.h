#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include <memory>
#include <string>
#include <utility>

#include "State.h"
#include "Energy.h"
#include "Lancelot.h"
#include "Gallahad.h"
#include "Notfredo.h"
#include "Room.h"
#include "Window.h"
#include "LoadingBar.h"
#include "menu/MenuState.h"
#include "MapAlgorithm.h"
#include "Character.h"
#include "ItensManager.h"

class StageState : public State
{
private:
	static Character* player;
	static Room* currentRoom;

	std::string mode;
	TileSet* tileSet;
	bool paused;
	std::vector<std::unique_ptr<Window>> windowArray;
	//std::unordered_map<SDL_Point, TileMap*> roomTable;
	Room*** roomInfo;
	int** roomArray;
	std::vector<int> roomOrder;
	std::vector<std::pair<int, int>> roomWay;
	std::vector<std::pair<int, int>>::iterator it;
	MapAlgorithm algorithm;
	LoadingBar *healthBar;
	LoadingBar *energyBar;
	int sizeX, sizeY, roomSizeX, roomSizeY;

	void HandleInput();
	void UpdateRoom();
	void UpdateGame();
	void CleanUpdateBars();

public:
	StageState(std::string mode_, int sizeX = 10, int sizeY = 10);
	~StageState();

	static GameObject* GetPlayer();
    static Room* GetCurrentRoom();
	static void KillPlayer();
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
	void CreateBars(std::string playerName);
	void CreateMap(int sizeX, int sizeY);
	void MassLoad(int sizeX, int sizeY);

	State* inGameMenu;
	ItensManager* itensManager;

};

#endif /* STAGESTATE_H_ */
