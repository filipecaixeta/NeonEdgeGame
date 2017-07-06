#include "Character.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"

Character::Character(int x,int y):
	GameObject(),
	physicsComponent(),
	graphicsComponent(nullptr),
	saveComponent(),
	hitpoints(10),
	power(1),
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
	if (hitpoints<=0)
	{
		if (!dieTimer.IsRunning())
			dieTimer.Start();
	}
	return isDead;
}

bool Character::IsCharacter()
{
	return true;
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

void Character::Empower(int pow)
{
	power = pow;
}

int Character::Power()
{
	return power;
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
	if(tile > 30)
	{
		Damage(1);
	}
	if(tile >= SOLID_TILE && (face == LEFT || face == RIGHT))
	{
		if(physicsComponent.velocity.y >= 0.6)
		{
			physicsComponent.velocity.y = -0.5;
		}
	}
}

void Character::NotifyObjectCollision(GameObject* other)
{
	if(!IsPlayer() || !other->IsPlayer())
	{
		SolidCollision(other);
	}
	if(!IsPlayer())
	{
		if(other->IsPlayer())
		{
			Player* c = (Player*) other;
			if(c->Attacking())
				Damage(c->Power());
		}
		if(other->Is("Projectile"))
		{
			Projectile* p = (Projectile*) other;
			if(p->GetOwner()->IsPlayer())
			{
				Damage(p->Power());
			}
		}
	}
	if(other->Is("Door"))
	{
		if(box.x < other->box.x - 1)
		{
			SetPosition(Vec2(other->box.x-box.w-1,box.y));
		}
		else
		{
			SetPosition(Vec2(other->box.x+other->box.w+1,box.y));
		}
	}
	/*if(other->Is("Box") || other->Is("Plattform"))
	{
		if(physicsComponent.velocity.x < 0 && footing == GROUNDED)
		{
			if(box.x < other->box.x+other->box.w && box.x+box.w > other->box.x+other->box.w)
			{
				SetPosition(Vec2(other->box.x+other->box.w+1,box.y));
			}
		}
		else if(physicsComponent.velocity.x > 0 && footing == GROUNDED)
		{
			if(box.x+box.w > other->box.x && box.x < other->box.x)
			{
				SetPosition(Vec2(other->box.x-box.w-1,box.y));
			}
		}
		else if(footing != GROUNDED && box.x+box.w - 40 > other->box.x)
		{
			if(box.y+box.h > other->box.y && box.y < other->box.y)
			{
				SetPosition(Vec2(box.x,other->box.y-box.h-1));
				if(lastFooting != GROUNDED)
					lastFooting = footing;
				footing = GROUNDED;
				if(other->Is("Plattform"))
				{
					Plattform* p = (Plattform*) other;
					if(p->on)
					{
						if(p->box.x - p->route[p->cycleCount][0] > 10 || p->box.x - p->route[p->cycleCount][0] < - 10 || p->box.y - p->route[p->cycleCount][1] > 10 || p->box.y - p->route[p->cycleCount][1] < - 10 )
						{
								if(p->box.y != p->route[p->cycleCount][1])
								{
									box.x += p->route[p->cycleCount][2]*(p->route[p->cycleCount][0]-p->box.x)/abs(((p->route[p->cycleCount][1])-p->box.y));
								}
								else if(p->box.x < p->route[p->cycleCount][0])
								{
									box.x +=p->route[p->cycleCount][2];
								}	
								else
								{
									box.x -= p->route[p->cycleCount][2];	
								}
						}
						else
						{
							box.x += p->box.x - p->route[p->cycleCount][0];
							box.y += p->box.y - p->route[p->cycleCount][1];
						}	
					}
				}
			}
		}
		graphicsComponent->Update(this,0);
	}*/
}

void Character::UpdateTimers(float dt)
{
	dieTimer.Update(dt);
	if (dieTimer.GetElapsed() == 1)
		isDead = true;
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
