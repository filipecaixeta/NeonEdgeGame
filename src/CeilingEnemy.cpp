/**
   Copyright 2017 Neon Edge Game
   File Name: CeilingEnemy.cpp
   Header File Name: CeilingEnemy.h
   Class Name: CeilingEnemy
   Objective: The objective of this class is declare the logig of the Ceiling Enemy.

*/

#include "CeilingEnemy.h"
#include "StageState.h"
#include "GraphicsComponent.h"
#include "Gallahad.h"

/**
   Objective: Constructor of the class Celing Enemy.
   @param int x - Position of the enemy in X
   @param int y - Position of the enemy in Y.
   @return: Return a instance of CeilingEnemy.
*/
CeilingEnemy::CeilingEnemy(int x, int y):
    Character(x, y) {
    // Block tha initiate atributes of CeilingEnemy.
    name = "SpiderMan";
    graphicsComponent = new CeilingEnemyGraphicsComponent("DroneInimigoSprite");
    box.SetWH(graphicsComponent->GetSize());
    physicsComponent.SetKinetic(true);
    state = WAITING;
    physicsComponent.velocity.y = 0;
}

/**
   Objective: Put this kind of enemy to attack.
   param: None.
   @return Bool True.
*/
bool CeilingEnemy::Attacking() {
    return true;
}

/**
   Objective: Notify if tile is collided, modifing its state.
   @param int tile
   @param Face face.
   @return void.
*/
void CeilingEnemy::NotifyTileCollision(int tile, Face face) {
    // Changing state according with the collision of the face.
    if (tile >= 0) {
        if (face == UPPER && state == REARMING) {
            state = WAITING;
        }
        if (face == BOTTOM && state == ATTACKING) {
            state = REARMING;
        }
    }
}

/**
   Objective: Function responsable to ubdate CeilingEnemy GameObject.
   @param: float dt.
   @return: void
*/
void CeilingEnemy::UpdateAI(float dt) {
    if (StageState::GetPlayer()) {
        //Block to check visibility of the player.
        if (!stunned.IsRunning()) {
            bool visible = true;
            if (StageState::GetPlayer()->Is("Gallahad")) {
                Gallahad* g = (Gallahad*) StageState::GetPlayer();
                if (g->IsHiding()) {
                    visible = false;
                }
            }
            // If Player is visible enemy attack ang go after player.
            if (visible) {
                if (state == WAITING && StageState::GetPlayer()->box.GetCenter().x > this->box.x - 25 &&
                        StageState::GetPlayer()->box.GetCenter().x < this->box.x + box.w + 25) {
                    state = ATTACKING;
                } else if (state == ATTACKING) {
                    physicsComponent.velocity.y += 0.006 * dt;
                    clamp(physicsComponent.velocity.y, -0.4f, 0.4f);
                } else if (state == REARMING) {
                    physicsComponent.velocity.y -= 0.012 * dt;
                    clamp(physicsComponent.velocity.y, -0.2f, 0.2f);
                }
            }
        } else {
            physicsComponent.velocity.y = 0;
        }
    }
}

/**
   Objective: Function responsable to ubdate CeilingEnemy GameObject, but overloades with the world object.
   @param TileMap* world
   @param float dt.
   @return: void.
*/
void CeilingEnemy::Update(TileMap* world, float dt) {
    UpdateTimers(dt);
    UpdateAI(dt);
    physicsComponent.Update(this, world, dt);
    if (OutOfBounds(world)) {
        SetPosition(Vec2(startingX, startingY));
    }

    graphicsComponent->Update(this, dt);
}
