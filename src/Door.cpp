/*
  Copyright 2017 Neon Edge Game
  File Name: Door.cpp
  Header File Name: Door.h
  Class Name: Door
  Objective: Class responsible for moving the doors of the game.
*/

#include "Door.h"
#include "Camera.h"
#include "StageState.h"

/*
  Function Objective: Constructor method that defines the initial port parameters.
  param: Initial position of the door (x, y).
  return: No return.
*/
Door::Door(int x, int y):
  Interactive(x,y,"Door") {
    name = "Door"; // Defines name of the door.
    open = false;  // Initializes of the door closed.
}

/*
  Function Objective: Destructor method that frees memory used by the class.
  param: No parameters.
  return: No return.
*/
Door::~Door() {
}

/*
  Function Objective: Turned on or off the door led according to the state of your enable.
  param: string playerName refers to the first part of the audio file name.
  return: No return.
*/
void Door::Trigger() {

    // Checks if the port is enabled
    if (Active()) {
        Off(); // Off the door led.
    } else {
        On();  // Turns on the door led.
    }
}

/*
  Function Objective: Define door movement.
  param: .
  return: No return.
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

/*
  Function Objective: Draws the door on the map.
  param: No parameters.
  return: No return.
*/
void Door::Render() {

    // Checks whether the door is closed or inactive.
    if (!open || !Active()) {
        graphicsComponent->Render(GetPosition() - Camera::GetInstance().pos); // Renders port on screen.
    }
}
