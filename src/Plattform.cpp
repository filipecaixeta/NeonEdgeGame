#include "Plattform.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

#include <cmath>

Plattform::Plattform(int x, int y, std::string sprite, int route[10][3])
{
	name = "Plattform";
	sp = Sprite(sprite);
	on = true;
	cycleCount = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Plattform::route[i][j] = route[i][j];
		}
	}
	Vec2 size = sp.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
}

Plattform::~Plattform()
{

}

bool Plattform::IsDead()
{
	return false;
}

void Plattform::Toggle() {
	on = !on;
}

void Plattform::NotifyObjectCollision(GameObject* other)
{

}

void Plattform::Update(TileMap* map, float dt)
{
	if(on)
	{
		if(box.x - route[cycleCount][0] > 10 || box.x - route[cycleCount][0] < - 10 || box.y - route[cycleCount][1] > 10 || box.y - route[cycleCount][1] < - 10 )
		{
			if(box.y != route[cycleCount][1])
			{
				box.x += (route[cycleCount][0]-box.x)/abs(((route[cycleCount][1])-box.y))*dt*route[cycleCount][2]/33;
				if(box.y < route[cycleCount][1])
				{
					box.y += dt*route[cycleCount][2]/33;
				}
				if(box.y > route[cycleCount][1])
				{
					box.y -= dt*route[cycleCount][2]/33;
				}
			}
			else if(box.x < route[cycleCount][0])
			{
				box.x += dt*route[cycleCount][2]/33;
			}	
			else
			{
				box.x -= dt*route[cycleCount][2]/33;	
			}
		}
		else if(cycleCount<9)
		{
			box.x = route[cycleCount][0];
			box.y = route[cycleCount][1];
			cycleCount++;
		}
		else
		{
			box.x = route[cycleCount][0];
			box.y = route[cycleCount][1];
			cycleCount = 0;
		}

	}
}

void Plattform::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
