// Copyright 2017 Neon Edge Game

#include "Notfredo.h"
#include "Camera.h"
#include "StageState.h"
#include "Gallahad.h"
#include "Lancelot.h"
#include "Vec2.h"
#include "Rect.h"
#include "Player.h"
#include "Projectile.h"
#include "Room.h"

typedef struct Node node;

struct Node{
  int x, y, z;
  float graph_distance;
  float physical_distance;
  float combined_distance;
  bool discovered;
  node* going_through;
  node* next;
};

Notfredo::Notfredo(int x, int y, Type type):
	Character(x, y),
	radius(),
	looking(1500),
	idle(1500) {
    if (type == GROUND) {
        graphicsComponent = new NotfredoGraphicsComponent("EnemyGallahad");
    }
    if (type == FLYING) {
        graphicsComponent = new NotfredoGraphicsComponent("EnemyGallahad"/*"DroneInimigoSprite"*/);
    }
	name = "Notfredo";
	box.SetWH(graphicsComponent->GetSize());
    attacking.SetLimit(360);
	idle.Start();
    this->type = type;
    Damage(5);
    }

Notfredo::~Notfredo() {
}

void Notfredo::Attack() {
	// Starts attack timer
	attacking.Start();
}

void Notfredo::NotifyTileCollision(int tile, GameObject::Face face) {
	if (tile >= SOLID_TILE && (face == LEFT || face == RIGHT)) {
		if (physicsComponent.velocity.y >= 0.6) {
			physicsComponent.velocity.y = -0.5;
		}
	}
}

void Notfredo::UpdateTimers(float dt) {
	Character::UpdateTimers(dt);
	if (looking.IsRunning()) {
		looking.Update(dt);
		if (!looking.IsRunning()) {
			idle.Start();
        }
	}
	else if (idle.IsRunning()) {
		idle.Update(dt);
		if (!idle.IsRunning()) {
			looking.Start();
        }
	}
}

void Notfredo::UpdateAI(float dt) {
    if (type == GROUND) {
        radius = Rect(box.x-200, box.y-200, box.w+400, box.h+400);
        if (StageState::GetPlayer()) {
            Rect player = StageState::GetPlayer()->box;
            bool visible = true;
            if (StageState::GetPlayer()->Is("Gallahad")) {
                Gallahad* p = (Gallahad*) StageState::GetPlayer();
                if (p->Hiding()) {
                    visible = false;
                }
            }
            if (player.OverlapsWith(radius) && visible) {
                if (player.x < box.x) {
                    physicsComponent.velocity.x -= 0.003*dt;
                    if (box.x - physicsComponent.velocity.x*dt < player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    }
                    facing = LEFT;
                }
                else {
                    physicsComponent.velocity.x += 0.003*dt;
                    if (box.x + physicsComponent.velocity.x*dt > player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    }
                    facing = RIGHT;
                }
                clamp(physicsComponent.velocity.x, -0.3f, 0.3f);

                if (!Attacking() && !Cooling()) {
                    Attack();
                }
            }
            else if (looking.IsRunning() && looking.GetElapsed() == 0) {
                if (facing == LEFT) {
                    physicsComponent.velocity.x = -0.2;
                }
                else {
                    physicsComponent.velocity.x = 0.2;
                }
            }
            else {
                if (idle.IsRunning() && idle.GetElapsed() == 0) {
                    physicsComponent.velocity.x = 0;
                    if (facing == LEFT) {
                        facing = RIGHT;
                    }
                    else {
                        facing = LEFT;
                    }
                }
            }
        }
    }
    if (type == FLYING) {
        /*node* aux = PathFind();
        box.x = aux->x;
        box.y = aux->y;*/
    }
}

void Notfredo::Update(TileMap* world, float dt) {
	UpdateTimers(dt);
	UpdateAI(dt);
	physicsComponent.Update(this, world, dt);
    if (OutOfBounds(world)) {
        SetPosition(Vec2(startingX, startingY));
    }
	graphicsComponent->Update(this, dt);
}

bool Notfredo::Is(std::string type) {
	return (type == "Enemy");
}
