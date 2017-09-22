/**
  Copyright 2017 Neon Edge Game
  File Name: Turret.cpp
  Header File Name: Turret.h
  Class Name: Turret
  Objective: Defines the behavior and actions of a Turret.

*/

#include "Turret.h"
#include "AIMovingOnGroudGraphicsComponent.h"
#include "StageState.h"
#include "Gallahad.h"
#include "Projectile.h"

/**
    Objective: Constructor of the class Turret.
    @param int x - Size in x of the Turret.
    @param int y - Size in y of the Turret.
    @return instance of Turret.

*/
Turret::Turret(int x, int y): Character(x, y), radius(), looking(1500), idle(1500) {
    name = "Turret";
    graphicsComponent = new AIMovingOnGroudGraphicsComponent("Turret");
    box.SetWH(graphicsComponent->GetSize());
    attackCD.SetLimit(300);
    idle.Start();
    hitpoints = 2;
}

/**
    Objective: Destructor of the class Turret.
    @param none.
    @return none.

*/
Turret::~Turret() {
}

/**
    Objective: Starts the Turret attack, generating attack object (projectile).
    @param none.
    @return none.

*/
void Turret::Attack() {
    attackCD.Start();
    StageState::AddObject(new Projectile(this, Vec2(0.4, 0), 400, 1, false));
}

/**
    Objective: none.
    @param int tile.
    @param Face face - Short int indicating the facing of the GameObject.
    @return none.

*/
void Turret::NotifyTileCollision(int tile, GameObject::Face face) {
}

/**
    Objective: Updates the timers of 'looking' state and 'idle' state.
    @param float dt - Amount of time the tower remains in the 'looking' and 'idle' state.
    @return none.

*/
void Turret::UpdateTimers(float dt) {
    Character::UpdateTimers(dt);
    if (!stunned.IsRunning()) {
        if (looking.IsRunning()) {
            looking.Update(dt);
            if (!looking.IsRunning()) {
                idle.Start();
						}
        } else if (idle.IsRunning()) {
            idle.Update(dt);
            if (!idle.IsRunning()) {
                looking.Start();
						}
        }
    }
}

/**
    Objective: Updates the AI of the Turret, from a radius.
    @param float dt - The amount of time the Turret updates its graphics.
    @return none.

*/
void Turret::UpdateAI(float dt) {
    // Defines the radius of vision of the Turret as a rectangle.
    radius = Rect(box.x - 200, box.y - 200, box.w + 400, box.h + 400);
    if (StageState::GetPlayer()) {
        if (!stunned.IsRunning()) {
            Rect player = StageState::GetPlayer()->box;
						bool visible = true;
            //  If the player is the galahad and if it is invisible, the visibility is false and the Turret does not attack.
            if (StageState::GetPlayer()->Is("Gallahad")) {
                Gallahad* g = (Gallahad*) StageState::GetPlayer();
                if (g->Hiding()) {
                    visible = false;
                }
            }
            // Does not allow the Turret to track the player instantly.
            if (player.OverlapsWith(radius) && visible) {
                if (player.x < box.x ) {
                    physicsComponent.velocity.x -= 0.003 * dt; // Sets the speed at x of the Turret less than the velocity at x of the player
                    if (box.x - physicsComponent.velocity.x * dt < player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    }
                    facing = LEFT; //
                } else {
                    physicsComponent.velocity.x += 0.003 * dt;
                    if (box.x + physicsComponent.velocity.x * dt > player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    }
										facing = RIGHT;
                }
                clamp(physicsComponent.velocity.x, -0.3f, 0.3f);

                if (!Cooling()) {
                    Attack();
                }
            } else if (looking.IsRunning() && looking.GetElapsed() == 0) {
                if (facing == LEFT) {
                physicsComponent.velocity.x = -0.2; // Sets the speed at x of the Turret when in 'looking' state and facing left.
							  } else {
                    physicsComponent.velocity.x = 0.2; // Sets the speed at x of the Turret when in 'looking' state and facing right.
								}
            } else {
                if (idle.IsRunning() && idle.GetElapsed() == 0) {
								    physicsComponent.velocity.x = 0;
                    if (facing == LEFT) {
						            facing = RIGHT;
                    } else {
                        facing = LEFT;
                    }
                }
            }
        } else {
            physicsComponent.velocity.x = 0;
        }
    }
}

/**
    Objective: Function responsible to update Turret GameObject, but overloaded with the world object.
    @param TileMap* world.
    @param float dt - Time the tower updates its timers, in nanoseconds.
    @return none.

*/
void Turret::Update(TileMap* world, float dt) {
    UpdateTimers(dt);
    UpdateAI(dt);
    physicsComponent.Update(this, world, dt);
    // If the tower is outside the boundaries of the map, its position is resetted.
    if (OutOfBounds(world)) {
		    SetPosition(Vec2(startingX, startingY));
    }
    graphicsComponent->Update(this, dt);
}

/**
    Objective: Returns the Turret type. A turret is a Enemy.
    @param string type - Type of the turret (enemy or player).
    @return string type.
*/
bool Turret::Is(std::string type) {
    return (type == "Enemy");
}
