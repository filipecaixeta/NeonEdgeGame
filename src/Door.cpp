/**
    Copyright (c) 2013 Thomas Park
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
    @param int x - Initial position of the door on the x axis.
    @param int y - Initial position of the door on the y axis.
    @return - none.

*/
Door::Door(int x, int y):
  Interactive(x,y,"Door") {
    name = "Door"; // Defines name of the door.
    open = false;  // Initializes of the door closed.
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
    @param TileMap* map - Game Map.
    @return: none.

*/
void Door::Update(TileMap* map, float delayTime) {
    open = false; // Closes the door

    // Checks if the port is enabled.
    if (Active()) {
        Rect radius = Rect(box.x-100, box.y-100, box.w+200, box.h+200); // Sets door opening movement.
        GameObject* player = StageState::GetPlayer();

        // Checks if the door activation button are pressed.
        if (radius.OverlapsWith(player->box)) {
            open = true; // Opens the door
        }
    }
    graphicsComponent->Update(this,delayTime);
}

/**
    Objective: Draws the door on the map.
    @param - No parameters.
    @return - none.

*/
void Door::Render() {

    // Checks whether the door is closed or inactive.
    if (!open || !Active()) {
        graphicsComponent->Render(GetPosition() - Camera::GetInstance().pos); // Renders port on screen.
    }
}
