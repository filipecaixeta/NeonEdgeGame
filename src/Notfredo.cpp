/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: Notfredo.cpp
 * Header File Name: Notfredo.h
 * Class Name: Notfredo
 * Objective: Defines the behavior and actions of a piece of the Notfredo, the hitman of the second level.
 */

#include "assert.h"
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

struct Node {
  int x = 0;
  int y = 0;
  int z = 0;
  float graph_distance = 0.0;
  float physical_distance = 0.0;
  float combined_distance = 0.0;
  bool discovered = false;
  node* going_through = NULL;
  node* next = NULL;
};

/**
 * Objective: Constructor of the class Notfredo.
 *
 * @param int x - Initial position of the Notfredo in x.
 * @param int y - Initial position of the Notfredo in y.
 * @param Type type - Enum that represents the status FLYING and GROUND.
 * @return none.
 */
Notfredo::Notfredo(int x, int y, Type type): Character(x, y), radius(), looking(1500), idle(1500) { // The parameter of the 'looking' and 'idle functions is the time that...
    if (type == GROUND) {                                                                           // ...the Notfredo is in the state 'idle' and 'looking', in nanoseconds.
		assert(type==GROUND);
        graphicsComponent = new NotfredoGraphicsComponent("EnemyGallahad");
    }
    if (type == FLYING) {
		assert(type==FLYING);
        graphicsComponent = new NotfredoGraphicsComponent("EnemyGallahad");
    }
	  name = "Notfredo";
	  assert(name=="Notfredo");
	  box.SetWH(graphicsComponent->GetSize());
    attacking.SetLimit(360); // Defines the time between each attack, in nanoseconds.
	  idle.Start(); // Starts the Notfredo status as 'idle'.
    this->type = type;
    assert(type!=NULL);
    Damage(5);
    }

/**
 * Objective: Destructor of the class Notfredo.
 *
 * @param none.
 * @return none.
 */
Notfredo::~Notfredo() {
}

/**
 * Objective: Starts the attack timer.
 *
 * @param none.
 * @return none.
 */
void Notfredo::Attack() {
	attacking.Start();
}

/**
 * Objective: Notify if tile is collided, modifing its state.
 *
 * @param int tile.
 * @param Face face - Short int indicating the facing of the GameObject.
 * @return none.
 */
void Notfredo::NotifyTileCollision(int tile, GameObject::Face face) {
	if (tile >= SOLID_TILE && (face == LEFT || face == RIGHT)) {
		assert(tile >= SOLID_TILE && (face == LEFT || face == RIGHT));
		if (physicsComponent.velocity.y >= 0.6) {
			physicsComponent.velocity.y = -0.5;
		}
	}
}

/**
 * Objective: Updates the timers of 'looking' state and 'idle' state.
 *
 * @param float dt - The time that the Notfredo remains in the "looking" and "idle" state.
 * @return none.
 */
void Notfredo::UpdateTimers(float dt) {
	Character::UpdateTimers(dt);
	if (looking.IsRunning()) {
		looking.Update(dt);
    // If 'looking' state is not running, 'idle' state starts.
		if (!looking.IsRunning()) {
			idle.Start();
        }
	}
	else if (idle.IsRunning()) {
		idle.Update(dt);
    // If 'idle' state is not running, 'looking' state starts.
		if (!idle.IsRunning()) {
			looking.Start();
        }
	}
}

void Notfredo::UpdateAI(float dt) {
    if (type == GROUND) {
		assert(type == GROUND);
        // Defines the radius of vision of the Notfredo as a rectangle.
        radius = Rect(box.x - 200, box.y - 200, box.w + 400, box.h + 400);
        if (StageState::GetPlayer()) {
            bool visible = true;
            Rect player = StageState::GetPlayer()->box;
            // If the character is 'Gallahad' and he uses the ability to hide, the visibility is 'false', not to be seen.
            if (StageState::GetPlayer()->Is("Gallahad")) {
                Gallahad* gallahad = (Gallahad*) StageState::GetPlayer();
                if (gallahad->IsHiding()) {
                    visible = false;
                }
            }
            // Does not allow the Notfredo follow the player instantly.
            if (player.OverlapsWith(radius) && visible) {
                if (player.x < box.x) {
                    physicsComponent.velocity.x -= 0.003 * dt; // Sets the speed at x of the Notfredo less than the velocity at x of the player
                    if (box.x - physicsComponent.velocity.x * dt < player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    }
                    facing = LEFT;
                    assert(facing == LEFT);
                }
                else {
                    physicsComponent.velocity.x += 0.003 * dt;
                    if (box.x + physicsComponent.velocity.x * dt > player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    }
                    facing = RIGHT;
					assert(facing==RIGHT);
                }
                clamp(physicsComponent.velocity.x, -0.3f, 0.3f);
                // Sets the attack action of the Notfredo if he not be Attacking or Cooling.
                if (!Attacking() && !Cooling()) {
                    Attack();
                }
            }
            // Sets the velocity to left and right when the status is 'looking'.
            else if (looking.IsRunning() && looking.GetElapsed() == 0) {
                if (facing == LEFT) {
                    physicsComponent.velocity.x = -0.2;
                }
                else {
                    physicsComponent.velocity.x = 0.2;
                }
            }
            else {
                // Turns sideways when the state is 'idle'.
                if (idle.IsRunning() && idle.GetElapsed() == 0) {
                    physicsComponent.velocity.x = 0; // Stops the Notfredo to turn sideways.
                    if (facing == LEFT) {
                        facing = RIGHT;
						assert(facing==RIGHT);
                    }
                    else {
                        facing = LEFT;
						assert(facing==LEFT);
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

/**
 * Objective: Function responsible to update Notfredo GameObject, but overloaded with the world object.
 *
 * @param TileMap* world.
 * @param float dt - Time the Notfredo updates its timers, in nanoseconds.
 * @return none.
 */
void Notfredo::Update(TileMap* world, float dt) {
	UpdateTimers(dt);
	UpdateAI(dt);
	physicsComponent.Update(this, world, dt);
    if (OutOfBounds(world)) {
        SetPosition(Vec2(startingX, startingY));
    }
	graphicsComponent->Update(this, dt);
}

/**
 * Objective: Returns the Notfredo type. The Notfredo is a Enemy.
 *
 * @param string type - Type of Notfredo (enemy or player).
 * @return string type.
 */
bool Notfredo::Is(std::string type) {
	return (type == "Enemy");
}
