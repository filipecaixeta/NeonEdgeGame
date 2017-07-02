#include "Player.h"
#include "Projectile.h"

Player::Player(ItensManager* itemManager, int x, int y):
	Character(x,y),
	inputComponent(nullptr),
	energy(5),
	regenCD(500),
	itemManager(itemManager),
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

void Player::EvalItem(std::string itemName)
{
	if (itemName=="Healing Potion")
	{
		hitpoints += 5;
		clamp(hitpoints,0,10);
	}
}

void Player::NotifyObjectCollision(GameObject* other)
{
	Character::NotifyObjectCollision(other);
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
		SetPosition(Vec2(startingX,startingY));
	graphicsComponent->Update(this,dt);
}

bool Player::Is(std::string type)
{
	return type=="Player";
}
