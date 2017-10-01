/**
    Copyright (c) 2017 Neon Edge Game.
    File Name: GallahadGraphicsComponent.cpp
    Header File Name: GallahadGraphicsComponent.h
    Class Name: GallahadGraphicsComponent
    Objective: manages Gallahad sprite action.

*/

#include "GallahadGraphicsComponent.h"
#include "Gallahad.h"
#include "Rect.h"

/**
    Objective: It constructs Gallahad graphics component object.
    @param string baseName_.
    @return none.

*/
GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseName_):
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
    AddSprite(baseName, "Crouching", 4, 80, true);
    AddSprite(baseName, "Active", 4, 80, true);
    AddSprite(baseName, "Jumping", 8, 80, true);
    AddSprite(baseName, "Shot", 4, 80, true);
    AddSprite(baseName, "RunningShot", 8, 80);
    AddSprite(baseName, "JumpingShot", 8, 80, true);
    AddSprite(baseName, "Dying", 8, 100, true);
    sp = sprites["Idle"];
    surface = surfaces["Idle"];
}

/**
    Objective: It destroys gallahad graphics component object.
    @param none.
    @return none.

*/
GallahadGraphicsComponent::~GallahadGraphicsComponent() {
}

/**
    Objective: It updates Gallahad sprite status by your action.
    @param GameObject *obj - object of Gallahad.
    @param float dt - value to update elapsed time of the sprite.
    @return none.

*/
void GallahadGraphicsComponent::Update(GameObject *obj, float dt) {
    // It instances the character.
    Gallahad *g = (Gallahad *) obj;
    // It verifies if character is going to left and it is setted.
    mirror = (obj->facing == GameObject::LEFT);
    // It verifies action of character to update sprite.
    if (g->IsShooting()) {
        // If character is shooting, it verifies how the character is shooting.
        if (g->physicsComponent.velocity.x != 0) {
            // If character speed is non-zero, character sprite action is updated to running shot.
            UpdateSprite(obj, "RunningShot");
        } else if (obj->footing == GameObject::AIRBORNE) {
            // If character feet are airborne, character sprite action is updated to jumping shot.
            UpdateSprite(obj, "JumpingShot");
        } else {
            // Else, character sprite action is updated to 'simple' shot.
            UpdateSprite(obj, "Shot");
        }

        // It verifies is character feet are in wall.
        if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
            // If yes, it updates character feet status to airborne.
            obj->footing = GameObject::AIRBORNE;
        }
    } else if (g->Crouching()) {
        // Else if character is crouching, character sprite action is updated to crouching.
        UpdateSprite(obj, "Crouching");
        // It verifies is character feet are in wall.
        if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
            // If yes, it updates character feet status to airborne.
            obj->footing = GameObject::AIRBORNE;
        }
    } else if (!g->Active()) {
        // Else if character is not active, character sprite action is updated to active.
        UpdateSprite(obj, "Active");
        // It verifies is character feet are in wall.
        if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
            // If yes, it updates character feet status to airborne.
            obj->footing = GameObject::AIRBORNE;
        }
    } else if (obj->footing == GameObject::AIRBORNE) {
        // Else if character feet status is airborne, character sprite action is updated to jumping.
        UpdateSprite(obj, "Jumping");
    } else if (g->physicsComponent.velocity.x == 0) {
        // Else if character is idle, character sprite action is updated to idle.
        UpdateSprite(obj, "Idle");
    } else {
        // Else, character sprite action is updated to running.
        UpdateSprite(obj, "Running");
    }

    // It verifies if the character is using transparency power.
    if (g->IsHiding()) {
        // If yes, changes transparency to 30 percent.
        sp->SetTransparency(0.3);
    } else {
        // Else, keeps transparency at 100 percent.
        sp->SetTransparency(1);
    }

    // It verifies if the character is dying.
    if (obj->dieTimer.IsRunning()) {
        // If character is dying, character sprite action is updated to dying.
        UpdateSprite(obj, "Dying");
    }

    sp->Mirror(mirror);  // It swaps direction of character sprite.
    sp->Update(dt);  // It updates elapsed time of the sprite with value passed, dt.
}
