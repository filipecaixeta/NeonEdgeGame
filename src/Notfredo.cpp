#include "Notfredo.h"
#include "InputManager.h"
#include "Camera.h"
#include "StageState.h"

Notfredo::Notfredo(int x, int y):
	physicsComponent(),
	graphicsComponent("Notfredo")
{
	name = "Notfredo";
	Vec2 size = graphicsComponent.GetSize();
	box = Rect(x, y, size.x, size.y);
	facing = RIGHT;
	speed = Vec2(0.2, 0.6);
	idle.Start();
}

Notfredo::~Notfredo()
{

}

Notfredo* Notfredo::Get()
{
	return this;
}

bool Notfredo::IsDead()
{
	return (hitpoints < 1);
}

void Notfredo::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning())
	{
		hitpoints -= (damage);
		invincibilityTimer.Start();
	}
}

void Notfredo::NotifyTileCollision(int tile, Face face)
{

}

void Notfredo::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Attack"))
	{
		if(other->facing == facing)
			Damage(1);
		else
			Damage(1);
	}
}

void Notfredo::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	if(looking.IsRunning())
	{	
		looking.Update(dt);
		if(!looking.IsRunning())
			idle.Start();
	}
	else if(idle.IsRunning())
	{
		idle.Update(dt);
		if(!idle.IsRunning())
			looking.Start();
	}
}

void Notfredo::UpdateAI(float dt)
{
	radius = Rect(box.x-200, box.y-200, box.w+400, box.h+400);
	if(StageState::GetPlayer())
	{
		Rect player = StageState::GetPlayer()->box;
		if(StageState::IsColliding(radius, player) /*&& !Godofredo::player->IsHidden()*/)
		{
			if(player.x < box.x)
			{
				speed.x -= 0.003*dt;
				if(box.x - speed.x*dt < player.x)
				{
					box.x = player.x;
					speed.x = 0;
				}
				facing = LEFT;
			}
			else
			{
				speed.x += 0.003*dt;
				if(box.x + speed.x*dt > player.x)
				{
					box.x = player.x;
					speed.x = 0;
				}
				facing = RIGHT;
			}
			clamp(speed.x,-0.4f,0.4f);
		}
		else if(looking.IsRunning() && looking.GetElapsed() == 0)
		{
			if(facing == LEFT)
				speed.x = -0.2;
			else
				speed.x = 0.2;
		}
		else
		{
			if(idle.IsRunning() && idle.GetElapsed() == 0)
			{
				speed.x = 0;
				if(facing == LEFT)
				{
					facing = RIGHT;
				}
				else
				{
					facing = LEFT;
				}
			}
		}
	}
}

void Notfredo::Update(float dt)
{
	UpdateTimers(dt);
	UpdateAI(dt);
	physicsComponent.Update(this,dt);
	graphicsComponent.Update(this,dt);
}

void Notfredo::Render()
{
	graphicsComponent.Render(GetPosition()-Camera::GetInstance().pos);
}
