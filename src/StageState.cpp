#include <iostream>
#include <ctime>
#include <cstdlib>

#include "StageState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "DialogWindow.h"
#include "SaveComponent.h"
#include "menu/InGamePause.h"
#include "ColisionFunctions.h"

std::string StageState::stage = "";
Player* StageState::player = nullptr;
Room* StageState::currentRoom = nullptr;

StageState::StageState(std::string fase, std::string background):
    State(),
    tileSet(nullptr),
    paused(false),
    windowArray(),
    healthBar(nullptr),
    energyBar(nullptr),
    inGameMenu(nullptr)
{
    this->background = new TileSet(7389, 1711, background, 0, 0);
    tileSet = new TileSet(64, 64, "Tile_Map_Cidade.png", 8, 8);
    currentRoom = new Room(tileSet, 0, Vec2(0,0), this->background,fase);

    if(fase == "cidadeLancelot"){
        this->background = new TileSet(7389, 1711, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Cidade.png", 8, 8);
        currentRoom = new Room(tileSet, 0, Vec2(0,0), this->background,fase);
    }
    else if(fase == "naveGalahad"){
        this->background = new TileSet(1, 1, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Nave.png", 8, 8);
        currentRoom = new Room(tileSet, 1, Vec2(0,0), this->background,fase);
        bek.Open("SpaceBG.png");
    }
    else if(fase == "cidadeGalahad"){
        this->background = new TileSet(7389, 1711, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Cidade.png", 8, 8);
        currentRoom = new Room(tileSet, 2, Vec2(0,0), this->background,fase);
    }
    else if(fase == "naveLancelot"){
        this->background = new TileSet(1, 1, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Nave.png", 8, 8);
        currentRoom = new Room(tileSet, 3, Vec2(0,0), this->background,fase);
        bek.Open("SpaceBG.png");
    }
    Camera::GetInstance().SetPos(Vec2(player->box.x, player->box.y));
    Camera::GetInstance().Follow(player);
    currentRoomX = 0;
    currentRoomY = 0;

    Camera::GetInstance().maxPos = Vec2(currentRoom->GetMap()->GetWidth()*currentRoom->GetMap()->GetTileWidth(),
                                        currentRoom->GetMap()->GetHeight()*currentRoom->GetMap()->GetTileHeight());
    CreateBars(player->name);

    stage = fase;
    itemHotBarSp.Open("menus/"+player->name+"itemhotbar.png");
}

StageState::~StageState()
{
    player = nullptr;
    delete currentRoom;
    music.Stop();
    windowArray.clear();
}

Room* StageState::GetCurrentRoom(){
    return currentRoom;
}

GameObject* StageState::GetPlayer()
{
    return player;
}

void StageState::SetPlayer(Player* ptr)
{
    player = ptr;
}

void StageState::KillPlayer()
{
    player = nullptr;
}

void StageState::AddObject(GameObject* ptr)
{
    currentRoom->AddObject(ptr);
}

void StageState::AddObjectAsFirst(GameObject* ptr)
{
    currentRoom->AddObjectAsFirst(ptr);
}

void StageState::RemoveObject(GameObject* ptr)
{
    currentRoom->RemoveObject(ptr);
}

void StageState::CreateBars(std::string playerName)
{
    healthBar = new LoadingBar("lifebar_"+playerName+".png",11);
    energyBar = new LoadingBar("energybar_"+playerName+".png",174,28,6);
}

void StageState::RemoveWindow(Window* ptr)
{
    windowArray.emplace_back(ptr);
}

void StageState::Pause()
{
    paused = true;
    inGamePause = new InGamePause(this);
    inGameMenu->LoadAssets();
}

void StageState::Resume()
{
    paused = false;
    if (inGameMenu!=nullptr)
    {
        delete inGameMenu;
        inGameMenu = nullptr;
    }
}

void StageState::LoadAssets()
{
    music.Open(player->name+"BGB.ogg");
    music.Play(-1);
}

void StageState::HandleInput()
{
    if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
    {
        if(paused)
            Resume();
        else
            Pause();
    }
}

void StageState::UpdateGame()
{
    //UpdateRoom();
    currentRoom->Update(Game::GetInstance().GetDeltaTime());
    CleanUpdateBars();
    Camera::GetInstance().Update(Game::GetInstance().GetDeltaTime());
}

void StageState::CleanUpdateBars()
{
    if(player)
    {
            healthBar->SetPercentage(player->GetHealth()/10.0);
            energyBar->SetPercentage(player->GetEnergy()/5.0);
    }
    else
    {
        healthBar->SetPercentage(0);
        energyBar->SetPercentage(0);
    }
}

void StageState::Update()
{
    if(!paused)
    {
        HandleInput();
        UpdateGame();
    }
    else
    {
        if(inGameMenu != nullptr)
        {
            inGameMenu->Update();
            if(inGameMenu->QuitRequested() == true)
                Resume();
        }
        else
            std::cerr << "ERRO: Menu in-game nao existe" <<std::endl;
    }
}

void StageState::Render()
{

    bek.Render(0,0);
    currentRoom->Render();
    for(unsigned int i = 0; i < windowArray.size(); i++)
        windowArray.at(i)->Render();
    healthBar->Render(51,44);
    energyBar->Render(51,44);
    itemHotBarSp.Render(20,629);
    if (player!=nullptr && player->itemManager!=nullptr)
        player->itemManager->Render();

    if (inGameMenu!=nullptr)
        inGameMenu->Render();
}

bool StageState::QuitRequested()
{
    return quitRequested;
}

bool StageState::Is(std::string type)
{
    return (type == "Stage");
}

StageState* StageState::get()
{
    return this;
}
