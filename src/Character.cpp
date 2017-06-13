#include "Character.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Character::Character(int x,int y):
	GameObject(),
	inputComponent(nullptr),
	physicsComponent(),
	graphicsComponent(nullptr),
	saveComponent(),
	hitpoints(10),
	energy(5),
	invincibilityTimer(500),
	attacking(500),
	regenerating(500),
	crouching(false)
{
	box.SetXY(Vec2(x,y));
	facing = RIGHT;
}

Character::~Character()
{

}

bool Character::IsDead()
{
	return (hitpoints < 1);
}

int Character::GetHealth()
{
	return hitpoints;
}

int Character::GetEnergy()
{
	return energy;
}

void Character::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning())
	{
		hitpoints -= (damage);
		invincibilityTimer.Start();
	}
}

void Character::Attack()
{

}

void Character::Crouch()
{
	crouching = true;
}

void Character::Stand()
{
	crouching = false;
}

bool Character::Attacking()
{
	return attacking.IsRunning();
}

bool Character::Crouching()
{
	return crouching;
}

void Character::NotifyTileCollision(int tile, Face face)
{
	if(tile > 11)
	{
		Damage(1);
	}
}

void Character::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Melee"))
	{
		Melee* m = (Melee*) other;
		if(m->owner->Is("Notfredo"))
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

bool Character::GetColisionData(SDL_Surface** surface_,SDL_Rect &clipRect_,Vec2 &pos_, bool &mirror)
{
	*surface_ = graphicsComponent->GetSurface();
	clipRect_ = graphicsComponent->GetClip();
	pos_ = box.GetXY();
	mirror = graphicsComponent->GetMirror();
	return true;
}

void Character::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	regenerating.Update(dt);
}

void Character::Update(TileMap* map, float dt)
{
	UpdateTimers(dt);
	inputComponent->Update(this,dt);
	physicsComponent.Update(this,map,dt);
	graphicsComponent->Update(this,dt);
}

void Character::Render()
{
	graphicsComponent->Render(GetPosition()-Camera::GetInstance().pos);
}
