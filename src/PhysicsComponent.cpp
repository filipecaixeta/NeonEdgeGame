#include <PhysicsComponent.h>
#include <TileMap.h>
#include <Rect.h>
#include <Vec2.h>
#include <StageState.h>

PhysicsComponent::PhysicsComponent()
{

}

void PhysicsComponent::Update(GameObject *obj, float dt)
{
	Vec2 position;
	Vec2 speed;

	//Gravidade
	obj->speed.y += 0.002*dt;
	clamp(obj->speed.y,-1.8f,1.8f);

	position = obj->GetPosition();
	speed = obj->speed;
	position.x += speed.x*dt;
	obj->SetPosition(position);
	MapColisionX(obj);

	position = obj->GetPosition();
	speed = obj->speed;
	position.y += speed.y*dt;
	obj->SetPosition(position);
	MapColisionY(obj);
}

bool PhysicsComponent::MapColisionX(GameObject *obj)
{
	Vec2 speed = obj->speed;
	TileMap* map = StageState::GetTileMap();
	Rect colisionBox = obj->box;
	colisionBox.SetXY(colisionBox.GetXY()+Vec2(1.0f,1.0f));
	colisionBox.SetWH(colisionBox.GetWH()-Vec2(2.0f,2.0f));

	int minX = colisionBox.x/map->GetTileWidth();
	int minY = colisionBox.y/map->GetTileHeight();
	int maxX = (colisionBox.x+colisionBox.w)/map->GetTileWidth();
	int maxY = (colisionBox.y+colisionBox.h)/map->GetTileHeight();
	clamp(minX,0,map->GetWidth());
	clamp(minY,0,map->GetHeight());
	clamp(maxX,0,map->GetWidth());
	clamp(maxY,0,map->GetHeight());

	for(int x = minX; x <= maxX; x++)
	{
		for(int y = minY; y <= maxY; y++)
		{
			Rect tile = map->GetAABB(x,y);
			if(map->At(x,y,0) > 5)
			{
				if(speed.x<=0)
				{
					if(colisionBox.x < tile.x+tile.w && colisionBox.x+colisionBox.w > tile.x+tile.w)
					{
						colisionBox.x = tile.x+tile.w+1;
						Vec2 box = obj->GetPosition();
						box.x = colisionBox.x-1;
						obj->SetPosition(box);
						obj->speed.x = 0;
	//					if(map->At(x,y,0) > 11)
	//						Damage(1);
	//					if(jumping)
	//					{
	//						if(lastWallJumping != 1)
	//							jumping = false;
	//						wallJumping = 1;
	//					}
						return true;
					}
				}
				else
				{
					if(colisionBox.x+colisionBox.w > tile.x && colisionBox.x < tile.x)
					{
						colisionBox.x = tile.x-colisionBox.w-1;
						Vec2 box = obj->GetPosition();
						box.x = colisionBox.x-1;
						obj->SetPosition(box);
						obj->speed.x = 0;
	//					if(map->At(x,y,0) > 11)
	//						Damage(1);
	//					if(jumping)
	//					{
	//						if(lastWallJumping != 2)
	//							jumping = false;
	//						wallJumping = 2;
	//					}
						return true;
					}
				}

			}
		}
	}
}

bool PhysicsComponent::MapColisionY(GameObject *obj)
{
	Vec2 speed = obj->speed;
	TileMap* map = StageState::GetTileMap();
	Rect colisionBox = obj->box;
	colisionBox.SetXY(colisionBox.GetXY()+Vec2(1.0f,1.0f));
	colisionBox.SetWH(colisionBox.GetWH()-Vec2(2.0f,2.0f));

	int minX = colisionBox.x/map->GetTileWidth();
	int minY = colisionBox.y/map->GetTileHeight();
	int maxX = (colisionBox.x+colisionBox.w)/map->GetTileWidth();
	int maxY = (colisionBox.y+colisionBox.h)/map->GetTileHeight();
	clamp(minX,0,map->GetWidth());
	clamp(minY,0,map->GetHeight());
	clamp(maxX,0,map->GetWidth());
	clamp(maxY,0,map->GetHeight());

	for(int x = minX; x <= maxX; x++)
	{
		for(int y = minY; y <= maxY; y++)
		{
			Rect tile = map->GetAABB(x,y);
			if(map->At(x,y,0) > 5)
			{
				//Cima
				if(speed.y<=0)
				{
					if(colisionBox.y < tile.y+tile.h && colisionBox.y+colisionBox.h > tile.y+tile.h)
					{
						colisionBox.y = tile.y+tile.h+1;
						Vec2 box = obj->GetPosition();
						box.y = colisionBox.y-1;
						obj->SetPosition(box);
						obj->speed.y = 0;
//						if(map->At(x,y,0) > 11)
//							Damage(1);
						return true;
					}
				}
				//Baixo
				else
				{
					if(colisionBox.y+colisionBox.h > tile.y && colisionBox.y < tile.y)
					{
						colisionBox.y = tile.y-colisionBox.h-1;
						Vec2 box = obj->GetPosition();
						box.y = colisionBox.y-1;
						obj->SetPosition(box);
						obj->speed.y = 0.6;
						obj->wallJumping = 0;
						obj->jumping = false;
//						if(map->At(x,y,0) > 11)
//							Damage(1);
						return true;
					}
				}
			}
		}
	}
}
