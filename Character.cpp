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
	physicsComponent(),
	graphicsComponent(nullptr),
	saveComponent(),
	hitpoints(10),
	invincibilityTimer(500),
	attacking(200),
	attackCD(500)
{
	box.SetXY(Vec2(x,y));
	facing = RIGHT;
	startingX = x;
	startingY = y;
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

bool Character::Attacking()
{
	return attacking.IsRunning();
}

bool Character::Cooling()
{
	return attackCD.IsRunning();
}


bool Character::GetColisionData(SDL_Surface** surface_,SDL_Rect &clipRect_,Vec2 &pos_, bool &mirror)
{
	*surface_ = graphicsComponent->GetSurface();
	clipRect_ = graphicsComponent->GetClip();
	pos_ = box.GetXY();
	mirror = graphicsComponent->GetMirror();
	return true;
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
	if(other->Is("Door"))
	{
		if(facing == RIGHT)
		{
			SetPosition(Vec2(GetPosition().x-2,GetPosition().y));
		}
		else
		{
			SetPosition(Vec2(GetPosition().x+2,GetPosition().y));
		}
	}
	if(other->Is("Box"))
	{
		if((facing == RIGHT) && (footing == GROUNDED))
		{
			SetPosition(Vec2(GetPosition().x-2,GetPosition().y));
		}
		else if ((facing == LEFT) && (footing == GROUNDED))
		{
			SetPosition(Vec2(GetPosition().x+2,GetPosition().y));
		}
		else
		{
			SetPosition(Vec2(GetPosition().x,GetPosition().y-2));
		}
	}
}

void Character::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	if(attacking.GetElapsed() == 1)
	{
		attacking.Reset();
		attackCD.Start();
	}
	attackCD.Update(dt);
}

bool Character::OutOfBounds(TileMap* map)
{
	return (box.x < 0 || box.x > (map->GetWidth()-1)*map->GetTileWidth() ||
			box.y < 0 || box.y > (map->GetHeight()-1)*map->GetTileHeight());
}

void Character::Update(TileMap* map, float dt)
{
	UpdateTimers(dt);
	physicsComponent.Update(this,map,dt);
	if(OutOfBounds(map))
		SetPosition(Vec2(startingX,startingY));
	graphicsComponent->Update(this,dt);
}

void Character::Render()
{
	graphicsComponent->Render(GetPosition()-Camera::GetInstance().pos);
}
