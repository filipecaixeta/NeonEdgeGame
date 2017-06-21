#include "Lever.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

Lever::Lever(int x, int y, TileMap* world, std::string sprite, std::vector<std::vector<int>> onTiles)
{
	name = "Lever";
	sp = Sprite(sprite);
	Vec2 size = sp.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
	Lever::onTiles = onTiles;
	offTiles = std::vector<std::vector<int>>();
	for(int i=0; i<onTiles.size(); i++)
	{
		offTiles.push_back(onTiles[i]);
		offTiles[i][2] = world->At(offTiles[i][0], offTiles[i][1], 0);
	}
	triggerCooldown = Timer(500);
}

Lever::~Lever()
{

}

bool Lever::IsDead()
{
	return false;
}

void Lever::Trigger(TileMap* map) {
	if(facing == LEFT)
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

void Lever::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Gallahad") || other->Is("Lancelot"))
	{
		Character* C = (Character*)other;
		if(C->Attacking())
		{
			if(!triggerCooldown.IsRunning())
			{
				if(facing == RIGHT)
				{
					facing = LEFT;
					sp.Mirror(true);
				}
				else
				{
					facing = RIGHT;
					sp.Mirror(false);
				}
				triggerCooldown.Start();
			}
		}
	}
}

void Lever::UpdateTimers(float dt)
{
	triggerCooldown.Update(dt);
}

void Lever::Update(TileMap* map, float dt)
{
	if(triggerCooldown.IsRunning() && triggerCooldown.GetElapsed() == 0)
	{
		Trigger(map);
	}
	UpdateTimers(dt);
}

void Lever::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
