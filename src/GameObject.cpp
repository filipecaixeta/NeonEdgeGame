#include "GameObject.h"
#include "Character.h"
#include "Game.h"

GameObject::~GameObject()
{

}

bool GameObject::Is(std::string type)
{
	return (type == name);
}

bool GameObject::IsDead()
{
	return isDead;
}

bool GameObject::IsCharacter()
{
	return false;
}

bool GameObject::IsPlayer()
{
	return false;
}

Vec2 GameObject::GetPosition()
{
	return Vec2(box.x, box.y);
}

void GameObject::SetPosition(Vec2 pos)
{
	box.x = pos.x;
	box.y = pos.y;
}

void GameObject::NotifyTileCollision(int tile, Face face)
{

}

void GameObject::NotifyObjectCollision(GameObject* other)
{

}

void GameObject::SolidCollision(GameObject* other)
{
	if(IsCharacter())
	{
		Character* c = (Character*) this;
		int y = box.y-c->physicsComponent.velocity.y*Game::GetInstance().GetDeltaTime();
		if(footing != GROUNDED && y+box.h < other->box.y)
		{
			box.y = other->box.y-box.h-1;
			c->physicsComponent.velocity.y = 0.6;
			if(lastFooting != GROUNDED)
				lastFooting = footing;
			footing = GROUNDED;
		}
		else
		{
			if(c->physicsComponent.velocity.x < 0)
			{
				if(box.x < other->box.x+other->box.w && box.x+box.w > other->box.x+other->box.w)
				{
					box.x = other->box.x+other->box.w+1;
				}
			}
			else if(c->physicsComponent.velocity.x > 0)
			{
				if(box.x+box.w > other->box.x && box.x < other->box.x)
				{
					box.x = other->box.x-box.w-1;
				}
			}
		}
		c->graphicsComponent->Update(this,0);
	}
}

bool GameObject::GetColisionData(SDL_Surface** surface_, SDL_Rect& clipRect_, Vec2& pos_, bool& mirror)
{
	return false;
}

void GameObject::DieAnimation()
{
	dieTimer.Start();
}

void GameObject::Render()
{

}
