#include "Player.h"
#include "Projectile.h"

Player::Player(ItensManager* itemManager, int x, int y):
	Character(x,y),
	inputComponent(nullptr),
	itemManager(itemManager),
	skills({false,false,true,true,true,false,false}),
	skillPoints(2),
	energy(5),
	regenCD(500),
	crouching(false)
{
	name = "Player";
}

Player::~Player()
{

}

bool Player::IsPlayer()
{
	return true;
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
	if (itemName == "Healing Potion")
	{
		hitpoints += 5;
		clamp(hitpoints,0,10);
	}
}

void Player::NotifyObjectCollision(GameObject* other)
{
	Character::NotifyObjectCollision(other);
	if(other->IsCharacter() && !other->IsPlayer())
	{
		Character* c = (Character*) other;
		if(c->Attacking())
			Damage(c->Power());
	}
	if(other->Is("Projectile"))
	{
		Projectile* p = (Projectile*) other;
		if(!p->GetOwner()->IsPlayer())
			Damage(p->Power());
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
	if(other->Is("Life"))
	{
		if(crouching && !regenCD.IsRunning())
		{
			regenCD.Start();
			hitpoints += 1;
			clamp(hitpoints,0,10);
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
