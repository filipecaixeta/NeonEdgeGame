// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_TURRET_H_
#define INCLUDE_TURRET_H_

#include "Character.h"

class Turret : public Character {
 public:
    Turret(int x, int y);

 private:
    ~Turret();
    void TurretMovingVelocity();
    void TurretChangingDirection();
    void TurretSeeingCharacter(bool *visible);
    void TurretChasingCharacterToAttack(Rect player, float deltaTime);
    void UpdateTurretLookingTime(float deltaTime);
    void UpdateTurretIdleTime(float deltaTime);
    void Attack();
    void NotifyTileCollision(int tile, Face face);
    void UpdateTimers(float deltaTime);
    void UpdateAI(float deltaTime);
    void Update(TileMap* world, float deltaTime);
    bool Is(std::string characterType);
    Rect visionRadius;
    Timer looking;
    Timer idle;
};

#endif  // INCLUDE_TURRET_H_
