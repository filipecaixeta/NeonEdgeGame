#include "TurretBoss.h"
#include "StageState.h"
#include "Cutscene.h"

#include <cmath>
#include <math.h>
#include <cstdlib>
#include <sys/time.h>

TurretBoss::TurretBoss(int x, int y):
    Character(x,y),
    idle(1000),
    aim(3000),
    shoot(300) {
    name = "TurretBoss";
    box.x = x;
    box.y = y;
    box.w = 0;
    box.h = 0;
    pieces = std::vector<TurretPiece*>();
    turrets = std::vector<TurretPiece*>();
    facing = LEFT;
    Damage(5);
    triggered = false;
    state = tIDLE;
    physicsComponent.SetKinetic(true);
    physicsComponent.velocity.y = 0;
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

void TurretBoss::AddPiece(TurretPiece* piece) {
    pieces.emplace_back(piece);
}

void TurretBoss::AddTurret(TurretPiece* turret) {
    turrets.emplace_back(turret);
}

void TurretBoss::NotifyObjectCollision(GameObject* other) {
}

void TurretBoss::UpdateAI(float dt) {
    radius = Rect(box.x-500, box.y-500, box.w+1000, box.h+1000);
    if (StageState::GetPlayer()) {
        Rect player = StageState::GetPlayer()->box;
        if (player.OverlapsWith(radius)) {
            triggered = true;
        }

        if (triggered) {
            if (state == tIDLE) {
                if (!idle.IsRunning()) {
                    aim.Start();
                    state = tAIMING;
                    turret1 = rand()%6;
                    turret2 = rand()%6;
                    while (turret2 == turret1) {
                        turret2 = rand()%6;
                    }
                }
            }
            if (state == tAIMING) {
                for (unsigned i = 0; i < turrets.size(); i++) {
                    if (i == turret1 || i == turret2) {
                        Rect turret = turrets[i]->box;
                        float dx = std::abs(turret.GetCenter().x - player.GetCenter().x);
                        float dy = turret.GetCenter().y - player.GetCenter().y;
                        float angle = atan(dy/dx) * 180 / M_PI;
                        if (angle < 0) {
                            if (turrets[i]->Rotation()-(0.03*dt) < angle) {
                                turrets[i]->Rotate(angle);
                            }
                            else {
                                turrets[i]->Rotate(turrets[i]->Rotation()-(0.03*dt));
                            }
                        } else {
                            if (turrets[i]->Rotation()+(0.03*dt) > angle) {
                                turrets[i]->Rotate(angle);
                            } else {
                                turrets[i]->Rotate(turrets[i]->Rotation()+(0.03*dt));
                            }
                        }
                    } else {
                        if (turrets[i]->Rotation() < 0) {
                            if (turrets[i]->Rotation()+(0.01*dt) > 0) {
                                turrets[i]->Rotate(0);
                            } else {
                                turrets[i]->Rotate(turrets[i]->Rotation()+(0.01*dt));
                            }
                        } else {
                            if (turrets[i]->Rotation()-(0.01*dt) < 0) {
                                turrets[i]->Rotate(0);
                            } else {
                                turrets[i]->Rotate(turrets[i]->Rotation()-(0.01*dt));
                            }
                        }
                    }
                }
                if (!aim.IsRunning()) {
                    shoot.Start();
                    state = tSHOOTING;
                }
            }
            if (state == tSHOOTING) {
                turrets[turret1]->Shoot();
                turrets[turret2]->Shoot();
                if (!shoot.IsRunning()) {
                    idle.Start();
                    state = tIDLE;
                }
            }
        }
    }
}

void TurretBoss::UpdateTimers(float dt) {
    Character::UpdateTimers(dt);
    idle.Update(dt);
    aim.Update(dt);
    shoot.Update(dt);
}

void TurretBoss::Update(TileMap* world, float dt) {
    UpdateTimers(dt);
    UpdateAI(dt);
    physicsComponent.Update(this, world, dt);
    if (OutOfBounds(world)) {
        SetPosition(Vec2(startingX, startingY));
    }
}

void TurretBoss::Render() {
}
