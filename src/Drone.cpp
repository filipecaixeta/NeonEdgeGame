/**
    Copyright (c) 2017 Neon Edge
    File Name: Drone.cpp
    Header File Name: Drone.h
    Class Name: Drone
    Objective: Class responsible for drone movement and actions.

*/

#include "Drone.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include <assert.h>

/**
    Objective: Constructor method. Initializes the drone components.
    @param int dronePositionX- Position of the drone on the x axis.
    @param int dronePositionY - Position of the drone on the y axis.
    @param int dronePositionX - Position of the character on the x axis.
    @param int dronePositionY - Position of the character on the Y axis.
    @return - none.

*/
Drone::Drone(ItemsManager* itemManager, int dronePositionX, int dronePositionY):
    Player(itemManager, dronePositionX, dronePositionY), droneActive(false) {
    name = ""; // Sets the drone name
    inputComponent = new DroneInputComponent(); // Creates independent movement of the drone in
                                                // relation to the character.
    assert(inputComponent != nullptr);

    physicsComponent.SetKinetic(true); // Disables gravity for the drone.
    graphicsComponent = new DroneGraphicsComponent("Drone"); // Loads drone images
                                                             //(drone moving, firing and etc).
    assert(graphicsComponent != nullptr);

    soundComponent = new SoundComponent(name); // Loads drone sound effects.
    assert(soundComponent != nullptr);

    box.SetWH(graphicsComponent->GetSize());
    Empower(0);
}

/**
    Objective: Destructive method. It deallocates memory used by the class.
    @param - No parameter.
    @return - none.

*/
Drone::~Drone() {
}

/**
    Objective: Generate/start drone attack.
    @param - No parameter.
    @return - none.

*/
void Drone::Attack() {
    attacking.Start();

}

/**
    Objective: Activate the drone (control over the drone).
    @param - Boolean (turnOnDrone) informs drone state (enabled or disabled).
    @return - none.

*/
void Drone::DroneActivate(bool turnOnDrone) {
    droneActive = turnOnDrone;
}

/**
    Objective: Inform drone activation status.
    @param - No parameter.
    @return - State of the drone.

*/
bool Drone::isActive() {
    return droneActive;
}

/**
    Objective: Sets the duration of the drone's attack.
    @param - Float (delayTime) duration of the attack.
    @return - none.

*/
void Drone::UpdateTimers(float delayTime) {
    Player::UpdateTimers(delayTime);
}


/**
    Objective: Changes the drone side and causes the drone to follow the character
    @param - bool (droneActive) drone enablement state.
    @return - none.

*/
void Drone::FollowsCharacter(bool droneActive) {
    // Test expected value
    assert(droneActive == false);

    //Face of the character
    facing = StageState::GetPlayer()->facing;

    // Checks which direction (left or right) the character has turned.
    if (StageState::GetPlayer()->facing == LEFT) {
        box.x = StageState::GetPlayer()->box.x + StageState::GetPlayer()->box.w - box.w; // Causes the drone to follow the character as he turns to the left.
    } else {
        box.x = StageState::GetPlayer()->box.x; // Causes the drone to follow the character as he turns to the hight.
    }
    box.y = StageState::GetPlayer()->box.y - 5; // Make the drone come back to follow the character by positioning him above him.
}



/**
    Objective: Updates position of objects and draws them on the screen.
    @param - Pointer to character position.
    @param - Drone on map and duration of actions.
    @return - none.

*/
void Drone::Update(TileMap* map, float delayTime) {
    UpdateTimers(delayTime); // Defines time parameters for modifying drone behavior.

    // Checks if the player is other than null.
    if (StageState::GetPlayer()) {
        // Checks whether the drone is active.
        if (droneActive) {
            assert(droneActive == true);
            inputComponent->Update(this, delayTime); // Updates drone position according to input.
            physicsComponent.Update(this, map, delayTime); // Moves the drone on the screen.
        } else {
            FollowsCharacter(droneActive);
        }
        // Checks if the drone is outside the screen boundaries.
        if (OutOfBounds(map)) {
            SetPosition(Vec2(269, 544)); // Resets the drone's position.
        } else {
             // It does nothing.
        }
        graphicsComponent->Update(this, delayTime); // Refresh drone image on screen according to your movement.
    } else {
         // It does nothing.
    }
}
