/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: Turret.cpp
 * Header File Name: Turret.h
 * Class Name: Turret
 * Objective: defines the behavior and actions of a Turret.
 */

#include "Turret.h"
#include "AIMovingOnGroudGraphicsComponent.h"
#include "StageState.h"
#include "Gallahad.h"
#include "Projectile.h"

/**
 * Objective: it constructs Turret object.
 *
 * @param int x - initial position of the Turret in x axis.
 * @param int y - initial position of the Turret in y axis.
 * @return instance of Turret.
 */
Turret::Turret(int x, int y): Character(x, y), radius(), looking(1500), idle(1500) {
    name = "Turret";
    // It instances the graphics adding the sprite.
    graphicsComponent = new AIMovingOnGroudGraphicsComponent("Turret");

    box.SetWH(graphicsComponent->GetSize());
    attackCD.SetLimit(300); // Defines the time between each attack, in nanoseconds.
    idle.Start();
    hitpoints = 2;
}

Turret::~Turret() {
}

/**
 * Objective: It starts the Turret attack, generating attack object (projectile).
 *
 * @param none.
 * @return none.
 */
void Turret::Attack() {
    attackCD.Start();
    StageState::AddObject(new Projectile(this, Vec2(0.4, 0), 400, 1, false));
}

/**
 * Objective: it notifies tile collision for inheritance.
 *
 * @param int tile.
 * @param Face face - Short int indicating the facing of the GameObject.
 * @return none.
 */
void Turret::NotifyTileCollision(int tile, GameObject::Face face) {
}

/**
 * Objective: it updates the timers of 'looking' state and 'idle' state.
 *
 * @param float deltaTime - amount of time the tower remains in the 'looking' and 'idle' state.
 * @return none.
 */
void Turret::UpdateTimers(float deltaTime) {
    if (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE) {
        Character::UpdateTimers(deltaTime);
        if (!stunned.IsRunning() && looking.IsRunning()) {
            looking.Update(deltaTime);
            // If 'looking' state is not running, 'idle' state starts.
            if (!looking.IsRunning()) {
                idle.Start();
            } else {
                // It does nothing.
            }
        } else if (idle.IsRunning()) {
            idle.Update(deltaTime);
            // If 'idle' state is not running, 'looking' state starts.
            if (!idle.IsRunning()) {
                looking.Start();
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: Updates the AI of the Turret, from a radius.
 *
 * @param float deltaTime - The amount of time the Turret updates its graphics.
 * @return none.
 */
void Turret::UpdateAI(float deltaTime) {
    if (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE) {
        // Defines the radius of vision of the Turret as a rectangle.
        radius = Rect(box.x - 200, box.y - 200, box.w + 400, box.h + 400);
        if (StageState::GetPlayer() && !stunned.IsRunning()) {
            Rect player = StageState::GetPlayer()->box;
            bool visible = true;
            Gallahad* gallahad = (Gallahad*) StageState::GetPlayer();
            // If the player is the galahad and if it is invisible,
            // the visibility is false and the Turret does not attack.
            if (StageState::GetPlayer()->Is("Gallahad") && gallahad->IsHiding()) {
                visible = false;
            } else {
                // It does nothing.
            }

            // It does not allows the Turret follow the player instantly.
            if (player.OverlapsWith(radius) && visible) {
                if (player.x < box.x) {
                    // Sets the speed at x axis of the Turret less than
                    // the velocity at x axis of the player.
                    physicsComponent.velocity.x -= 0.003 * deltaTime;
                    if (box.x - physicsComponent.velocity.x * deltaTime < player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    } else {
                        // It does nothing.
                    }
                    facing = LEFT;
                } else {
                    physicsComponent.velocity.x += 0.003 * deltaTime;
                    if (box.x + physicsComponent.velocity.x * deltaTime > player.x) {
                        box.x = player.x;
                        physicsComponent.velocity.x = 0;
                    } else {
                        // It does nothing.
                    }
                    facing = RIGHT;
                }
                clamp(physicsComponent.velocity.x, -0.3f, 0.3f);

                if (!Cooling()) {
                    Attack();
                } else {
                    // It does nothing.
                }
            } else if (looking.IsRunning() && looking.GetElapsed() == 0) {
                if (facing == LEFT) {
                    // Sets the speed at x of the Turret when in 'looking' state and facing left.
                    physicsComponent.velocity.x = -0.2;
                } else {
                    // Sets the speed at x of the Turret when in 'looking' state and facing right.
                    physicsComponent.velocity.x = 0.2;
                }
            } else {
                if (idle.IsRunning() && idle.GetElapsed() == 0) {
                    physicsComponent.velocity.x = 0;
                    if (facing == LEFT) {
                        facing = RIGHT;
                    } else {
                        facing = LEFT;
                    }
                } else {
                    // It does nothing.
                }
            }
        } else {
            physicsComponent.velocity.x = 0;
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates Turret GameObject, but overloaded with the world object.
 *
 * @param TileMap* world.
 * @param float deltaTime - Time the tower updates its timers, in nanoseconds.
 * @return none.
 */
void Turret::Update(TileMap *world, float deltaTime) {
    if (world && (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE)) {
        UpdateTimers(deltaTime);
        UpdateAI(deltaTime);
        physicsComponent.Update(this, world, deltaTime);
        // If the tower is outside the boundaries of the map, its position is resetted.
        if (OutOfBounds(world)) {
            SetPosition(Vec2(startingX, startingY));
        } else {
            // It does nothing.
        }
        graphicsComponent->Update(this, deltaTime);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it returns the Turret type. A turret is a Enemy.
 *
 * @param string characterType - Type of the turret (enemy or player).
 * @return string characterType.
 */
bool Turret::Is(std::string characterType) {
    return (characterType == "Enemy");
}
