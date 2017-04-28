#include "Godofredo.h"
#include "InputManager.h"
#include "Camera.h"
#include "StageState.h"

Godofredo* Godofredo::player = nullptr;

Godofredo::Godofredo(int x, int y) {
	if(player) {
		printf("Multiple Player Instances\n");
		exit(EXIT_FAILURE);
	}else{
		player = this;
	}

	sp = Sprite("resources/img/LancelotIdleRight.png", 8, 120);
	box = Rect(x+1, y+1, sp.GetWidth()-2, sp.GetHeight()-2);

	hitpoints = 10;
	power = 1;
	defense = 0;
	speed = Vec2(0, 0.6);

	facing = RIGHT;

	healthBar = Sprite("resources/img/healthBar.png", 11);
	healthBar.SetFrame(11);
	stealthBar = Sprite("resources/img/stealthBar.png", 11);
	stealthBar.SetFrame(1);

	invincibilityT = Timer(500);
	attackT = Timer(500);
	hiddenT = Timer(1000);
}

Godofredo::~Godofredo() {
	player = nullptr;
}

void Godofredo::Update(float dt) {
	UpdateTimers(dt);
	UpdateCommands(dt);
	UpdatePosition(dt);
	if(speed.y < 1.8)
		speed.y += 0.002*dt;
	else
		speed.y = 1.8;
	sp.Update(dt);
}

void Godofredo::UpdateTimers(float dt) {
	if(invincibilityT.GetTime() > -1) {
		if(invincibilityT.GetTime() < invincibilityT.GetLimit())
			invincibilityT.Update(dt);
		else
			invincibilityT.Reset();
	}
	if(attackT.GetTime() > -1) {
		if(attackT.GetTime() < attackT.GetLimit()) {
			attackT.Update(dt);
		}else{
			attacking = false;
			attackT.Reset();
		}
	}
	if(hiddenT.GetTime() > -1) {
		if(hiddenT.GetTime() < hiddenT.GetLimit()) {
			hiddenT.Update(dt);
			stealthBar.SetFrame(round((hiddenT.GetLimit()-hiddenT.GetTime())/100)+1);
		}else{
			hiddenT.Reset();
			stealthBar.SetFrame(1);
			hidden = false;
		}
	}
}

void Godofredo::UpdateCommands(float dt) {
	if(InputManager::GetInstance().IsKeyDown(SDLK_a)) {
		if(speed.x > -0.4)
			speed.x -= 0.002*dt;
		else
			speed.x = -0.4;
		facing = LEFT;
		if(hidden){
			if(sp.GetFile() != "resources/img/LancelotRunningLeftInv.png") {
				sp.SetFile("resources/img/LancelotRunningLeftInv.png", 8, 120);
				UpdateBoundingBox();
			}
		}else{
			if(sp.GetFile() != "resources/img/LancelotRunningLeft.png") {
				sp.SetFile("resources/img/LancelotRunningLeft.png", 8, 120);
				UpdateBoundingBox();
			}
		}
	}else if(InputManager::GetInstance().IsKeyDown(SDLK_d)) {
		if(speed.x < 0.4)
			speed.x += 0.002*dt;
		else
			speed.x = 0.4;
		facing = RIGHT;
		if(hidden) {
			if(sp.GetFile() != "resources/img/LancelotRunningRightInv.png") {
				sp.SetFile("resources/img/LancelotRunningRightInv.png", 8, 120);
				UpdateBoundingBox();
			}
		}else{
			if(sp.GetFile() != "resources/img/LancelotRunningRight.png") {
				sp.SetFile("resources/img/LancelotRunningRight.png", 8, 120);
				UpdateBoundingBox();
			}
		}
	}else{
		speed.x = 0;
		if(facing == LEFT) {
			if(hidden) {
				if(sp.GetFile() != "resources/img/LancelotHiddenLeft.png") {
					sp.SetFile("resources/img/LancelotHiddenLeft.png", 8, 120);
					UpdateBoundingBox();
				}
			}else{
				if(sp.GetFile() != "resources/img/LancelotIdleLeft.png") {
					sp.SetFile("resources/img/LancelotIdleLeft.png", 8, 120);
					UpdateBoundingBox();
				}
			}
		}else if(facing == RIGHT){
			if(hidden) {
				if(sp.GetFile() != "resources/img/LancelotHiddenRight.png") {
					sp.SetFile("resources/img/LancelotHiddenRight.png", 8, 120);
					UpdateBoundingBox();
				}
			}else{
				if(sp.GetFile() != "resources/img/LancelotIdleRight.png") {
					sp.SetFile("resources/img/LancelotIdleRight.png", 8, 120);
					UpdateBoundingBox();
				}
			}
		}
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_e)) {
		if(attackT.GetTime() < 0) {
			StageState::AddObject(new Attack("resources/img/notattack.png", 2, box.x+(box.w/2), box.y, power, 200, facing));
			attackT.Start();
		}
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_SPACE)) {
		if(InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
			if(!jumping) {
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
		}else if(InputManager::GetInstance().KeyRelease(SDLK_SPACE)) {
			jumpingPower = 0;
		}else{
			if(jumpingPower > 0 && jumpingPower < 11) {
				speed.y -= 0.03;
				jumpingPower++;
			}
		}
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_s)) {
		NotifyTileCollision(SPECIAL);
	}
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
		box.x += (sp.GetLastWidth()-sp.GetWidth())/2;
		box.y += sp.GetLastHeight()-sp.GetHeight();
		box.w = sp.GetWidth()-2;
		box.h = sp.GetHeight()-2;
}

void Godofredo::Render() {
	sp.Render(box.x - Camera::GetInstance().pos.x -1, box.y - Camera::GetInstance().pos.y -1);
	healthBar.Render(5, 5);
	stealthBar.Render(5, 10+stealthBar.GetHeight());
}

void Godofredo::Damage(int damage) {
	if(invincibilityT.GetTime() < 0) {
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
