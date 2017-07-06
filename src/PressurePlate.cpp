#include "PressurePlate.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

/*PressurePlate::PressurePlate(int x, int y, TileMap* world, std::string spriteOn, std::string spriteOff, std::vector<std::vector<int>> onTiles)
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
}*/

PressurePlate::PressurePlate(int x, int y, std::string spriteOn, std::string spriteOff, Door* door)
{
	name = "PressurePlate";
	toggle = false;
	spOn = Sprite(spriteOn);
	spOff = Sprite(spriteOff);
	Vec2 size = spOn.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
	PressurePlate::door = door;
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
	if(toggle)
	{
		door->hard = false;
		door->sp = Sprite();
	}
	else
	{
		door->hard = true;
		door->sp = Sprite("Melee.png");
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
