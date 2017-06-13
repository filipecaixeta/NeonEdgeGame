#include <sstream>

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