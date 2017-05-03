#include "Godofredo.h"
#include "InputManager.h"
#include "Camera.h"
#include "StageState.h"
#include <iostream>
#include <math.h>
#define clamp(N,L,U) N=std::max((float)L,std::min(N,(float)U))

Godofredo* Godofredo::player = nullptr;

Godofredo::Godofredo(int x, int y) {
	if(player) {
		printf("Multiple Player Instances\n");
		exit(EXIT_FAILURE);
	}else{
		player = this;
	}

    sprites.emplace("Idle", new Sprite("LancelotIdleRight.png", 8, 120,true));
    sprites.emplace("Running", new Sprite("LancelotRunningRight.png", 8, 120,true));

    currentSprite = sprites["Idle"];

    box = Rect(x+1, y+1, currentSprite->GetWidth()-2, currentSprite->GetHeight()-2);

	hitpoints = 10;
	power = 1;
	defense = 0;
	speed = Vec2(0, 0.6);

	facing = RIGHT;

    healthBar = Sprite("healthBar.png", 11);
    healthBar.SetFrameNormalized(1.0f);
    stealthBar = Sprite("stealthBar.png", 11);
    stealthBar.SetFrameNormalized(0.0f);

	invincibilityT = Timer(500);
	attackT = Timer(500);
    hiddenT = Timer(1000);
}

Godofredo::~Godofredo() {
	player = nullptr;
    for ( auto it = sprites.begin(); it != sprites.end(); ++it )
    {
        delete it->second;
    }
    sprites.clear();
}

void Godofredo::UpdateTimers(float dt) {
    invincibilityT.Update(dt);
    attackT.Update(dt);
    hiddenT.Update(dt);

    attacking = attackT.isRunning();
    if (hiddenT.isRunning())
    {
        stealthBar.SetFrameNormalized(hiddenT.getElapsed());
    }
    else
    {
        stealthBar.SetFrameNormalized(0);
    }
}

void Godofredo::Update(float dt)
{
    invincibilityT.Update(dt);
    attackT.Update(dt);
    hiddenT.Update(dt);

    if(InputManager::GetInstance().IsKeyDown(SDLK_a))
        RunState(MOVE_LEFT,dt);
    else if(InputManager::GetInstance().IsKeyDown(SDLK_d))
        RunState(MOVE_RIGHT,dt);
    else
        RunState(NONE,dt);

    if(InputManager::GetInstance().IsKeyDown(SDLK_e))
        AttackState(dt);

    if(InputManager::GetInstance().IsKeyDown(SDLK_SPACE))
        JumpState(dt);

    if (InputManager::GetInstance().IsKeyDown(SDLK_s))
        InvisibleState(dt);

    if (hiddenT.isRunning())
    {
        stealthBar.SetFrameNormalized(hiddenT.getElapsed());
        alpha = 0.3;
    }
    else
    {
        stealthBar.SetFrameNormalized(0);
        alpha = 1.0;
    }

    UpdatePosition(dt);



    currentSprite->SetAlpha(alpha);
    currentSprite->Mirror(mirror);
    currentSprite->Update(dt);
}

void Godofredo::RunState(StateT s,float dt)
{
    if(s == StateT::MOVE_LEFT)
    {
        speed.x -= 0.002*dt;
        mirror = true;
        currentSprite = sprites["Running"];
        facing = LEFT;
        //Update bounding box
    }
    else if(s == StateT::MOVE_RIGHT)
    {
        speed.x += 0.002*dt;
        mirror = false;
        currentSprite = sprites["Running"];
        facing = RIGHT;
        //Update bounding box
    }
    else if (s == StateT::NONE)
    {
        speed.x = 0;
        currentSprite = sprites["Idle"];
    }
    clamp(speed.x,-0.4,0.4);
    speed.y += 0.002*dt;
    clamp(speed.y,-1.8,1.8);
}

void Godofredo::AttackState(float dt)
{
    if (attackT.isRunning())
        return;
    StageState::AddObject(new Attack("notattack.png", 2, box.x+(box.w/2), box.y, power, 200, facing));
    attackT.Start();
}

void Godofredo::JumpState(float dt)
{
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE))
    {
        if(!jumping)
        {
            jumping = true;
            speed.y = -0.6;
            if(wallJumping == 1)
                speed.x = 0.4;
            if(wallJumping == 2)
                speed.x = -0.4;
            lastWallJumping = wallJumping;
            wallJumping = 0;
            jumpingPower = 1;
        }
    }
    else if(InputManager::GetInstance().KeyRelease(SDLK_SPACE))
    {
        jumpingPower = 0;
    }
    else
    {
        if(jumpingPower > 0 && jumpingPower < 11)
        {
            speed.y -= 0.03;
            jumpingPower++;
        }
    }
}

void Godofredo::InvisibleState(float dt)
{
    NotifyTileCollision(SPECIAL);
}

void Godofredo::UpdatePosition(float dt) {
	box.x += speed.x*dt;

    if(speed.x > 0)
        NotifyTileCollision(RIGHT);
    else
        NotifyTileCollision(LEFT);

    box.y += speed.y*dt;
    if(speed.y > 0)
        NotifyTileCollision(BOTTOM);
    else
        NotifyTileCollision(UPPER);
}

