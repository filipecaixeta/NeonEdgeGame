/**
    Copyright (c) 2017 Neon Edge
    File Name: Door.cpp
    Header File Name: Door.h
    Class Name: Door
    Objective: Class responsible for moving the doors of the game.

*/

#include "Door.h"
#include "Camera.h"
#include "StageState.h"

/**
    Objective: Constructor method that defines the initial port parameters.
    @param int doorPositionX  - Initial position of the door on the x axis.
    @param int doorPositionY - Initial position of the door on the y axis.
    @return - none.

*/
Door::Door(int doorPositionX, int doorPositionY):
  Interactive(doorPositionX, doorPositionY,"Door") {
    name = "Door"; // Defines name of the door.
    doorOpen = false;  // Initializes of the door closed.
}

/**
    Objective: Destructor method that frees memory used by the class.
    @param - No parameters.
    @return - none.

*/
Door::~Door() {
}

/**
    Objective: Turned on or off the door led according to the state of your enable.
    @param - No parameters.
    @return - none.

*/
void Door::Trigger() {

    // Checks if the port is enabled
    if (Active()) {
        Off(); // Off the door led.
    } else {
        On();  // Turns on the door led.
    }
}

/**
    Function Objective: Define door movement.
    @param TileMap* worldMap - Game Map.
    @param float delayTime -  Trigger to update the game screen.
    @return: none.

*/
void Door::Update(TileMap* worldMap, float delayTime) {
    doorOpen = false; // Closes the door

    // Checks if the port is enabled.
    if (Active()) {
        Rect doorMovementRadius = Rect(box.x - 100, box.y - 100, box.w + 200, box.h + 200); // Sets door opening movement.
        GameObject* player = StageState::GetPlayer();

        // Checks if the door activation button are pressed.
        if (doorMovementRadius.OverlapsWith(player->box)) {
            doorOpen = true; // Opens the door
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
    graphicsComponent->Update(this, delayTime); // Updates game screen.
}

/**
    Objective: Draws the door on the map.
    @param - No parameters.
    @return - none.

*/
void Door::Render() {

    // Checks whether the door is closed or inactive.
    if (!doorOpen || !Active()) {
        graphicsComponent->Render(GetPosition() - Camera::CheckInstance().screenPosition); // Renders port on screen.
    } else {
        // It does nothing.
    }
}
