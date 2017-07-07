#include <sstream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Room.h"
#include "Camera.h"
#include "StageState.h"
#include "ColisionFunctions.h"
#include "Item.h"

#include "Character.h"
#include "Player.h"
#include "CeilingEnemy.h"
#include "NotFredoStationary.h"
#include "TurretBoss.h"
#include "Turret.h"

#include "Interactive.h"
#include "Door.h"
#include "PressurePlate.h"
#include "Box.h"
#include "BoxSpawner.h"

Room::Room(TileSet* tileSet, int index, Vec2 position, TileSet* background):
	sceneObjects("resources/map/objs/sceneObjects.txt")
{
	std::stringstream ss;
	Room::index = index;
	Room::position = position;
	ss << index;
	map = new TileMap("resources/map/room0"+ss.str()+".txt", tileSet, {0,0});
	std::cerr << map->GetSize() << std::endl;
	backgroundMap = new TileMap("resources/map/bg.txt", background, {0, map->GetSize().y}, true);
	objectArray = std::vector<GameObject*>();
	LoadObjects("resources/map/objs/room0"+ss.str()+".txt");
	CreateObjects();
	std::cout << ss.str() << "\t";
}

Room::~Room()
{
	delete map;
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		delete objectArray[i];
	}
	objectArray.clear();
}

void Room::AddObject(GameObject* ptr)
{
	objectArray.emplace_back(ptr);
}

void Room::AddObjectAsFirst(GameObject* ptr)
{
	objectArray.emplace(objectArray.begin(), ptr);
}

void Room::RemoveObject(GameObject* ptr)
{
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		if(ptr == objectArray[i])
		{
			if (!objectArray[i]->Is("Item"))
			{
				delete objectArray[i];
			}
			objectArray.erase(objectArray.begin()+i);
			break;
		}
	}
}

void Room::RemovePlayer()
{
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		if(objectArray[i] == StageState::GetPlayer())
		{
			objectArray.erase(objectArray.begin()+i);
			break;
		}
	}	
}

GameObject* Room::GetFirst()
{
	return objectArray[0];
}

Vec2 Room::GetPos()
{
	return position;
}

TileMap* Room::GetMap()
{
	return map;
}

void Room::ObjectUpdate(float dt)
{
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->Update(map, dt);
	}
}
	
void Room::ObjectCollision()
{
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		for(unsigned j = i+1; j < objectArray.size(); j++)
		{
			if(objectArray[i]->Is("Animation") || objectArray[j]->Is("Animation"))
			{

			}
			else if(objectArray[i]->box.OverlapsWith(objectArray[j]->box))
			{
				objectArray[i]->NotifyObjectCollision(objectArray[j]);
				objectArray[j]->NotifyObjectCollision(objectArray[i]);
				if(objectArray[i]->Is("Item") && objectArray[j]->Is("Player"))
					dynamic_cast<Item*>(objectArray[i])->Eval(dynamic_cast<Player*>(objectArray[j]));
				else if(objectArray[j]->Is("Item") && objectArray[i]->Is("Player"))
					dynamic_cast<Item*>(objectArray[j])->Eval(dynamic_cast<Player*>(objectArray[i]));
			}
		}
	}
}

void Room::ObjectCleanup()
{
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		if(objectArray[i]->IsDead())
		{
			if(objectArray[i] == Camera::GetInstance().GetFocus())
				Camera::GetInstance().Unfollow();
			if(objectArray[i] == StageState::GetPlayer())
				StageState::KillPlayer();
			sceneObjects.AddObject(objectArray[i]->name,objectArray[i]->box.GetXY()+Vec2(0,objectArray[i]->box.h));
			delete objectArray[i];
			objectArray.erase(objectArray.begin()+i);
		}
	}
}
	
void Room::Update(float dt)
{
	ObjectUpdate(dt);
	sceneObjects.Update();
	ObjectCollision();
	ObjectCleanup();
}

void Room::Render()
{
	backgroundMap->RenderLayer(0,Camera::GetInstance().pos.x,Camera::GetInstance().pos.y);
	sceneObjects.Render();
	map->RenderLayer(0,Camera::GetInstance().pos.x,Camera::GetInstance().pos.y);
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->Render();
	}
	//map->RenderLayer(0,Camera::GetInstance().pos.x,Camera::GetInstance().pos.y);
}

