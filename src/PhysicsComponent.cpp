#include "PhysicsComponent.h"
#include "Vec2.h"
#include "Rect.h"
#include "TileMap.h"
#include "StageState.h"

PhysicsComponent::PhysicsComponent()
{

}

void PhysicsComponent::Update(GameObject* obj, float dt)
{
	//Gravity
	if(obj->speed.y >= 0.1 && (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED))
	{
		obj->speed.y = 0.1;//-= 0.001*dt;
	}
	else if(obj->speed.y == 0.1 && obj->footing == GameObject::AIRBORNE)
	{
		obj->speed.y = 0.6;
	}
	else
	{
		obj->speed.y += 0.002*dt;
	}
	clamp(obj->speed.y,-1.8f,1.8f);

	obj->box.x += obj->speed.x*dt;
	if(obj->speed.x < 0)
		obj->NotifyTileCollision(TileCollision(obj, GameObject::LEFT), GameObject::LEFT);
	else
		obj->NotifyTileCollision(TileCollision(obj, GameObject::RIGHT), GameObject::RIGHT);

	obj->box.y += obj->speed.y*dt;
	if(obj->speed.y < 0)
		obj->NotifyTileCollision(TileCollision(obj, GameObject::UPPER), GameObject::UPPER);
	else
		obj->NotifyTileCollision(TileCollision(obj, GameObject::BOTTOM), GameObject::BOTTOM);
}

int PhysicsComponent::TileCollision(GameObject* obj, GameObject::Face face)
{
	if((face == GameObject::LEFT || face == GameObject::RIGHT) || 
	   (obj->footing != GameObject::LEFT_WALLED && obj->footing != GameObject::RIGHT_WALLED))
	{
		obj->footing = GameObject::AIRBORNE;
	}

	TileMap* map = StageState::GetTileMap();
	Rect box = obj->box;
	box.SetXY(box.GetXY()+Vec2(1.0f,1.0f));
	box.SetWH(box.GetWH()-Vec2(2.0f,2.0f));

	int minX = box.x/map->GetTileWidth();
	int minY = box.y/map->GetTileHeight();
	int maxX = (box.x+box.w)/map->GetTileWidth();
	int maxY = (box.y+box.h)/map->GetTileHeight();
	clamp(minX,0,map->GetWidth()-1);
	clamp(minY,0,map->GetHeight()-1);
	clamp(maxX,0,map->GetWidth()-1);
	clamp(maxY,0,map->GetHeight()-1);

	for(int x = minX; x <= maxX; x++)
	{
		for(int y = minY; y <= maxY; y++)
		{
			if(map->At(x,y,0) >= SOLID_TILE)
			{
				Rect tile = map->GetTileBox(x,y);
				if(face == GameObject::LEFT)
				{
					if(box.x+2 < tile.x+tile.w && box.x+box.w+2 > tile.x+tile.w)
					{
						obj->footing = GameObject::LEFT_WALLED;
					}
					if(box.x < tile.x+tile.w && box.x+box.w > tile.x+tile.w)
					{
						box.x = tile.x+tile.w+2;
						obj->box.x = box.x;
						return map->At(x,y,0);
					}
				}
				else if(face == GameObject::RIGHT)
				{
					if(box.x+box.w-2 > tile.x && box.x-2 < tile.x)
					{
						obj->footing = GameObject::RIGHT_WALLED;
					}
					if(box.x+box.w > tile.x && box.x < tile.x)
					{
						box.x = tile.x-box.w-2;
						obj->box.x = box.x;
						return map->At(x,y,0);
					}
				}
				else if(face == GameObject::UPPER)
				{
					if(box.y < tile.y+tile.h && box.y+box.h > tile.y+tile.h)
					{
						box.y = tile.y+tile.h+2;
						obj->box.y = box.y;
						obj->speed.y = 0;
						return map->At(x,y,0);
					}
				}
				else if(face == GameObject::BOTTOM)
				{
					if(box.y+box.h > tile.y && box.y < tile.y)
					{
						box.y = tile.y-box.h-2;
						obj->box.y = box.y;
						obj->speed.y = 0.6;
						if(obj->lastFooting != GameObject::GROUNDED)
							obj->lastFooting = obj->footing;
						obj->footing = GameObject::GROUNDED;
						obj->jumping = false;
						return map->At(x,y,0);
					}
				}
			}
		}
	}

	return 0;
}
