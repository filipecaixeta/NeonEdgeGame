/**
  Copyright (c) 2017 Neon Edge Game.
  File Name: Arthur.cpp
  Header File Name: Arthur.h
  Class Name: Arthur
  Objective: Defines the behavior and actions of Arthur, the boss of the second stage.

*/

#include "Arthur.h"
#include "Cutscene.h"
#include "StageState.h"

/**
    Objective: Constructor of the class Arthur.
    @param int x - Initial position of the Arthur in X
    @param int y - Initial position of the Arthur in Y.
    @return instance of Arthur.

*/
Arthur::Arthur(int x, int y): Character(x, y), idle(3000), dash(1000), slash(1000), punch(1000) {
    graphicsComponent = new ArthurGraphicsComponent("Arthur"); // Instances the graphics, adding the sprites.
    name = "Arthur";
    box.SetWH(graphicsComponent->GetSize());
    state = IDLE; // Sets the initial state as 'idle'.
    triggered = false;
    Damage(9);
}

/**
    Objective: Destructor of the class Arthur.
    @param none.
    @return none.

*/
Arthur::~Arthur() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(7, false));
}

/**
    Objective: Deal with the collisions with Arthur.
    @param GameObject other - object of type GameObject that receives the actions when collide with Arthur.
    @return none.

*/
void Arthur::NotifyObjectCollision(GameObject* other) {
    Character::NotifyObjectCollision(other);
}

/**
    Objective: Updates the AI of the Arthur, from a radius.
    @param float dt - The amount of time the Arthur updates its graphics.
    @return none.

*/
void Arthur::UpdateAI(float dt) {
    // Defines the radius of vision of the Arthur as a rectangle.
    radius = Rect(box.x - 800, box.y - 800, box.w + 1000, box.h + 1000);
    if (StageState::GetPlayer()) {
        Rect player = StageState::GetPlayer()->box;
        if (player.OverlapsWith(radius)) {
            triggered = true;
        }
        if (triggered) {
            if (state == IDLE) {
                physicsComponent.velocity.x = 0; // Sets the velocity in zero when the state is 'idle'.
                if (player.x < box.x) {
                    facing = LEFT; // When the state is idle and velocity is zero, turns sideways.
                    // If 'idle' state is not running, this block changes the state of Arthur according to the position of the Player.
                    if (!idle.IsRunning()) {
                        if (box.x - player.x > 400) {
                            dash.Start();
                            state = DASHINGLEFT;
                        } else if (box.x - player.x > 100) {
                            punch.Start();
                            state = PUNCHING;
                        } else {
                            slash.Start();
                            state = SLASHING;
                        }
                    }
                }
                if (player.x > box.x) {
                    facing = RIGHT;
                    // Repeats the behaviors of the last block commented, but when 'facing' is RIGHT.
                    if (!idle.IsRunning()) {
                        if (player.x - box.x > 400) {
                            dash.Start();
                            state = DASHINGRIGHT;
                        } else if (player.x - box.x > 100) {
                            punch.Start();
                            state = PUNCHING;
                        } else {
                            slash.Start();
                            state = SLASHING;
                        }
                    }
                }
            } else if (state == DASHINGLEFT) {
                facing = LEFT;
                if (!dash.IsRunning()) {
                    idle.Start(); // Starts the 'idle' state when is not dashing to left.
                    state = IDLE;
                }
                if (dash.IsRunning()) {
                    physicsComponent.velocity.x -= 0.006 * dt; // Defines the velocity when is dashing to left.
                    Attack();
                }
                clamp(physicsComponent.velocity.x, -0.8f, 0.8f);
            } else if (state == DASHINGRIGHT) {
                facing = RIGHT;
                if (!dash.IsRunning()) {
                    idle.Start(); // Starts the 'idle' state when is not dashing to right.
                    state = IDLE;
                }
                if (dash.IsRunning()) {
                    physicsComponent.velocity.x += 0.006 * dt; // Defines the velocity when is dashing to right.
                    Attack();
                }
                clamp(physicsComponent.velocity.x, -0.8f, 0.8f);
            } else if (state == SLASHING) {
                if (player.x < box.x) {
                    facing = LEFT;
                    if (!slash.IsRunning()) {
                        idle.Start(); // Starts the 'idle' state when is not slashing to left.
                        state = IDLE;
                    }
                    if (slash.IsRunning()) {
                        Attack(); // The slash is a attack. Starts attack when slash is running.
                    }
                }
                if (player.x > box.x) {
                    facing = RIGHT;
                    if (!slash.IsRunning()) {
                        idle.Start(); // Starts the 'idle' state when is not slashing to right.
                        state = IDLE;
                    }
                    if (slash.IsRunning()) {
                        Attack(); // The slash is a attack. Starts attack when slash is running.
                    }
                }
            } else if (state == PUNCHING) {
                if (player.x < box.x) {
                    facing = LEFT;
                    if (!punch.IsRunning()) {
                        idle.Start(); // Starts the 'idle' state when is not punching to left.
                        state = IDLE;
                    }
                    if (punch.IsRunning()) {
                    }
                }
                if (player.x > box.x) {
                    facing = RIGHT;
                    if (!punch.IsRunning()) {
                        idle.Start(); // Starts the 'idle' state when is not punching to right.
                        state = IDLE;
                    }
                    if (punch.IsRunning()) {
                    }
                }
            }
        }
    }
}

/**
    Objective: Starts the Arthur attack.
    @param none.
    @return none.

*/
void Arthur::Attack() {
    attacking.Start();
}

/**
    Objective: Updates the timers of 'idle', 'slash', 'dash' and 'punch' states.
    @param float dt - Amount of time the Arthur remains in some state.
    @return none.

*/
void Arthur::UpdateTimers(float dt) {
    attacking.SetLimit(60);
    idle.Update(dt);
    slash.Update(dt);
    dash.Update(dt);
    punch.Update(dt);
    if (attacking.GetElapsed() == 1) {
        attacking.Reset();
        attackCD.Start();
    }
    attackCD.Update(dt);
}

/**
    Objective: Function responsible to update Arthur GameObject, but overloaded with the world object.
    @param TileMap* world.
    @param float dt - Time the Arthur updates its timers, in nanoseconds.
    @return none.

*/
void Arthur::Update(TileMap* world, float dt) {
    UpdateTimers(dt);
    UpdateAI(dt);
    physicsComponent.Update(this, world, dt);
    // If the Arthur is outside the boundaries of the map, its position is resetted.
    if (OutOfBounds(world)) {
        SetPosition(Vec2(startingX, startingY));
    }
    graphicsComponent->Update(this, dt);
}

/**
    Objective: Returns the actual state of Arthur.
    @param none.
    @return state - Enum that represents a status: 0-IDLE, 1-SLASHING, 2-DASHINGLEFT, 3-DASHINGRIGHT, 4-PUNCHING

*/
ArthurState Arthur::GetState() {
    return state;
}