void Room::CreateObjects()
{
	for(unsigned int i = 0; i < objectData.size(); i++)
	{
		if(objectData.at(i).id == 0) // Lancelot
		{
			ItensManager* itensManager = new ItensManager();
			AddObjectAsFirst(new Lancelot(itensManager,objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
								   		  objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
			Player* p = (Player*) objectArray[0];
			StageState::SetPlayer(p);
		}
		else if(objectData.at(i).id == 1) // Gallahad
		{
			ItensManager* itensManager = new ItensManager();
			AddObject(new Drone(itensManager,objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
								objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
			AddObjectAsFirst(new Gallahad(itensManager,objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
								   		  objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(),
								   		  objectArray.at(objectArray.size()-1)));
			Player* p = (Player*) objectArray[0];
			StageState::SetPlayer(p);
		}
		else if(objectData.at(i).id == 2) // Arthur
		{
			AddObject(new Arthur(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
        						 objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
		}
		else if(objectData.at(i).id == 3) // TurretBoss
		{
			TurretBoss* t;
			TurretPiece* p;
			AddObject(new TurretBoss(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
									 objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
			t = (TurretBoss*) objectArray.at(objectArray.size()-1);
			AddObject(new TurretPiece(t, -50, -53, 4));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, -50, -163, 4));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, -50, -273, 4));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 0, -55, 2));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 0, -165, 2));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 0, -275, 2));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 0, 0, 1));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 0, -110, 1));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 0, -220, 1));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, -5, -358, 0));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 20, -53, 3));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 20, -163, 3));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
			AddObject(new TurretPiece(t, 20, -273, 3));
			p = (TurretPiece*) objectArray.at(objectArray.size()-1);
			t->AddPiece(p);
		}
		else if(objectData.at(i).id == 10)
		{
			AddObject(new Notfredo(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
                                    objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(),GROUND));
		}
		else if(objectData.at(i).id == 12)
        {
            AddObject(new Notfredo(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
                                   objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(),FLYING));
        }
		else if(objectData.at(i).id == 14)
        {
            AddObject(new CeilingEnemy(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
                                       objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
        }
		else if(objectData.at(i).id == 15)
        {
            AddObject(new NotFredoStationary(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
                                   objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
        }
		else if(objectData.at(i).id == 16)
		{
			AddObject(new Turret(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
								 objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
		}
		else if(objectData.at(i).id == 19)
		{
			
		}
		else if(objectData.at(i).id == 20)
        {
        	AddObject(new Energy(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
								 objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(), "Energy.png", 4, 120));
        }
		else if(objectData.at(i).id == 21) // Door
        {
        	AddObject(new Door(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
							   objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
        }
		else if(objectData.at(i).id == 22) // PressurePlate
        {
        	Interactive* in = (Interactive*) objectArray.at(objectArray.size()-1);
        	AddObjectAsFirst(new PressurePlate(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
        									   objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(), in));
        }
		else if(objectData.at(i).id == 23) // Box
        {
        	AddObject(new Box(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
        					  objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
        }
        else if(objectData.at(i).id == 24) // BoxSpawner
        {
        	AddObject(new BoxSpawner(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
        					  objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
        }
		else if(objectData.at(i).id == 41)
        {
			ItensManager* itensManager = new ItensManager();
			AddObject(new Drone(itensManager,objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
        						objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight()));
        }
		else if(objectData.at(i).id > 100) // Item
		{
			AddObject(new Item(objectData[i].id,objectData[i].x,objectData[i].y));
		}
	}
}

void Room::LoadObjects(std::string file){
	std::ifstream f;
	f.open(file.c_str(), std::ios::in);

	if(!f.is_open())
	{
		std::cerr<< "f.open: unable to open file: " << file.c_str();
		return;
	}
	for(std::string line; std::getline(f, line); )
	{
		char delimiter;
		int n;
		ObjectData data;
		std::stringstream ss(line);
		ss >> data.id;
		ss >> delimiter;
		ss >> data.x;
		ss >> delimiter;
		ss >> data.y;
		ss >> delimiter;
		ss >> n;
		ss >> delimiter;

		if(n > 20)
		{
			ObjectData newData;
			
			newData.id = n;
			ss >> newData.x;
			ss >> delimiter;
			ss >> newData.y;
			ss >> delimiter;

			objectData.push_back(newData);
		}

		objectData.push_back(data);
	}
}
