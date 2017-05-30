#include "PhysicsComponent.h"
#include "Vec2.h"
#include "Rect.h"

PhysicsComponent::PhysicsComponent(bool kinetic)
{
	PhysicsComponent::kinetic = kinetic;
}

void PhysicsComponent::Update(GameObject* obj, TileMap* world, float dt)
{
	//Gravity
	if(!kinetic)
	{
		if(velocity.y >= 0.1 && (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED))
		{
			velocity.y = 0.1;//-= 0.001*dt;
		}
		else if(velocity.y == 0.1 && obj->footing == GameObject::AIRBORNE)
		{
			velocity.y = 0.6;
		}
		else
		{
			velocity.y += 0.002*dt;
		}
		clamp(velocity.y,-1.8f,1.8f);
	}

	//Apply velocity in x
	obj->box.x += velocity.x*dt;
	if(velocity.x < 0)
		obj->NotifyTileCollision(TileCollision(obj, world, GameObject::LEFT), GameObject::LEFT);
	else
		obj->NotifyTileCollision(TileCollision(obj, world, GameObject::RIGHT), GameObject::RIGHT);

	//Apply velocity in y
	obj->box.y += velocity.y*dt;
	if(velocity.y < 0)
		obj->NotifyTileCollision(TileCollision(obj, world, GameObject::UPPER), GameObject::UPPER);
	else
		obj->NotifyTileCollision(TileCollision(obj, world, GameObject::BOTTOM), GameObject::BOTTOM);
}

int PhysicsComponent::TileCollision(GameObject* obj, TileMap* world, GameObject::Face face)
{
	if((face == GameObject::LEFT || face == GameObject::RIGHT) || 
	   (obj->footing != GameObject::LEFT_WALLED && obj->footing != GameObject::RIGHT_WALLED))
	{
		obj->footing = GameObject::AIRBORNE;
	}

	Rect box = obj->box;
	box.SetXY(box.GetXY()+Vec2(1.0f,1.0f));
	box.SetWH(box.GetWH()-Vec2(2.0f,2.0f));

	int minX = box.x/world->GetTileWidth();
	int minY = box.y/world->GetTileHeight();
	int maxX = (box.x+box.w)/world->GetTileWidth();
	int maxY = (box.y+box.h)/world->GetTileHeight();
	clamp(minX,0,world->GetWidth()-1);
	clamp(minY,0,world->GetHeight()-1);
	clamp(maxX,0,world->GetWidth()-1);
	clamp(maxY,0,world->GetHeight()-1);

	for(int x = minX; x <= maxX; x++)
	{
		for(int y = minY; y <= maxY; y++)
		{
			if(world->At(x,y,0) >= SOLID_TILE)
			{
				Rect tile = world->GetTileBox(x,y);
				if(face == GameObject::LEFT)
				{
					if(box.x+2 < tile.x+tile.w && box.x+box.w+2 > tile.x+tile.w)
					{
						obj->footing = GameObject::LEFT_WALLED;
					}
					if(box.x <= tile.x+tile.w && box.x+box.w >= tile.x+tile.w)
					{
						box.x = tile.x+tile.w+2;
						obj->box.x = box.x;
						return world->At(x,y,0);
					}
				}
				else if(face == GameObject::RIGHT)
				{
					if(box.x+box.w-2 > tile.x && box.x-2 < tile.x)
					{
						obj->footing = GameObject::RIGHT_WALLED;
					}
					if(box.x+box.w >= tile.x && box.x <= tile.x)
					{
						box.x = tile.x-box.w-2;
						obj->box.x = box.x;
						return world->At(x,y,0);
					}
				}
				else if(face == GameObject::UPPER)
				{
					if(box.y < tile.y+tile.h && box.y+box.h > tile.y+tile.h)
					{
						box.y = tile.y+tile.h+2;
						obj->box.y = box.y;
						if(!kinetic)
							velocity.y = 0;
						return world->At(x,y,0);
					}
				}
				else if(face == GameObject::BOTTOM)
				{
					if(box.y+box.h > tile.y && box.y < tile.y)
					{
						box.y = tile.y-box.h-2;
						obj->box.y = box.y;
						if(!kinetic)
							velocity.y = 0.6;
						if(obj->lastFooting != GameObject::GROUNDED)
							obj->lastFooting = obj->footing;
						obj->footing = GameObject::GROUNDED;
						return world->At(x,y,0);
					}
				}
			}
		}
	}

	return -1;
}
