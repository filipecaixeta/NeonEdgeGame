#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include <memory>
#include <string>
#include <utility>

#include "State.h"
#include "Room.h"
#include "Window.h"
#include "LoadingBar.h"
#include "menu/MenuState.h"
#include "MapAlgorithm.h"
#include "Player.h"
#include "ItemsManager.h"

class ItemsManager;

class StageState : public State
{
private:
    static Room* currentRoom;

    TileSet* tileSet;
    TileSet* background;
    bool paused;
    std::vector<std::unique_ptr<Window>> windowArray;
    LoadingBar *healthBar;
    LoadingBar *energyBar;
    int roomSizeX, roomSizeY, currentRoomX, currentRoomY;

    void HandleInput();
    //void UpdateRoom();
    void UpdateGame();
    void CleanUpdateBars();

public:
    StageState(std::string fase = "cidadeLancelot", std::string background = "background.png");
    ~StageState();

    static GameObject* GetPlayer();
    static void SetPlayer(Player* ptr);
    static void KillPlayer();
    static void AddObject(GameObject* ptr);
    static void AddObjectAsFirst(GameObject* ptr);
    static void RemoveObject(GameObject* ptr);
    static Room* GetCurrentRoom();
    static std::string GetFase();
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
    //void CreateMap(int sizeX, int sizeY);
    //void MassLoad(int sizeX, int sizeY);

    State* inGameMenu;
    State* inGamePause;
    static Player* player;
    static std::string stage;
    Sprite itemHotBarSp;
    Sprite bek;
};

#endif /* STAGESTATE_H_ */
