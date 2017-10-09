/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: TurretBoss.cpp
 * Header File Name: TurretBoss.h
 * Class Name: TurretBoss
 * Objective: it defines the characteristics and behaviors of the TurretBoss.
 */

#include <cmath>
#include <math.h>
#include <cstdlib>
#include <sys/time.h>

#include "TurretBoss.h"
#include "StageState.h"
#include "Cutscene.h"

/**
 * Objective: it constructs Turret Boss object.
 *
 * @param int x - initial position of the TurretBoss in x axis
 * @param int y - initial position of the TurretBoss in y axis.
 * @return instance of TurretBoss.
 */
TurretBoss::TurretBoss(int x, int y): Character(x, y), idle(1000), aim(3000), shoot(300) {
    name = "TurretBoss";
    box.x = x;
    box.y = y;
    box.w = 0;
    box.h = 0; // Sets the attributes x, y, width and height of the box of the TurretBoss.
    pieces = std::vector<TurretPiece*>();
    turrets = std::vector<TurretPiece*>();
    facing = LEFT; // Sets left to 'facing', initialing the TurretBoss facing to left.
    Damage(5);
    triggered = false;
    state = tIDLE; // The initial state of the TurretBoss is 'idle'.
    physicsComponent.SetKinetic(true);
    physicsComponent.velocity.y = 0; // Velocity in y is zero why the TurretBoss is fixed.
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
}

TurretBoss::~TurretBoss() {
    for (unsigned i = 0; i < pieces.size(); i++) {
        pieces[i]->Kill();
    }

    for (unsigned i = 0; i < turrets.size(); i++) {
        turrets[i]->Kill();
    }
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(5, false));
}

/**
 * Objective: it adds turret piece on the TurretBoss.
 *
 * @param TurretPiece* piece - piece of the type TurretPiece for add in the final of TurretBoss.
 * @return none.
 */
void TurretBoss::AddPiece(TurretPiece *piece) {
    if (piece) {
        pieces.emplace_back(piece);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it adds a turret piece on the TurretBoss.
 *
 * @param TurretPiece *turret - piece of the type TurretPiece for add in the final of TurretBoss.
 * @return none.
 */
void TurretBoss::AddTurret(TurretPiece *turret) {
    if (turret) {
        turrets.emplace_back(turret); // Adds a turret piece on the final of vector turret.
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it notifies tile collision for inheritance.
 *
 * @param GameObject *other.
 * @return none.
 */
void TurretBoss::NotifyObjectCollision(GameObject *other) {
}

/**
 * Objective: Updates the AI of the TurretBoss, from a radius.
 *
 * @param float deltaTime - The amount of time the TurretBoss updates its graphics.
 * @return none.
 */
void TurretBoss::UpdateAI(float deltaTime) {
    if (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE) {
        // Defines the radius of vision of the TurretBoss as a rectangle.
        radius = Rect(box.x - 500, box.y - 500, box.w + 1000, box.h + 1000);
        if (StageState::GetPlayer()) {
            Rect player = StageState::GetPlayer()->box;
            if (player.OverlapsWith(radius)) {
                triggered = true;
            } else {
                // It does nothing.
            }

            if (triggered) {
                // If the state of the TurretBoss is 'idle' the aim is selected and the new state is 'aiming'.
                if (state == tIDLE && !idle.IsRunning()) {
                    aim.Start();
                    state = tAIMING;
                    // Sets differents random and differents numbers to turret1 and turret2.
                    turret1 = rand() % 6;
                    turret2 = rand() % 6;

                    while (turret2 == turret1) {
                        turret2 = rand() % 6;
                    }
                } else {
                    // It does nothing.
                }

                if (state == tAIMING) {
                    for (unsigned i = 0; i < turrets.size(); i++) {
                        if (i == turret1 || i == turret2) {
                            Rect turret = turrets[i]->box;
                            // From absolute values of x and y of the Turret and Player, sets the angle for attack.
                            float dx = std::abs(turret.GetCenter().x - player.GetCenter().x);
                            float dy = turret.GetCenter().y - player.GetCenter().y;
                            float angle = atan(dy / dx) * 180 / M_PI;
                            // If the turret angle is less than zero, other turret with valid angle is selected to attack.
                            if (angle < 0) {
                                if (turrets[i]->Rotation() - (0.03 * deltaTime) < angle) {
                                    turrets[i]->Rotate(angle);
                                }
                                else {
                                    turrets[i]->Rotate(turrets[i]->Rotation() - (0.03 * deltaTime));
                                }
                            } else {
                                if (turrets[i]->Rotation() + (0.03 * deltaTime) > angle) {
                                    turrets[i]->Rotate(angle);
                                } else {
                                    turrets[i]->Rotate(turrets[i]->Rotation() + (0.03 * deltaTime));
                                }
                            }
                        } else {
                            if (turrets[i]->Rotation() < 0) {
                                if (turrets[i]->Rotation() + (0.01 * deltaTime) > 0) {
                                    turrets[i]->Rotate(0);
                                } else {
                                    turrets[i]->Rotate(turrets[i]->Rotation() + (0.01 * deltaTime));
                                }
                            } else {
                                if (turrets[i]->Rotation() - (0.01 * deltaTime) < 0) {
                                    turrets[i]->Rotate(0);
                                } else {
                                    turrets[i]->Rotate(turrets[i]->Rotation() - (0.01 * deltaTime));
                                }
                            }
                        }
                    }
                    // If there is a target the turret starts the attack, altering your state to 'shooting'.
                    if (!aim.IsRunning()) {
                        shoot.Start();
                        state = tSHOOTING;
                    } else {
                        // It does nothing.
                    }
                }

                if (state == tSHOOTING) {
                    turrets[turret1]->Shoot();
                    turrets[turret2]->Shoot();
                    // If the turret isnt shooting, the actual state is 'idle'.
                    if (!shoot.IsRunning()) {
                        idle.Start();
                        state = tIDLE;
                    } else {
                        // It does nothing.
                    }
                } else {
                    // It does nothing.
                }
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
 * Objective: Function responsible to update the Timer of the behaviors of the TurretBoss.
 *
 * @param float deltaTime - The amount of time the TurretBoss stay in a state (idle, shooting, or aim).
 * @return none.
 */
void TurretBoss::UpdateTimers(float deltaTime) {
    if (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE) {
        Character::UpdateTimers(deltaTime);
        // Updates the idle, aim and shoot timer.
        idle.Update(deltaTime);
        aim.Update(deltaTime);
        shoot.Update(deltaTime);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: Function responsible to update TurretBoss GameObject, but overloaded with the world object.
 *
 * @param TileMap *world.
 * @param float deltaTime - Time the tower updates its timers, in nanoseconds.
 * @return none.
 */
void TurretBoss::Update(TileMap *world, float deltaTime) {
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
    } else {
        // It does nothing.
    }
}

/**
 * Objective: none.
 *
 * @param none.
 * @return none.
 */
void TurretBoss::Render() {
}
