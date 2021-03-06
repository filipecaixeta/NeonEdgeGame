/**
 * Copyright 2017 Neon Edge Game
 * File Name: CeilingEnemy.cpp
 * Header File Name: CeilingEnemy.h
 * Class Name: CeilingEnemy
 * Objective: it declares the logig of the Ceiling Enemy.
 */

#include "CeilingEnemy.h"
#include "StageState.h"
#include "GraphicsComponent.h"
#include "Gallahad.h"
#include "Logger.h"
#include <assert.h>

/**
 * Objective: it constructs Celing Enemy object.
 *
 * @param int x_axis_position - position of the enemy in x axis.
 * @param int y_axis_position - position of the enemy in y axis.
 * @return instance of CeilingEnemy.
 */
CeilingEnemy::CeilingEnemy(int x_axis_position, int y_axis_position): Character(x_axis_position,
                                                                                y_axis_position) {
    // Block tha initiate atributes of CeilingEnemy.
    if ((x_axis_position >= INT_MIN_SIZE) && (x_axis_position <= INT_MAX_SIZE) &&
        (y_axis_position >= INT_MIN_SIZE) && (y_axis_position <= INT_MAX_SIZE)) {
        name = "SpiderMan";
        graphicsComponent = new CeilingEnemyGraphicsComponent("DroneInimigoSprite");
        box.SetWH(graphicsComponent->GetSize());
        physicsComponent.SetKinetic(true);
        state = WAITING;
        physicsComponent.velocity.y = INITIAL_SPIDERMAN_VELOCITY;

        assert(graphicsComponent != nullptr);

        Log::instance.info("CeilingEnemy builder started!");
    } else {
        Log::instance.error("Tested value is higher or lower than allowed!");
    }
}

/**
 * Objective: it puts this kind of enemy to attack.
 *
 * param none.
 * @return Bool True.
 */
bool CeilingEnemy::Attacking() {
    return true;
}

/**
 * Objective: it notifies if tile is collided, modifing its state.
 *
 * @param int tile.
 * @param Face face.
 * @return none.
 */
void CeilingEnemy::NotifyTileCollision(int tile, Face face) {
    if (tile >= INT_MIN_SIZE && tile <= INT_MAX_SIZE) {
        if (tile >= 0) {
            // Changing state according with the collision of the face.
            if (face == BOTTOM && state == ATTACKING) {
                state = REARMING;
            } else if (face == UPPER && state == REARMING) {
                state = WAITING;
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }
    } else {
        Log::instance.error("Tested value is higher or lower than allowed!");
    }
}

/**
 * Objective: Attack the player if the enemy can see him.
 *
 * @param float deltaTime.
 * @return none.
 */
void CeilingEnemy::AttackVisiblePlayer(float deltaTime){
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);

    if (state == WAITING &&
            ((StageState::GetPlayer()->box.GetCenter().x) >
            (this->box.x - PIXELS_X_FROM_SPIDERMAN)) &&
            ((StageState::GetPlayer()->box.GetCenter().x) <
            (this->box.x + box.w + PIXELS_X_FROM_SPIDERMAN))) {
        state = ATTACKING;
    } else if (state == ATTACKING) {
        physicsComponent.velocity.y += ATTACKING_DELAY_TIME * deltaTime;
        clamp(physicsComponent.velocity.y, -ATTACKING_CLAMP_L_U, ATTACKING_CLAMP_L_U);
    } else if (state == REARMING) {
        physicsComponent.velocity.y -= REARMING_DELAY_TIME * deltaTime;
        clamp(physicsComponent.velocity.y, -REARMING_CLAMP_L_U, REARMING_CLAMP_L_U);
    } else {
        Log::instance.warning("No valid state of CeilingEnemy");
    }
}

/**
 * Objective: it updates CeilingEnemy GameObject.
 *
 * @param float deltaTime.
 * @return none.
 */
void CeilingEnemy::UpdateAI(float deltaTime) {
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);

    if (StageState::GetPlayer()) {
        //Block to check visibility of the player.
        if (!stunned.IsRunning()) {
            bool visible = true;
            if (StageState::GetPlayer()->Is("Gallahad")) {
                Gallahad *gallahad = (Gallahad *) StageState::GetPlayer();
                if (gallahad->IsHiding()) {
                    visible = false;
                } else {
                    // It does nothing.
                }
            } else {
                // It does nothing.
            }
            // If Player is visible enemy attack ang go after player.
            if (visible) {
                AttackVisiblePlayer(deltaTime);
            } else {
                // It does nothing.
            }
        } else {
            physicsComponent.velocity.y = 0;
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates CeilingEnemy GameObject, but overloades with the world object.
 *
 * @param TileMap* world
 * @param float deltaTime.
 * @return: void.
 */
void CeilingEnemy::Update(TileMap *world, float deltaTime) {
    assert(world != nullptr);
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);

    UpdateTimers(deltaTime);
    UpdateAI(deltaTime);
    physicsComponent.Update(this, world, deltaTime);
    if (OutOfBounds(world)) {
        SetPosition(Vec2(startingX, startingY));
        Log::instance.warning("Outdated limits!");
    } else {
        // It does nothing.
    }

    graphicsComponent->Update(this, deltaTime);
}
