#include "Player.h"
#include "Projectile.h"

Player::Player(ItensManager* itemManager, int x, int y):
	Character(x,y),
	inputComponent(nullptr),
	itemManager(itemManager),
	soundComponent(nullptr),
	skills({false,false,true,true,true,false,false}),
	skillPoints(0),
	energy(5),
	regenCD(500),
	crouching(false),
	crouchingEdge(true)
{
	name = "Player";
	hitpoints = MAX_HITPOINTS;
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
	if(crouchingEdge)
	{
		crouchingEdge = false;
		soundComponent->Crouching();
	}
	crouching = true;
}

void Player::Stand()
{
	crouching = false;
	crouchingEdge = true;
}

bool Player::Crouching()
{
	return crouching;
}

void Player::EvalItem(std::string itemName)
{
	if (itemName == "Healing Potion 25")
	{
		hitpoints += MAX_HITPOINTS*0.5;
		clamp(hitpoints,0,MAX_HITPOINTS);
	}
	if (itemName == "Healing Potion 50")
	{
		hitpoints += MAX_HITPOINTS*0.5;
		clamp(hitpoints,0,MAX_HITPOINTS);
	}
	if (itemName == "Energy Potion 25")
	{
		energy += 2;
		clamp(energy,0,5);
	}
	if (itemName == "Energy Potion 50")
	{
		energy += 5;
		clamp(energy,0,5);
	}
	if (itemName == "Skill Coin"){
		skillPoints++;
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
		if(!(p->GetOwner() == "Gallahad"))
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