void Godofredo::UpdateBoundingBox() {
        box.x += (currentSprite->GetLastWidth()-currentSprite->GetWidth())/2;
        box.y += currentSprite->GetLastHeight()-currentSprite->GetHeight();
        box.w = currentSprite->GetWidth()-2;
        box.h = currentSprite->GetHeight()-2;
}

void Godofredo::Render() {
    currentSprite->Render(box.x - Camera::GetInstance().pos.x -1, box.y - Camera::GetInstance().pos.y -1);
	healthBar.Render(5, 5);
	stealthBar.Render(5, 10+stealthBar.GetHeight());
}

void Godofredo::Damage(int damage) {
    if(!invincibilityT.isRunning()) {
		hitpoints -= (damage-defense);
		healthBar.SetFrame(hitpoints+1);
		invincibilityT.Start();
	}
}

bool Godofredo::NotifyTileCollision(Face face) {
	TileMap* map = StageState::GetTileMap();
	unsigned limitX = ((box.x+box.w)/map->GetTileWidth() < map->GetWidth()) ? ((box.x+box.w)/map->GetTileWidth()) : (map->GetWidth());
	unsigned limitY = ((box.y+box.h)/map->GetTileHeight() < map->GetHeight()) ? ((box.y+box.h)/map->GetTileHeight()) : (map->GetHeight());
	if(face == LEFT) {
		for(unsigned x = box.x/map->GetTileWidth(); x <= limitX; x++) {
			for(unsigned y = box.y/map->GetTileHeight(); y <= limitY; y++) {
				if(map->At(x,y,0) > 5) {
					Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
					if(box.x < tile.x+tile.w && box.x+box.w > tile.x+tile.w) {
						box.x = tile.x+tile.w+1;
						speed.x = 0;
						if(map->At(x,y,0) > 11)
							Damage(1);
						if(jumping) {
							if(lastWallJumping != 1)
								jumping = false;
							wallJumping = 1;
						}
						return true;
					}
				}
			}
		}
	}
	if(face == RIGHT) {
		for(unsigned x = box.x/map->GetTileWidth(); x <= limitX; x++) {
			for(unsigned y = box.y/map->GetTileHeight(); y <= limitY; y++) {
				if(map->At(x,y,0) > 5) {
					Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
					if(box.x+box.w > tile.x && box.x < tile.x) {
						box.x = tile.x-box.w-1;
						speed.x = 0;
						if(map->At(x,y,0) > 11)
							Damage(1);
						if(jumping) {
							if(lastWallJumping != 2)
								jumping = false;
							wallJumping = 2;
						}
						return true;
					}
				}
			}
		}
	}
	if(face == UPPER) {
		for(unsigned x = box.x/map->GetTileWidth(); x <= limitX; x++) {
			for(unsigned y = box.y/map->GetTileHeight(); y <= limitY; y++) {
				if(map->At(x,y,0) > 5) {
					Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
					if(box.y < tile.y+tile.h && box.y+box.h > tile.y+tile.h) {
						box.y = tile.y+tile.h+1;
						if(map->At(x,y,0) > 11)
							Damage(1);
						return true;
					}
				}
			}
		}
	}
    if(face == BOTTOM) {
            for(unsigned x = box.x/map->GetTileWidth(); x <= limitX; x++) {
                for(unsigned y = box.y/map->GetTileHeight(); y <= limitY; y++) {
                    if(map->At(x,y,0) > 5) {
                        Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
                        if(box.y+box.h > tile.y && box.y < tile.y) {
                            box.y = tile.y-box.h-1;
                            speed.y = 0.6;
                            wallJumping = 0;
                            jumping = false;
                            if(map->At(x,y,0) > 11)
                                Damage(1);
                            return true;
                        }
                    }
                }
            }
    }
	if(face == SPECIAL) {
        for(unsigned x = box.x/map->GetTileWidth(); x <= limitX; x++) {
            for(unsigned y = box.y/map->GetTileHeight(); y <= limitY; y++) {
                if(map->At(x,y,1) == 0) {
                    Rect tile = Rect(x*map->GetTileWidth(), y*map->GetTileHeight(), map->GetTileWidth(), map->GetTileHeight());
                    if((((box.x+box.w >= tile.x) && (box.x <= tile.x+tile.w))
                       && ((box.y+box.h >= tile.y) && (box.y <= tile.y+tile.h)))) {
							hiddenT.Start();
							hidden = true;
							return true;
                    }
                }
            }
        }
	}
	return false;
}

void Godofredo::NotifyCollision(GameObject* other) {
	if(other->Is("Notattack"))
		Damage(other->power);
}

bool Godofredo::Is(std::string type) {
	return (type == "Godofredo");
}

bool Godofredo::IsHidden() {
	return hidden;
}

bool Godofredo::IsDead() {
	return (hitpoints < 1);
}

Godofredo* Godofredo::get() {
	return this;
}
