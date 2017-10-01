/**
    Copyright (c) 2017 Neon Edge Game.
    File Name: LancelotGraphicsComponent.cpp
    Header File Name: LancelotGraphicsComponent.h
    Class Name: LancelotGraphicsComponent
    Objective: manages Lancelot sprite action.

*/

#include "LancelotGraphicsComponent.h"
#include "Lancelot.h"

/**
    Objective: It constructs Lancelot graphics component object.
    @param string baseName_.
    @return none.

*/
LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseName_):
        GraphicsComponent(baseName_) {
    /*
    AddSprite(string baseName,
              string name - character action,
              int frameCount - value of frame count,
              int frameTime - value of frame time,
              bool loops = false - value of loops, by default loops it is setted to false);
    */
    AddSprite(baseName, "Idle", 8, 80);
    AddSprite(baseName, "Running", 8, 80);
    AddSprite(baseName, "Jumping", 8, 80, true);
    AddSprite(baseName, "Walled", 1, 0);
    AddSprite(baseName, "Crouching", 4, 80, true);
    AddSprite(baseName, "Blocking", 6, 80, true);
    AddSprite(baseName, "AttackingStraight", 3, 80, true);
    AddSprite(baseName, "AttackingUppercut", 3, 80, true);
    AddSprite(baseName, "AttackingChop", 4, 80, true);
    AddSprite(baseName, "AttackingSpear", 3, 80, true);
    AddSprite(baseName, "AttackingSword", 3, 80, true);
    AddSprite(baseName, "AttackingAxe", 4, 80, true);
    AddSprite(baseName, "Dying", 5, 50);
    sp = sprites["Idle"];
    surface = surfaces["Idle"];
}

/**
    Objective: It destroys Lancelot graphics component object.
    @param none.
    @return none.

*/
LancelotGraphicsComponent::~LancelotGraphicsComponent() {
}

/**
    Objective: It updates Lancelot sprite status by your action.
    @param GameObject *obj - object of Lancelot.
    @param float dt - value to update elapsed time of the sprite.
    @return none.

*/
void LancelotGraphicsComponent::Update(GameObject *obj, float dt) {
    // It instances the character.
    Lancelot *l = (Lancelot *) obj;
    // It verifies if character is going to left and it is setted.
    mirror = (obj->facing == GameObject::LEFT);
    // It verifies action of character to update sprite.
    if (l->Attacking()) {
        // If character is attacking, it verifies how the character is attacking
        // and it settes sprite action to respective action.
        UpdateSprite(obj, "Attacking" + l->GetCombo());
        // It verifies is character feet are in wall.
        if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
            // If yes, it updates character feet status to airborne.
            obj->footing = GameObject::AIRBORNE;
        }
    } else if (l->IsBlocking()) {
        // Else if character is blocking, character sprite action is updated to blocking.
        UpdateSprite(obj, "Blocking");
        // It verifies is character feet are in wall.
        if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
            // If yes, it updates character feet status to airborne.
            obj->footing = GameObject::AIRBORNE;
        }
    } else if (l->Crouching()) {
        // Else if character is crouching, character sprite action is updated to crouching.
        UpdateSprite(obj, "Crouching");
        // It verifies is character feet are in wall.
        if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
            // If yes, it updates character feet status to airborne.
            obj->footing = GameObject::AIRBORNE;
        }
    } else if (obj->footing == GameObject::AIRBORNE) {
        // Else if character feet status is airborne, character sprite action is updated to jumping.
        UpdateSprite(obj, "Jumping");
    } else if (obj->footing == GameObject::LEFT_WALLED ||
               obj->footing == GameObject::RIGHT_WALLED) {
        // Else if character feet are in wall, character sprite action is updated to walled.
        UpdateSprite(obj, "Walled");
        // It verifies if character is going to left and it is setted.
        mirror = (obj->footing == GameObject::LEFT_WALLED);
    } else if (l->physicsComponent.velocity.x == 0) {
        // Else if character is idle, character sprite action is updated to idle.
        UpdateSprite(obj, "Idle");
    } else {
        // Else, character sprite action is updated to running.
        UpdateSprite(obj, "Running");
    }

    // It verifies if the character is dying.
    if (obj->dieTimer.IsRunning()) {
        // If character is dying, character sprite action is updated to dying.
        UpdateSprite(obj, "Dying");
    }

    sp->Mirror(mirror);  // It swaps direction of character sprite.
    sp->Update(dt);  // It updates elapsed time of the sprite with value passed, dt.
}
