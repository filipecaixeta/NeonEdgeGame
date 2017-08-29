// Copyright 2017 Neon Edge Game

#include "Arthur.h"
#include "Cutscene.h"
#include "StageState.h"

Arthur::Arthur(int x, int y):
    Character(x, y),
    idle(3000),
    dash(1000),
    slash(1000),
    punch(1000) {
    graphicsComponent = new ArthurGraphicsComponent("Arthur");
    name = "Arthur";
    box.SetWH(graphicsComponent->GetSize());
    state = IDLE;
    triggered = false;
    Damage(9);
}

Arthur::~Arthur() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(7, false));
}

void Arthur::NotifyObjectCollision(GameObject* other) {
    Character::NotifyObjectCollision(other);
}

void Arthur::UpdateAI(float dt) {
    radius = Rect(box.x-800, box.y-800, box.w+1000, box.h+1000);
    if (StageState::GetPlayer()) {
        Rect player = StageState::GetPlayer()->box;
        if (player.OverlapsWith(radius)) {
            triggered = true;
        }
        if (triggered) {
            if (state == IDLE) {
                physicsComponent.velocity.x = 0;
                if (player.x < box.x) {
                    facing = LEFT;
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
                    idle.Start();
                    state = IDLE;
                }
                if (dash.IsRunning()) {
                    physicsComponent.velocity.x -= 0.006*dt;
                    Attack();
                }
                clamp(physicsComponent.velocity.x, -0.8f, 0.8f);
            } else if (state == DASHINGRIGHT) {
                facing = RIGHT;
                if (!dash.IsRunning()) {
                    idle.Start();
                    state = IDLE;
                }
                if (dash.IsRunning()) {
                    physicsComponent.velocity.x += 0.006*dt;
                    Attack();
                }
                clamp(physicsComponent.velocity.x, -0.8f, 0.8f);
            } else if (state == SLASHING) {
                if (player.x < box.x) {
                    facing = LEFT;
                    if (!slash.IsRunning()) {
                        idle.Start();
                        state = IDLE;
                    }
                    if (slash.IsRunning()) {
                        Attack();
                    }
                }
                if (player.x > box.x) {
                    facing = RIGHT;
                    if (!slash.IsRunning()) {
                        idle.Start();
                        state = IDLE;
                    }
                    if (slash.IsRunning()) {
                        Attack();
                    }
                }
            } else if (state == PUNCHING) {
                if (player.x < box.x) {
                    facing = LEFT;
                    if (!punch.IsRunning()) {
                        idle.Start();
                        state = IDLE;
                    }
                    if (punch.IsRunning()) {
                        // Summon tower
                    }
                }
                if (player.x > box.x) {
                    facing = RIGHT;
                    if (!punch.IsRunning()) {
                        idle.Start();
                        state = IDLE;
                    }
                    if (punch.IsRunning()) {
                        // Summon tower
                    }
                }
            }
        }
    }
}

void Arthur::Attack() {
    attacking.Start();
}

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

void Arthur::Update(TileMap* world, float dt) {
    UpdateTimers(dt);
    UpdateAI(dt);
    physicsComponent.Update(this, world, dt);
    if (OutOfBounds(world)) {
        SetPosition(Vec2(startingX, startingY));
    }
    graphicsComponent->Update(this, dt);
}

ArthurState Arthur::GetState() {
    return state;
}
