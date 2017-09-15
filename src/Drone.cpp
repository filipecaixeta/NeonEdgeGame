/**
    Copyright 2017 Neon Edge Game
    File Name: Drone.cpp
    Header File Name: Drone.h
    Class Name: Drone
    Objective: Define behavior and drone actions.

*/

#include "Drone.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"

/**
    Objective: Constructor method. Initializes the drone components.
    @param int x - Position of the drone on the x axis.
    @param int y - Position of the drone on the y axis.
    @return - No return.

*/
Drone::Drone(ItensManager* itemManager, int x, int y): Player(itemManager, x, y), active(false) {
    name = "Drone"; // Sets the drone name
    inputComponent = new DroneInputComponent(); // Creates independent movement of the drone in relation to the character.
    physicsComponent.SetKinetic(true); // Disables gravity for the drone.
    graphicsComponent = new DroneGraphicsComponent("Drone"); // Loads drone images (drone moving, firing and etc).
    soundComponent = new SoundComponent(name); // Loads drone sound effects.
    box.SetWH(graphicsComponent->GetSize());
    Empower(0);
}

/**
    Objective: Destructive method. It deallocates memory used by the class.
    @param - No parameter.
    @return - No return.

*/
Drone::~Drone() {
}

/**
    Objective: Generate/start drone attack.
    @param - No parameter.
    @return - No return.

*/
void Drone::Attack() {
    attacking.Start();
}

/**
    Objective: Activate the drone (control over the drone).
    @param - Boolean (on) informs drone state (enabled or disabled).
    @return - No return.

*/
void Drone::Activate(bool on) {
    active = on;
}

/**
    Objective: Inform drone activation status.
    @param - No parameter.
    @return - State of the drone.

*/
bool Drone::Active() {
    return active;

}

/**
    Objective: Sets the duration of the drone's attack.
    @param - Float (delayTime) duration of the attack.
    @return - No return.

*/
void Drone::UpdateTimers(float delayTime) {
    Player::UpdateTimers(delayTime);
}

/**
    Objective: Updates position of objects and draws them on the screen.
    @param - Pointer to character position.
    @param - Drone on map and duration of actions.
    @return - No return.

*/
void Drone::Update(TileMap *map, float delayTime) {
    UpdateTimers(delayTime); // Defines time parameters for modifying drone behavior.

    // Checks if the player is other than null.
    if (StageState::GetPlayer()) {

        // Checks whether the drone is active.
        if (active == true) {
            inputComponent->Update(this, delayTime); // Updates drone position according to input.
            physicsComponent.Update(this, map, delayTime); // Moves the drone on the screen.
        } else {
            facing = StageState::GetPlayer()->facing;

            // Checks which direction (left or right) the character has turned.
            if (StageState::GetPlayer()->facing == LEFT) {
                box.x = StageState::GetPlayer()->box.x + StageState::GetPlayer()->box.w-box.w; // Makes the drone turn to the left when the character turns to that position.
            } else {
                box.x = StageState::GetPlayer()->box.x; // Makes the drone turn to the right when the character turns to that position.
            }
            box.y = StageState::GetPlayer()->box.y - 5; // Make the drone come back to follow the character by positioning him above him.
        }

        // Checks if the drone is outside the screen boundaries.
        if (OutOfBounds(map)) {
            SetPosition(Vec2(269, 544)); // Resets the drone's position.
        }

        graphicsComponent->Update(this, delayTime); // Refresh drone image on screen according to your movement.
    }
}
