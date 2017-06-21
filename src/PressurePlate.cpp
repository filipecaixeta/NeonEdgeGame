#include "PressurePlate.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
/*
PressurePlate::PressurePlate(float x, float y, std::string spriteOn, std::string spriteOff, std::vector<std::vector<int>> onTiles)
{
	name = "PressurePlate";
	spOn = Sprite(spriteOn);
	spOff = Sprite(spriteOff);	
	Vec2 size = sp.GetSize();
	box = Rect(x, y, size.x, size.y);
	PressurePlate::onTiles = onTiles;
	offTiles = std::vector<std::vector<int>>();
	for(int i=0; i<onTiles.size(); i++)
	{
		offTiles.push_back(onTiles[i]);
		offTiles[i][2] = StageState::GetCurrentRoom()->GetMap()->At(offTiles[i][0], offTiles[i][1], 0);
	}
}

PressurePlate::~PressurePlate()
{

}

bool PressurePlate::IsDead()
{
	return false;
}

void PressurePlate::Trigger() {
	if(facing == RIGHT)
	{
		for (int i = 0; i<onTiles.size(); i++)
		{
			StageState::GetCurrentRoom()->GetMap()->SetTile(onTiles[i][0], onTiles[i][1], 0, onTiles[i][2]);
		}
	}
	else
	{
		for (int i = 0; i<offTiles.size(); i++)
		{
			StageState::GetCurrentRoom()->GetMap()->SetTile(offTiles[i][0], offTiles[i][1], 0, offTiles[i][2]);
		}
	}
}

void PressurePlate::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Gallahad") || other->Is("Lancelot"))
	{
		Character* C = (Character*)other;
		if(C->Attacking())
		{
			if(facing == RIGHT)
			{
				facing = LEFT;
				Trigger();
				sp.Mirror(false);
			}
			else
			{
				facing = RIGHT;
				Trigger();
				sp.Mirror(true);
			}
		}
	}
}

void PressurePlate::Update(float dt)
{

}

void PressurePlate::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
*/