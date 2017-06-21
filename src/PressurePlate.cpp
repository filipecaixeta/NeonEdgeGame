#include "PressurePlate.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

PressurePlate::PressurePlate(int x, int y, TileMap* world, std::string spriteOn, std::string spriteOff, std::vector<std::vector<int>> onTiles)
{
	name = "PressurePlate";
	toggle = false;
	spOn = Sprite(spriteOn);
	spOff = Sprite(spriteOff);
	Vec2 size = spOn.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
	PressurePlate::onTiles = onTiles;
	offTiles = std::vector<std::vector<int>>();
	for(int i=0; i<onTiles.size(); i++)
	{
		offTiles.push_back(onTiles[i]);
		offTiles[i][2] = world->At(offTiles[i][0], offTiles[i][1], 0);
	}
}

PressurePlate::~PressurePlate()
{

}

bool PressurePlate::IsDead()
{
	return false;
}

void PressurePlate::Trigger(TileMap* map)
{
	//int **coisa = toggle ? onTiles : offTiles;
	if(toggle)
	{
		for (int i = 0; i<onTiles.size(); i++)
		{
			map->SetTile(onTiles[i][0], onTiles[i][1], 0, onTiles[i][2]);
		}
	}
	else
	{
		for (int i = 0; i<offTiles.size(); i++)
		{
			map->SetTile(offTiles[i][0], offTiles[i][1], 0, offTiles[i][2]);
		}
	}
}

void PressurePlate::NotifyObjectCollision(GameObject* other)
{
	toggle = true;
}

void PressurePlate::Update(TileMap* map, float dt)
{
		Trigger(map);
		toggle = false;
}

void PressurePlate::Render()
{
	if(toggle)
	{
		spOn.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
	}
	else
	{
		spOff.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
	}

}
