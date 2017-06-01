#include "Notfredo.h"
#include "Camera.h"
#include "StageState.h"
#include "Gallahad.h"
#include "Lancelot.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"
#include "IAComponent.h"

Notfredo::Notfredo(int x, int y):
	Character(x,y),
	radius(),
	looking(1500),
	idle(1500)
{
	inputComponent = new IAComponent();
	graphicsComponent = new NotfredoGraphicsComponent("EnemyGallahad");
	name = "Notfredo";
	box.SetWH(graphicsComponent->GetSize());
	idle.Start();
}

Notfredo::~Notfredo()
{

}

void Notfredo::Attack()
{
	//Starts attack timer
	attacking.Start();
	//Generates attack object
	StageState::AddObject(new Melee("Melee.png", 2, 0, this, 500, 1));
}

void Notfredo::NotifyTileCollision(int tile, Face face)
{
	if(tile >= SOLID_TILE && (face == LEFT || face == RIGHT))
	{
		if(physicsComponent.velocity.y >= 0.6)
		{
			physicsComponent.velocity.y = -0.5;
		}
	}
}

void Notfredo::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
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
		bool visible = true;
		if(StageState::GetPlayer()->Is("Gallahad"))
		{
			Gallahad* p = (Gallahad*) StageState::GetPlayer();
			if(p->Hiding())
			{
				visible = false;
			}
		}
		if(player.OverlapsWith(radius) && visible)
		{
			if(player.x < box.x )
			{
				physicsComponent.velocity.x -= 0.003*dt;
				if(box.x - physicsComponent.velocity.x*dt < player.x)
				{
					box.x = player.x;
					physicsComponent.velocity.x = 0;
				}
				facing = LEFT;
			}
			else
			{
				physicsComponent.velocity.x += 0.003*dt;
				if(box.x + physicsComponent.velocity.x*dt > player.x)
				{
					box.x = player.x;
					physicsComponent.velocity.x = 0;
				}
				facing = RIGHT;
			}
			clamp(physicsComponent.velocity.x,-0.4f,0.4f);

			if(!Attacking())
			{
				Attack();
			}
		}
		else if(looking.IsRunning() && looking.GetElapsed() == 0)
		{
			if(facing == LEFT)
				physicsComponent.velocity.x = -0.2;
			else
				physicsComponent.velocity.x = 0.2;
		}
		else
		{
			if(idle.IsRunning() && idle.GetElapsed() == 0)
			{
				physicsComponent.velocity.x = 0;
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

void Notfredo::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	UpdateAI(dt);
	inputComponent->Update(this,dt);
	physicsComponent.Update(this,world,dt);
	graphicsComponent->Update(this,dt);
}

bool Notfredo::Is(std::string type)
{
	return (type=="Enemy");
}
