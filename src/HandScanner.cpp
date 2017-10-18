/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: HandScanner.cpp
 * Header File Name: HandScanner.h
 * Class Name: HandScanner
 * Objective: it manages door action.
 */

#include "HandScanner.h"
#include "Camera.h"
#include "StageState.h"
#include "Player.h"

#include <assert.h>

/**
 * Objective: it constructs Hand scanner object.
 *
 * @param int x - initial position of the Arthur in X
 * @param int y - initial position of the Arthur in Y.
 * @param Interactive *door - interactive door object.
 * @return instance of Hand scanner.
 */
HandScanner::HandScanner(int x, int y, Interactive *door): Interactive(x, y, "HandScanner") {
    assert(door != NULL);
    name = "HandScanner";
    this->door = door;

    assert(door != NULL);
}

HandScanner::~HandScanner() {
}

/**
 * Objective: it active door action.
 *
 * @param none.
 * @return none.
 */
void HandScanner::Trigger() {
    if (Active()) {
        door->On();
    } else {
        door->Off();
    }
}

/**
 * Objective: it verifies collison of drone in the door.
 *
 * @param GameObject* gameObject.
 * @return none.
 */
void HandScanner::NotifyObjectCollision(GameObject* gameObject) {
    assert(gameObject != NULL);
    if (gameObject && gameObject->Is("Drone")) {
        Player *player = (Player *) gameObject;
        if (player->Attacking()) {
            assert(player != NULL);
            Player *play = (Player *) StageState::GetPlayer();
            if (play->skills[4]) {
                assert(play != NULL);
                On();
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }

    assert(gameObject != NULL);
}

/**
 * Objective: it updates door action.
 *
 * @param TileMap* map.
 * @param float deltaTime - The amount of time to updates interactive door time.
 * @return none.
 */
void HandScanner::Update(TileMap* map, float deltaTime) {
    assert(map != NULL);
    Interactive::Update(map, deltaTime);
    Trigger();
}
