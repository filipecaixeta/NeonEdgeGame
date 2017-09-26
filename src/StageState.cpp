/**
    Copyright (c) 2017 Neon Edge
    File Name: StageState.cpp
    Header File Name: StageState.h
    Class Name: StageState
    Objective: Class responsible for the stage state of the moment of game.

*/

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

/**
    Objective: Construction method that loads the component in their respective stages.
    @param string fase - Refers to the stage of game.
    @return - none.

*/
StageState::StageState(std::string fase, std::string background): State(), tileSet(nullptr),
                                                                  paused(false), windowArray(), healthBar(nullptr),
                                                                  energyBar(nullptr), inGameMenu(nullptr) {
    this->background = new TileSet(7389, 1711, background, 0, 0);
    tileSet = new TileSet(64, 64, "Tile_Map_Cidade.png", 8, 8);
    currentRoom = new Room(tileSet, 0, Vec2(0, 0), this->background, fase);

    //restrain the objects that will be created in their respectives stages/fase.
    if (fase == "cidadeLancelot") {
        this->background = new TileSet(7389, 1711, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Cidade.png", 8, 8);
        currentRoom = new Room(tileSet, 0, Vec2(0, 0), this->background, fase);
        } else if (fase == "naveGalahad") {
        this->background = new TileSet(1, 1, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Nave.png", 8, 8);
        currentRoom = new Room(tileSet, 1, Vec2(0, 0), this->background, fase);
        bek.Open("SpaceBG.png");
        } else if (fase == "cidadeGalahad") {
        this->background = new TileSet(7389, 1711, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Cidade.png", 8, 8);
        currentRoom = new Room(tileSet, 2, Vec2(0, 0), this->background, fase);
        } else if (fase == "naveLancelot") {
                this->background = new TileSet(1, 1, background, 0, 0);
        tileSet = new TileSet(64, 64, "Tile_Map_Nave.png", 8, 8);
        currentRoom = new Room(tileSet, 3, Vec2(0, 0), this->background, fase);
        bek.Open("SpaceBG.png");
    }

    Camera::GetInstance().SetPos(Vec2(player->box.x, player->box.y)); // Sets the box position in x and y of the player.
    Camera::GetInstance().Follow(player); // Initializes putting the player to be the focus of camera.
    currentRoomX = 0; // Set the default position of the current room in X.
    currentRoomY = 0; // Set the default position of the current room in Y.

    Camera::GetInstance().maxPos = Vec2(currentRoom->GetMap()->GetWidth()*currentRoom->GetMap()->GetTileWidth(),
                                   currentRoom->GetMap()->GetHeight()*currentRoom->GetMap()->GetTileHeight());
    CreateBars(player->name);

    stage = fase;
    itemHotBarSp.Open("menus/" + player->name + "itemhotbar.png");
}

/**
    Objective: Function that defines the default of the objects stages.
    @param - It does not receive parameters.
    @return - none.

*/
StageState::~StageState() {
    // Initializing the core variables of stages.
    player = nullptr; // Initializing player pointin to nullptr and be the default stage of a player.
    delete currentRoom;
    music.Stop();
    windowArray.clear();
}

/**
    Objective: Send the pointer data information of the stage of current room .
    @param - It does not receive parameters.
    @return - none.

*/
Room* StageState::GetCurrentRoom() {
    return currentRoom;
}

/**
    Objective: Send the pointer data information of the stage of player.
    @param - It does not receive parameters.
    @return - none.

*/
GameObject* StageState::GetPlayer() {
    return player;
}

/**
    Objective: This function sets the pointer data to player.
    @param Player* ptr - The reference of a Players object.
    @return - none.

*/
void StageState::SetPlayer(Player* ptr) {
    player = ptr;
}

/**
    Objective: Function used to destroy players type objects.
    @param - It does not receive parameters.
    @return - none.

*/

void StageState::KillPlayer() {
    player = nullptr;
}

/**
    Objective: The function of this method is used to add objects by data reference to the currentRoom.
    @param GameObject* ptr - The reference of a GameObject type.
    @return - none.

*/
void StageState::AddObject(GameObject* ptr) {
    currentRoom->AddObject(ptr);
}

/**
    Objective: The function of this method is used to add objects by data reference in the first position to the currentRoom.
    @param GameObject* ptr - The reference of a GameObject type.
    @return - none.

*/

void StageState::AddObjectAsFirst(GameObject* ptr) {
    currentRoom->AddObjectAsFirst(ptr);
}

/**
    Objective: The function of this method is used to remove objects by data reference of the currentRoom.
    @param GameObject* ptr - The reference of a GameObject type.
    @return - none.

*/
void StageState::RemoveObject(GameObject* ptr) {
    currentRoom->RemoveObject(ptr);
}

/**
    Objective: This method create the lifebar and energybar.
    @param string playerName - The name of a player.
    @return - none.

*/
void StageState::CreateBars(std::string playerName) {
    healthBar = new LoadingBar("lifebar_" + playerName + ".png", 11); // Initializing and make the configuration of the healthBar file picture.
    energyBar = new LoadingBar("energybar_" + playerName + ".png", 174, 28, 6);  // Initializing and make the configuration of the energyBar file picture.
}

/**
    Objective: This method stop the rendering of a windows
    @param Window* ptr - The reference data of a windows
    @return - none.

*/
void StageState::RemoveWindow(Window* ptr) {
    windowArray.emplace_back(ptr);
}

/**
    Objective: This method is used to load the pause stage in the game.
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::Pause() {
    // Call the Pause components to run the Pause stage.
    paused = true;
    inGameMenu = new InGamePause(this);
    inGameMenu->LoadAssets();
}

/**
    Objective: This method is used to set the Resume stage in the game.
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::Resume() {
    // Puts the game to run again and set their components to default.
    paused = false;
    if (inGameMenu != nullptr) {
        delete inGameMenu;
        inGameMenu = nullptr;
    }
}

/**
    Objective: This method is used to load the sound of the game.
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::LoadAssets() {
    // The code responsible to call sounds in their respective situations.
    music.Open(player->name + "BGB.ogg");
    music.Play(-1);
}

/**
    Objective: This method is used to control the stage pause and resume.
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::HandleInput() {
    if (InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
        if (paused) {
            Resume();
        } else {
            Pause();
        }
    }
}

/**
    Objective: This method is used to update the game.
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::UpdateGame() {
    // UpdateRoom();
    currentRoom->Update(Game::GetInstance().GetDeltaTime());
    CleanUpdateBars();
    Camera::GetInstance().Update(Game::GetInstance().GetDeltaTime());
}

/**
    Objective: This method is used to control the values of healthBar and energyBar in their respective stages..
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::CleanUpdateBars() {
    // Checks the condition of player to set the healthBat and energyBar percentage.
    if (player) {
        healthBar->SetPercentage(player->GetHealth() / 10.0);
        energyBar->SetPercentage(player->GetEnergy() / 5.0);
    } else {
        healthBar->SetPercentage(0);
        energyBar->SetPercentage(0);
    }
}

/**
    Objective: This method is used to update the game.
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::Update() {
    // Check whether the stage of pause is different from null.
    if (!paused) {
        HandleInput();
        UpdateGame();
    } else {
        if (inGameMenu != nullptr) {
            inGameMenu->Update();
            // Check wheter the stage of the menu is finish to the player resume the game.
            if (inGameMenu->QuitRequested() == true) {
                Resume();
                    }
            } else {
            std::cerr << "ERRO: Menu in-game nao existe" << std::endl;
        }
    }
}

/**
    Objective: This method is responsible to render the stages of the game.
    @param - It does not receive parameters.
    @return - none.

*/
void StageState::Render() {
    bek.Render(0, 0);
    currentRoom->Render();
    // Render the entire window with their respectives measures.
    for (unsigned int i = 0; i < windowArray.size(); i++) {
        windowArray.at(i)->Render();
        }
    healthBar->Render(51, 44);
    energyBar->Render(51, 44);
    itemHotBarSp.Render(20, 629);

    // Check if is be possible to render the itemManager of player
    if (player != nullptr && player->itemManager != nullptr) {
        player->itemManager->Render();
    }
    // Check if the stage of inGameMenu can be rendering.
    if (inGameMenu != nullptr) {
        inGameMenu->Render();
    }
}

/**
    Objective: This method is used to know the quit request stage of the game.
    @param - It does not receive parameters.
    @return - none.

*/
bool StageState::QuitRequested() {
    return quitRequested;
}

/**
    Objective: This function is used to check if is really stage type or not.
    @param string type - Is used to receive the types stage.
    @return - none.

*/
bool StageState::Is(std::string type) {
    return (type == "Stage");
}

/**
    Objective: This function make be possible get the stages in the game.
    @param - It does not receive parameters.
    @return - none.

*/

StageState* StageState::get() {
    return this;
}
