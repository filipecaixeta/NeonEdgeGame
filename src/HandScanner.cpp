#include "HandScanner.h"
#include "Camera.h"
#include "StageState.h"
#include "Player.h"

HandScanner::HandScanner(int x, int y, Interactive* d):
	Interactive(x,y,"HandScanner")
{
	name = "HandScanner";
	door = d;
}

HandScanner::~HandScanner()
{

}

void HandScanner::Trigger()
{
	if(Active())
	{
		door->On();
	}
	else
	{
		door->Off();
	}
}

void HandScanner::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Drone"))
	{
		Player* p = (Player*) other;
		if(p->Attacking())
		{
			Player* play = (Player*) StageState::GetPlayer();
			if(play->skills[4])
			{
				On();		
			}
		}
	}
}

void HandScanner::Update(TileMap* map, float dt)
{
	Interactive::Update(map,dt);
	Trigger();
}
