#include "Lancelot.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Lancelot::Lancelot(int x, int y):
	inputComponent(),
	physicsComponent(),
	graphicsComponent("Lancelot"),
	saveComponent()
{
	name = "Lancelot";
	Vec2 size = graphicsComponent.GetSize();
	box = Rect(x, y, size.x, size.y);
	facing = RIGHT;
}

Lancelot::~Lancelot()
{

}

bool Lancelot::IsDead()
{
	return (hitpoints < 1);
}

int Lancelot::GetHealth()
{
	return hitpoints;
}

int Lancelot::GetEnergy()
{
	return energy;
}

void Lancelot::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning() && !blocking.IsRunning()) 
	{
		hitpoints -= (damage);
		invincibilityTimer.Start();
	}
}

void Lancelot::Attack()
{
	//Starts attack timer
	attacking.Start();
	//Generates attack object
	StageState::AddObject(new Melee("Melee.png", 2, 0, this, 500, 1));
}

void Lancelot::Block()
{
	blocking.Start();
	energy -= 1;
	clamp(energy,0,5);
}

void Lancelot::Crouch()
{
	crouching = true;
}

void Lancelot::Stand()
{
	crouching = false;
}

bool Lancelot::Attacking()
{
	return attacking.IsRunning();
}

bool Lancelot::Blocking()
{
	return blocking.IsRunning();
}

bool Lancelot::Crouching()
{
	return crouching;
}

void Lancelot::NotifyTileCollision(int tile, Face face)
{
	if(tile > 11)
	{
		Damage(1);
	}
}

void Lancelot::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Melee"))
	{
		Melee* a = (Melee*) other;
		if(a->owner->Is("Notfredo"))
			Damage(1);
	}
	if(other->Is("Projectile"))
	{
		Projectile* p = (Projectile*) other;
		if(p->owner->Is("Notfredo"))
			Damage(1);
	}
	if(other->Is("Energy"))
	{
		if(crouching && !regenerating.IsRunning())
		{
			regenerating.Start();
			energy += 1;
			clamp(energy,0,5);
		}
	}
}

void Lancelot::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	blocking.Update(dt);
	regenerating.Update(dt);
}

void Lancelot::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	inputComponent.Update(this,dt);
	physicsComponent.Update(this,world,dt);
	graphicsComponent.Update(this,dt);
}

void Lancelot::Render()
{
	graphicsComponent.Render(GetPosition()-Camera::GetInstance().pos);
}
