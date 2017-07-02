#include <iostream>
#include <ctime>
#include <cstdlib>

#include "StageState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "DialogWindow.h"
#include "SaveComponent.h"
#include "menu/inGamePause.h"
#include "ColisionFunctions.h"

Player* StageState::player = nullptr;
Room* StageState::currentRoom = nullptr;

StageState::StageState(std::string mode_, int sizeX, int sizeY, std::string background):
	State(),
	mode(mode_),
	tileSet(nullptr),
	paused(false),
	windowArray(),
	//roomArray(nullptr),
	healthBar(nullptr),
	energyBar(nullptr),
	inGameMenu(nullptr)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	tileSet = new TileSet(64, 64, "Tile_Map_Cidade.png", 8, 8);
	currentRoom = new Room(tileSet, 0, Vec2(0,0));
	//CreateMap(sizeX,sizeY);
	/*if(mode == "Lancelot")
		player = new Lancelot(133, 131);
	else if(mode == "Gallahad")
		player = new Gallahad(269, 544);*/
	player = (Player*) currentRoom->GetFirst();
	Camera::GetInstance().Follow(player);	
	currentRoomX = 0;
	currentRoomY = 0;

	bg = new Sprite(background);
	//bg->SetScaleX(currentRoom->GetMap()->GetWidth() * currentRoom->GetMap()->GetTileWidth()/bg->GetWidth());
	//bg->SetScaleY(currentRoom->GetMap()->GetHeight() * currentRoom->GetMap()->GetTileHeight()/bg->GetHeight());

	AddObject(new Box(2000, 1000, "window.png"));

	Camera::GetInstance().maxPos = Vec2(currentRoom->GetMap()->GetWidth()*currentRoom->GetMap()->GetTileWidth(),
										currentRoom->GetMap()->GetHeight()*currentRoom->GetMap()->GetTileHeight());

	CreateBars(player->name);
}

StageState::~StageState()
{
	player = nullptr;
	delete currentRoom;
	delete bg;
	//currentRoom = nullptr;
	//delete[] roomArray;
	//delete tileSet;
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
	inGameMenu = new inGamePause(this);
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
	music.Open("stageState.ogg");
	/*bg.Open("LancelotIdle.png");
	bg.Open("LancelotRunning.png");
	bg.Open("Melee.png");
	bg.Open("NotfredoRunning.png");
	bg.Open("NotfredoIdle.png");
	bg.Open("Tileset3D.png");*/
	music.Play(-1);
}

void StageState::HandleInput()
{
	if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE))
	{
		quitRequested = true;
	}

	if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
	{
		if(paused)
			Resume();
		else
			Pause();
	}
}

/*void StageState::UpdateRoom()
{
	int x = (int)player->box.GetCenter().x/(currentRoom->GetMap()->GetWidth()*currentRoom->GetMap()->GetTileWidth());
	int y = (int)player->box.GetCenter().y/(currentRoom->GetMap()->GetHeight()*currentRoom->GetMap()->GetTileHeight());
	if(currentRoom->GetPos().x != x || currentRoom->GetPos().y != y)
	{
		currentRoom->RemovePlayer();
		currentRoom = roomInfo[x][y];
		currentRoomX = x;
		currentRoomY = y;
		currentRoom->AddObjectAsFirst(player);
	}
}*/

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
			if(inGameMenu->QuitRequested()==true)
				Resume();
		}
		else
			std::cerr << "ERRO: Menu in-game nao existe" <<std::endl;
	}
}

void StageState::Render() 
{
	/*for(int i = sizeX-1; i >= 0; i--)
	{
		for(int j = sizeY-1; j >= 0; j--)
		{
			if(i > currentRoomX - 1 || i < currentRoomX + 1)
				if(j > currentRoomY - 1 || j < currentRoomY + 1)
					roomInfo[i][j]->Render();
		}
	}*/
	bg->Render(0, 0);
	currentRoom->Render();
	for(unsigned int i = 0; i < windowArray.size(); i++)
		windowArray.at(i)->Render();
	healthBar->Render(51,44);
	energyBar->Render(51,44);
	if (player->itemManager!=nullptr)
		player->itemManager->Render();

	if (inGameMenu!=nullptr)
		inGameMenu->Render();
}

/*void StageState::CreateMap(int sizeX, int sizeY)
{
	std::pair<int, int> aux(0, 0);
	srand(time(NULL));
	algorithm = MapAlgorithm();

	algorithm.RandomizeRoomOrder(&roomOrder);

	roomArray = new int*[sizeX];
	for(int i = 0; i < sizeX; i++){
		roomArray[i] = new int[sizeY];
	}

	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			roomArray[i][j] = -1;
		}
	}

	roomInfo = new Room**[sizeX];
	for(int i = 0; i < sizeX; i++){
		roomInfo[i] = new Room*[sizeY];
	}

	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			roomInfo[i][j] = nullptr;
		}
	}

	algorithm.PopulateRoomArray(roomArray, &roomOrder, &aux, sizeX, sizeY);

	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			std::cout << roomArray[i][j] << "\t";
		}
		std::cout << "\n";
	}

	MassLoad(sizeX, sizeY);
}*/

/*void StageState::MassLoad(int sizeX, int sizeY)
{
	for(int i = 0; i < sizeX; i++)
	{
		for(int j = 0; j < sizeY; j++)
		{
			roomInfo[i][j] = new Room(tileSet, roomArray[i][j], Vec2(i,j));
		}
		std::cout << "\n";
	}
}*/

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
