#include "Minifredo.h"
#include "InputManager.h"
#include "Camera.h"
#include "StageState.h"

Minifredo::Minifredo() {
    sp = Sprite("minifredo.png", 3);
	box = Rect(Godofredo::player->box.x+13, Godofredo::player->box.y+6,
			   sp.GetWidth(), sp.GetHeight());
	speed = Vec2(0.4, 0.4);
}

Minifredo::~Minifredo() {

}

void Minifredo::Update(float dt) {
	sp.SetFrame(1);
	if(mf) {
		if(InputManager::GetInstance().IsKeyDown(SDLK_a)) {
			box.x -= speed.x*dt;
			NotifyTileCollision(LEFT);
			sp.SetFrame(2);
		}
		if(InputManager::GetInstance().IsKeyDown(SDLK_d)) {
			box.x += speed.x*dt;
			NotifyTileCollision(RIGHT);
			sp.SetFrame(3);
		}
		if(InputManager::GetInstance().IsKeyDown(SDLK_w)) {
			box.y -= speed.y*dt;
			NotifyTileCollision(UPPER);
		}
		if(InputManager::GetInstance().IsKeyDown(SDLK_s)) {
			box.y += speed.y*dt;
			NotifyTileCollision(BOTTOM);
		}
	}else{
		if(!perched) {
			if(Godofredo::player) {
				if(Godofredo::player->box.GetCenter().x < box.x) {
					if(box.x-speed.x*dt <= Godofredo::player->box.GetCenter().x)
						box.x = Godofredo::player->box.GetCenter().x;
					else
						box.x -= speed.x*dt;
					NotifyTileCollision(LEFT);
					sp.SetFrame(2);
				}else{
					if(box.x+speed.x*dt >= Godofredo::player->box.GetCenter().x)
						box.x = Godofredo::player->box.GetCenter().x;
					else
						box.x += speed.x*dt;
					NotifyTileCollision(RIGHT);
					sp.SetFrame(3);
				}
				if(Godofredo::player->box.GetCenter().y < box.y) {
					if(box.y-speed.y*dt <= Godofredo::player->box.GetCenter().y)
						box.y = Godofredo::player->box.GetCenter().y;
					else
						box.y -= speed.y*dt;
					NotifyTileCollision(UPPER);
				}else{
					if(box.y+speed.y*dt >= Godofredo::player->box.GetCenter().y)
						box.y = Godofredo::player->box.GetCenter().y;
					else
						box.y += speed.y*dt;
					NotifyTileCollision(BOTTOM);
				}
			}
			if(Godofredo::player->box.IsInside(box.GetV1()) || Godofredo::player->box.IsInside(box.GetV2()) ||
			   Godofredo::player->box.IsInside(box.GetV3()) || Godofredo::player->box.IsInside(box.GetV4())) {
				perched = true;
			}
		}else{
			if(Godofredo::player) {
				if(Godofredo::player->IsHidden()){
					box.x = Godofredo::player->box.x+12;
					box.y = Godofredo::player->box.y+17;
				}else{
					if(Godofredo::player->facing == RIGHT) {
						box.x = Godofredo::player->box.x+12;
						box.y = Godofredo::player->box.y+5;
						sp.SetFrame(1);
					}else if(Godofredo::player->facing == LEFT) {
						box.x = Godofredo::player->box.x+18;
						box.y = Godofredo::player->box.y+5;
						sp.SetFrame(2);
					}else{
						box.x = Godofredo::player->box.x+20;
						box.y = Godofredo::player->box.y+5;
						sp.SetFrame(3);
					}
				}
			}
		}
	}
}

void Minifredo::Render() {
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}

bool Minifredo::NotifyTileCollision(Face face) {
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
					}
				}
			}
		}
	}
	return false;
}

void Minifredo::NotifyCollision(GameObject* other) {
	if(other->Is("Notfredo") && !perched) {
		dead = true;
		//Godofredo::player->droneRespawn.Start();
		//Godofredo::player->mf = false;
		Camera::GetInstance().Follow(Godofredo::player);
	}
}

bool Minifredo::Is(std::string type) {
	return (type == "Minifredo");
}

bool Minifredo::IsDead() {
	return (Godofredo::player == nullptr || dead);
}

Minifredo* Minifredo::get() {
	return this;
}

