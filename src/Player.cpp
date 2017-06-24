#include "Player.h"
#include "Projectile.h"

Player::Player(int x, int y):
	Character(x,y),
	inputComponent(nullptr),
	energy(5),
	regenCD(500),
	crouching(false)
{

}

Player::~Player()
{

}

int Player::GetEnergy()
{
	return energy;
}

void Player::Crouch()
{
	crouching = true;
}

void Player::Stand()
{
	crouching = false;
}

bool Player::Crouching()
{
	return crouching;
}

void Player::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Notfredo"))
	{
		Character* c = (Character*) other;
		if(c->Attacking())
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
		if(crouching && !regenCD.IsRunning())
		{
			regenCD.Start();
			energy += 1;
			clamp(energy,0,5);
		}
	}
}

bool Player::OutOfBounds(TileMap* map)
{
	return (box.x < 0 || box.x > (map->GetWidth()-1)*map->GetTileWidth() ||
			box.y < 0 || box.y > (map->GetHeight()-1)*map->GetTileHeight());
}

void Player::UpdateTimers(float dt)
{
	Character::UpdateTimers(dt);
	regenCD.Update(dt);
}

void Player::Update(TileMap* map, float dt)
{
	UpdateTimers(dt);
	inputComponent->Update(this,dt);
	physicsComponent.Update(this,map,dt);
	if(OutOfBounds(map))
		SetPosition(Vec2(269,544));
	graphicsComponent->Update(this,dt);
}