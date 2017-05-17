#include "Notfredo.h"
#include "InputManager.h"
#include "Camera.h"
#include "StageState.h"

Notfredo::Notfredo(int x, int y)
{
    sprites.emplace("Idle", new Sprite("NotfredoIdle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite("NotfredoRunning.png", 8, 120, true));
    sp = sprites["Idle"];
	box = Rect(x+1, y+1, sp->GetWidth()-2, sp->GetHeight()-2);
	speed = Vec2(0.2, 0.6);
	hitpoints = 5;
	power = 1;
	defense = 0;
	invincibilityT = Timer(500);
	attackT = Timer(1000);
	idle = Timer(1500);
	idle.Start();
	looking = Timer(1500);
    facing = RIGHT;
}

Notfredo::~Notfredo()
{
	sp = nullptr;
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
}

void Notfredo::Update(float dt)
{
	UpdateTimers(dt);
	UpdatePosition(dt);
	speed.y += 0.06;
	sp->Update(dt);
}

void Notfredo::UpdateTimers(float dt)
{
	invincibilityT.Update(dt);
	attackT.Update(dt);
	statusTimer.Update(dt);
	if(!statusTimer.isRunning())
		status = NORMAL;
}

void Notfredo::UpdatePosition(float dt)
{
	radius = Rect(box.x-200, box.y-200, box.w+400, box.h+400);
	if(Godofredo::player)
	{
		if(status != STUNNED)
		{
			Rect player = Godofredo::player->box;
			if(StageState::IsColliding(radius, player) && !Godofredo::player->IsHidden())
			{
				speed.x = 0.3;
				if(player.x < box.x)
				{
					if(!attackT.isRunning())
					{
						StageState::AddObject(new Notattack("notattack.png", 2, box.x+(box.w/2), box.y, power, 200, facing));
						attackT.Start();
					}
					if(box.x - speed.x*dt < player.x)
						box.x = player.x;
					else
						box.x -= speed.x*dt;
					sp->Mirror(true);
					UpdateSprite("Running");
					facing = LEFT;
				}
				else
				{
					if(!attackT.isRunning())
					{
						StageState::AddObject(new Notattack("notattack.png", 2, box.x+(box.w/2), box.y, power, 200, facing));
						attackT.Start();
					}
					if(box.x + speed.x*dt > player.x)
						box.x = player.x;
					else
						box.x += speed.x*dt;
					sp->Mirror(false);
					UpdateSprite("Running");
					facing = RIGHT;
				}
				NotifyTileCollision(facing);
			}
			else if(looking.isRunning())
			{
				speed.x = 0.2;
				if(facing == LEFT)
				{
					box.x -= speed.x*dt;
					sp->Mirror(true);
					UpdateSprite("Running");
				}
				else
				{
					box.x += speed.x*dt;
					sp->Mirror(false);
					UpdateSprite("Running");
				}
				NotifyTileCollision(facing);
				looking.Update(dt);
				if(!looking.isRunning())
					idle.Start();
			}
			else
			{
				if(idle.getElapsed() == 0)
				{
					if(facing == LEFT)
					{
						facing = RIGHT;
						sp->Mirror(true);
						UpdateSprite("Idle");
					}
					else
					{
						facing = LEFT;
						sp->Mirror(false);
						UpdateSprite("Idle");
					}
				}
				idle.Update(dt);
				if(!idle.isRunning())
					looking.Start();
			}
		}
	}
	box.y += speed.y*dt;
	if(speed.y < 0)
		NotifyTileCollision(UPPER);
	else
		NotifyTileCollision(BOTTOM);
}

void Notfredo::UpdateSprite(std::string sprite)
{
	if(sp != sprites[sprite])
	{
		int w = sp->GetWidth();
		int h = sp->GetHeight();
		sp = sprites[sprite];
		box.x += (w-sp->GetWidth())/2;
		box.y += h-sp->GetHeight();
		box.w = sp->GetWidth();
		box.h = sp->GetHeight();
	}
}

void Notfredo::Render()
{
	sp->Render(box.x - Camera::GetInstance().pos.x -1, box.y - Camera::GetInstance().pos.y -1);
}

void Notfredo::Damage(int damage)
{
	if(!invincibilityT.isRunning())
	{
		hitpoints -= (damage-defense);
		invincibilityT.Start();
	}
}

bool Notfredo::NotifyTileCollision(Face face)
{
	TileMap* map = StageState::GetTileMap();
	unsigned limitX = ((box.x+box.w)/map->GetTileWidth() < map->GetWidth()) ? ((box.x+box.w)/map->GetTileWidth()) : (map->GetWidth());
	unsigned limitY = ((box.y+box.h)/map->GetTileHeight() < map->GetHeight()) ? ((box.y+box.h)/map->GetTileHeight()) : (map->GetHeight());

	for(unsigned x = box.x/map->GetTileWidth(); x <= limitX; x++)
	{
		for(unsigned y = box.y/map->GetTileHeight(); y <= limitY; y++)
		{
			if(face == LEFT)
			{
				if(map->At(x,y,0) > 5)
				{
					Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
					if(box.x < tile.x+tile.w && box.x+box.w > tile.x+tile.w)
					{
						if(map->At(x,y-1,0) < 6 && map->At(x+1,y+1,0) > 5)
							speed.y = -0.46;
						box.x = tile.x+tile.w+1;
						speed.x = 0;
						return true;
					}
				}
			}
			if(face == RIGHT)
			{
				if(map->At(x,y,0) > 5)
				{
					Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
					if(box.x+box.w > tile.x && box.x < tile.x)
					{
						if(map->At(x,y-1,0) < 6 && map->At(x-1,y+1,0) > 5)
							speed.y = -0.46;
						box.x = tile.x-box.w-1;
						speed.x = 0;
						return true;
					}
				}
			}
			if(face == UPPER)
			{
				if(map->At(x,y,0) > 5)
				{
					Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
					if(box.y < tile.y+tile.h && box.y+box.h > tile.y+tile.h)
					{
						box.y = tile.y+tile.h+1;
						return true;
					}
				}
			}
			if(face == BOTTOM)
			{
				if(map->At(x,y,0) > 5)
				{
					Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
					if(box.y+box.h > tile.y && box.y < tile.y)
					{
						box.y = tile.y-box.h-1;
						speed.y = 0.6;
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Notfredo::NotifyCollision(GameObject* other)
{
	if(other->Is("Attack"))
	{
		if(other->facing == facing)
			Damage(other->power*2);
		else
			Damage(other->power);
	}
}

bool Notfredo::Is(std::string type)
{
	return (type == "Notfredo");
}

bool Notfredo::IsDead()
{
	return (hitpoints < 1);
}

Notfredo* Notfredo::get()
{
	return this;
}

