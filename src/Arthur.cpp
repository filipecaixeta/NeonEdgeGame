/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: Arthur.cpp
 * Header File Name: Arthur.h
 * Class Name: Arthur
 * Objective: it defines the behavior and actions of Arthur, the boss of the second stage.
 */

#include "Arthur.h"
#include "Cutscene.h"
#include "StageState.h"

/**
 * Objective: it constructs Arthur object.
 *
 * @param int x - Initial position of the Arthur in X
 * @param int y - Initial position of the Arthur in Y.
 * @return instance of Arthur.
 */
Arthur::Arthur(int x, int y): Character(x, y), idle(3000), dash(1000), slash(1000), punch(1000) {
    // Instances the graphics, adding the sprites.
    graphicsComponent = new ArthurGraphicsComponent("Arthur");

    name = "Arthur";
    box.SetWH(graphicsComponent->GetSize());
    arthurState = IDLE; // Sets the initial state as 'idle'.
    triggered = false;
    Damage(9);
}

Arthur::~Arthur() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(7, false));
}

/**
 * Objective: it deals with the collisions with Arthur.
 *
 * @param GameObject *gameObject - GameObject object that receives the actions when
 *                                 collide with Arthur.
 * @return none.
 */
void Arthur::NotifyObjectCollision(GameObject *gameObject) {
    if (gameObject) {
        Character::NotifyObjectCollision(gameObject);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates the AI of the Arthur, from a radius.
 *
 * @param float deltaTime - The amount of time the Arthur updates its graphics.
 * @return none.
 */
void Arthur::UpdateAI(float deltaTime) {
    if (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE) {
        // Defines the radius of vision of the Arthur as a rectangle.
        radius = Rect(box.x - 800, box.y - 800, box.w + 1000, box.h + 1000);
        if (StageState::GetPlayer()) {
            Rect player = StageState::GetPlayer()->box;
            if (player.OverlapsWith(radius)) {
                triggered = true;
                if (arthurState == IDLE) {
                    // It sets the velocity in zero when the state is 'idle'.
                    physicsComponent.velocity.x = 0;
                    if (player.x < box.x) {
                        // When the state is idle and velocity is zero, turns sideways.
                        facing = LEFT;
                        // If 'idle' state is not running, this block changes the state of Arthur
                        // according to the position of the Player.
                        if (!idle.IsRunning()) {
                            if (box.x - player.x > 400) {
                                dash.Start();  // It starts the 'dash' to left if the distance
                                               // between the player and Arthur is greater than 400.
                                arthurState = DASHINGLEFT;
                            } else if (box.x - player.x > 100) {
                                punch.Start();  // It starts the 'punch' state if the distance
                                                // between the player and Arthur is greater than 100.
                                arthurState = PUNCHING;
                            } else {
                                slash.Start();  // It starts the 'slash' state if the distance
                                                // between the player and Arthur is less than 100.
                                arthurState = SLASHING;
                            }
                        } else {
                            // It does nothing.
                        }
                    } else if (player.x > box.x) {
                        facing = RIGHT;
                        // If 'idle' state is not running,this block changes the state of Arthur
                        // according to the position of the Player.
                        if (!idle.IsRunning()) {
                            if (player.x - box.x > 400) {
                                dash.Start();
                                arthurState = DASHINGRIGHT;
                            } else if (player.x - box.x > 100) {
                                punch.Start();
                                arthurState = PUNCHING;
                            } else {
                                slash.Start();
                                arthurState = SLASHING;
                            }
                        } else {
                            // It does nothing.
                        }
                    } else {
                        // It does nothing.
                    }
                } else if (arthurState == DASHINGLEFT) {
                    facing = LEFT;
                    if (!dash.IsRunning()) {
                        idle.Start();  // It starts the 'idle' state when is not dashing to left.
                        arthurState = IDLE;
                    } else if (dash.IsRunning()) {
                        // Defines the velocity when is dashing to left.
                        physicsComponent.velocity.x -= 0.006 * deltaTime;

                        Attack();
                    } else {
                        // It does nothing.
                    }
                    clamp(physicsComponent.velocity.x, -0.8f, 0.8f);
                } else if (arthurState == DASHINGRIGHT) {
                    facing = RIGHT;
                    if (!dash.IsRunning()) {
                        idle.Start();  // It starts the 'idle' state when is not dashing to right.
                        arthurState = IDLE;
                    } else if (dash.IsRunning()) {
                        // It defines the velocity when is dashing to right.
                        physicsComponent.velocity.x += 0.006 * deltaTime;

                        Attack();
                    } else {
                        // It does nothing.
                    }
                    clamp(physicsComponent.velocity.x, -0.8f, 0.8f);
                } else if (arthurState == SLASHING) {
                    if (player.x < box.x) {
                        facing = LEFT;
                        if (!slash.IsRunning()) {
                            // It starts the 'idle' state when is not slashing to left.
                            idle.Start();

                            arthurState = IDLE;
                        } else if (slash.IsRunning()) {
                            Attack(); // The slash is a attack. Starts attack when slash is running.
                        } else {
                            // It does nothing.
                        }
                    } else if (player.x > box.x) {
                        facing = RIGHT;
                        if (!slash.IsRunning()) {
                            // It starts the 'idle' state when is not slashing to right.
                            idle.Start();

                            arthurState = IDLE;
                        } else if (slash.IsRunning()) {
                            Attack(); // It starts attack when slash is running.
                        } else {
                            // It does nothing.
                        }
                    } else {
                        // It does nothing.
                    }
                } else if (arthurState == PUNCHING) {
                    if (player.x < box.x) {
                        facing = LEFT;
                        if (!punch.IsRunning()) {
                            idle.Start();  // Starts the 'idle' state when is not punching to left.
                            arthurState = IDLE;
                        } else {
                            // It does nothing.
                        }
                    } else if (player.x > box.x) {
                        facing = RIGHT;
                        if (!punch.IsRunning()) {
                            idle.Start();  // Starts the 'idle' state when is not punching to right.
                            arthurState = IDLE;
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
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it starts the Arthur attack.
 *
 * @param none.
 * @return none.
 */
void Arthur::Attack() {
    attacking.Start();
}

/**
 * Objective: it updates the timers of 'idle', 'slash', 'dash' and 'punch' states.
 *
 * @param float deltaTime - Amount of time the Arthur remains in some state.
 * @return none.
 */
void Arthur::UpdateTimers(float deltaTime) {
    if (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE) {
        attacking.SetLimit(60);
        idle.Update(deltaTime);
        slash.Update(deltaTime);
        dash.Update(deltaTime);
        punch.Update(deltaTime);
        if (attacking.GetElapsed() == 1) {
            attacking.Reset();
            attackCD.Start();
        } else {
            // It does nothing.
        }
        attackCD.Update(deltaTime);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates Arthur GameObject, but overloaded with the world object.
 *
 * @param TileMap *world.
 * @param float deltaTime - Time the Arthur updates its timers, in nanoseconds.
 * @return none.
 */
void Arthur::Update(TileMap *world, float deltaTime) {
    if (world && (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE)) {
        UpdateTimers(deltaTime);
        UpdateAI(deltaTime);
        physicsComponent.Update(this, world, deltaTime);
        // If the Arthur is outside the boundaries of the map, its position is resetted.
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
 * Objective: it returns the actual state of Arthur.
 *
 * @param none.
 * @return arthurState - Enum that represents a status:
 *                       0 - IDLE, 1 - SLASHING, 2 - DASHINGLEFT, 3 - DASHINGRIGHT, 4 - PUNCHING.
 */
ArthurState Arthur::GetState() {
    return arthurState;
}
