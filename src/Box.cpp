#include "Box.h"
#include "Camera.h"
#include "StageState.h"
#include "Character.h"
#include "Projectile.h"

Box::Box(int x, int y):
	Interactive(x,y,"Box")
{
	name = "Box";
	hitpoints = 5;
	invincibilityTimer = Timer(500);
}

Box::~Box()
{

}

int Box::GetHealth()
{
	return hitpoints;
}

void Box::Kill()
{
	hitpoints = 0;
}

bool Box::IsDead()
{
	return (hitpoints < 1);
}

void Box::Trigger()
{
	if(!invincibilityTimer.IsRunning())
	{
		hitpoints -= 1;
		invincibilityTimer.Start();
	}
}

void Box::NotifyObjectCollision(GameObject* other)
{
	if(other->IsPlayer() && !other->Is("Drone"))
	{
		Character* c = (Character*) other;
		if((c->physicsComponent.velocity.x > 0) && (other->footing == GROUNDED) && (other->box.y+other->box.h > box.y) && (other->facing == RIGHT))
		{
			box.x += 5;
			physicsComponent.TileFix(this,StageState::GetCurrentRoom()->GetMap(),RIGHT);
		}
		else if((c->physicsComponent.velocity.x < 0) && (other->footing == GROUNDED) && (other->box.y+other->box.h > box.y) && (other->facing == LEFT))
		{
			box.x -= 5;
			physicsComponent.TileFix(this,StageState::GetCurrentRoom()->GetMap(),LEFT);
		}
		if(c->Attacking())
		{
			Trigger();
		}
	}
	if(other->Is("Projectile"))
	{
		Projectile* p = (Projectile*) other;
		if(p->GetOwner()->IsPlayer())
		{
			Trigger();		
		}
	}
}

void Box::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
}

void Box::Update(TileMap* map, float dt)
{
	UpdateTimers(dt);
	physicsComponent.Update(this,map,dt);
	Interactive::Update(map,dt);
}
