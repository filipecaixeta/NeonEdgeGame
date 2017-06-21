#include <sstream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Room.h"
#include "Camera.h"
#include "StageState.h"

Room::Room(TileSet* tileSet, int index, Vec2 position)
{
	std::stringstream ss;
	Room::index = index;
	Room::position = position;
	ss << index;
	map = new TileMap("resources/map/room0"+ss.str()+".txt", tileSet, {position.x,position.y});
	objectArray = std::vector<GameObject*>();
	LoadObjects("resources/map/objs/room0"+ss.str()+".txt");
	CreateObjects();
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
			delete objectArray[i];
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
			delete objectArray[i];
			objectArray.erase(objectArray.begin()+i);
		}
	}
}
	
void Room::Update(float dt)
{
	ObjectUpdate(dt);
	ObjectCollision();
	ObjectCleanup();
}

void Room::Render()
{
	map->RenderLayer(0,Camera::GetInstance().pos.x,Camera::GetInstance().pos.y);
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->Render();
	}
	//map->RenderLayer(0,Camera::GetInstance().pos.x,Camera::GetInstance().pos.y);
}

void Room::CreateObjects(){
	for(unsigned int i = 0; i < objectData.size(); i++)
	{
		if(objectData.at(i).id == 0)
		{
			//cria Lancelot
		}
		if(objectData.at(i).id == 1)
		{
			//cria Galahad
		}
		if(objectData.at(i).id == 2)
		{
			AddObject(new Energy(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
								objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(), "Energy.png", 4, 120));
		}
		if(objectData.at(i).id == 10)
		{
			AddObject(new Notfredo(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
                                    objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(),GROUND));
		}
        if(objectData.at(i).id == 12)
        {
            AddObject(new Notfredo(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
                                   objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(),FLYING));
        }
        if(objectData.at(i).id == 21)
        {
        	AddObject(new Lever(objectData.at(i).x + position.x * map->GetWidth() * map->GetTileWidth(),
        						objectData.at(i).y + position.y * map->GetHeight() * map->GetTileHeight(),
        						map, "Lever.png", objectData.at(i).v));
        }
	}
}

void Room::LoadObjects(std::string file){
	int repeat = 0;
	ObjectData data;
	std::ifstream f;
	std::string num;

	f.open(file.c_str(), std::ios::in);
	if(f.is_open())
	{
		while(getline(f, num, ','))
		{
			if(repeat == 0)
			{
				data.id = atoi(num.c_str());
				repeat++;
			}
			else if(repeat == 1)
			{
				data.x = atoi(num.c_str());
				repeat++;
			}
			else if(repeat == 2)
			{
				data.y = atoi(num.c_str());
				repeat++;
			}
			else if(repeat == 3)
			{
				int n = atoi(num.c_str());
				for(int i = 0; i<n; i++)
				{
					data.v.push_back(std::vector<int>());
					getline(f, num, ',');
					data.v[i].push_back(atoi(num.c_str()));
					getline(f, num, ',');
					data.v[i].push_back(atoi(num.c_str()));
					getline(f, num, ',');
					data.v[i].push_back(atoi(num.c_str()));
				}
				objectData.push_back(data);
				repeat = 0;
			}
		}
	}
	else
	{
		std::cout<< "f.open: unable to open file: " << file.c_str();
	}
}
