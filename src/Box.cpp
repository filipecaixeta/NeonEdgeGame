#include "Box.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Projectile.h"
#include "Room.h"

Box::Box(int x, int y, std::string sprite)
{
	name = "Box";
	sp = Sprite(sprite);
	Vec2 size = sp.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
	hitpoints = 4;
	triggerCooldown = Timer(1000);
}

Box::~Box()
{

}

bool Box::IsDead()
{
	return hitpoints<1;
}

void Box::Trigger(TileMap* map)
{
	hitpoints -= 1;
}

void Box::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Player") && !other->Is("Drone"))
	{
		Character* c = (Character*) other;
		if((c->physicsComponent.velocity.x > 0) && (other->footing == GROUNDED) && (other->box.y+other->box.h>box.y) && (other->facing == RIGHT))
		{
			box.x += 5;
		}
		else if((c->physicsComponent.velocity.x < 0) && (other->footing == GROUNDED) && (other->box.y+other->box.h>box.y) && (other->facing == LEFT))
		{
			box.x -= 5;
		}
		if(c->Attacking())
		{
			if(!triggerCooldown.IsRunning())
			{
				triggerCooldown.Start();
			}
		}
	}
	if(other->Is("Drone"))
	{
		if(other->box.x < box.x && other->box.y > box.y)
		{
			box.x += 10;
		}
		if(other->box.x > box.x && other->box.y > box.y)
		{
			box.x -= 10;
		}
		if(other->box.y < box.y)
		{
			other->box.y -= 10;
		}
	}
	if(other->Is("Door"))
	{
		Door* d = (Door*) other;
		if(d->hard)
		{
			if(box.x < other->box.x)
			{
				box.x -= 10;
			}
			else
			{
				box.x += 10;
			}
		}
	}
	if(other->Is("Projectile"))
	{
		Projectile* p = (Projectile*) other;
		if(p->GetOwner()->Is("Gallahad") || p->GetOwner()->Is("Player"))
		{
			if(!triggerCooldown.IsRunning())
			{
				triggerCooldown.Start();
			}			
		}
	}
}

void Box::UpdateTimers(float dt)
{
	triggerCooldown.Update(dt);
}

void Box::Update(TileMap* map, float dt)
{
	physicsComponent.Update(this,map,dt);
	if(triggerCooldown.IsRunning() && triggerCooldown.GetElapsed() == 0)
	{
		Trigger(map);
	}
	UpdateTimers(dt);
}

void Box::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
