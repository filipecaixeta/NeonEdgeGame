#include "Gallahad.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Gallahad::Gallahad(int x, int y):
	inputComponent(),
	physicsComponent(),
	graphicsComponent("Gallahad"),
	saveComponent()
{
	name = "Gallahad";
	Vec2 size = graphicsComponent.GetSize();
	box = Rect(x, y, size.x, size.y);
	facing = RIGHT;
}

Gallahad::~Gallahad()
{

}

bool Gallahad::IsDead()
{
	return (hitpoints < 1);
}

int Gallahad::GetHealth()
{
	return hitpoints;
}

int Gallahad::GetEnergy()
{
	return energy;
}

void Gallahad::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning()) 
	{
		hitpoints -= (damage);
		invincibilityTimer.Start();
	}
}

void Gallahad::Attack()
{
	//Starts attack timer
	attacking.Start();
	//Generates attack object
	StageState::AddObject(new Projectile("Melee.png", 2, 0, this, Vec2(0.6, 0), 800, 1, true));
}

void Gallahad::Hide()
{
	hiding.Start();
	energy -= 1;
	clamp(energy,0,5);
}

void Gallahad::Crouch()
{
	crouching = true;
}

void Gallahad::Stand()
{
	crouching = false;
}

bool Gallahad::Attacking()
{
	return attacking.IsRunning();
}

bool Gallahad::Hiding()
{
	return hiding.IsRunning();
}

bool Gallahad::Crouching()
{
	return crouching;
}

void Gallahad::NotifyTileCollision(int tile, Face face)
{
	if(tile > 11)
	{
		Damage(1);
	}
}

void Gallahad::NotifyObjectCollision(GameObject* other)
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

void Gallahad::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	hiding.Update(dt);
	regenerating.Update(dt);
}

void Gallahad::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	inputComponent.Update(this,dt);
	physicsComponent.Update(this,world,dt);
	graphicsComponent.Update(this,dt);
}

void Gallahad::Render()
{
	graphicsComponent.Render(GetPosition()-Camera::GetInstance().pos);
}
