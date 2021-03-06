/**
 * Copyright (c) 2017 Neon Edge
 * File Name: Door.cpp
 * Header File Name: Door.h
 * Class Name: Door
 * Objective: Class responsible for moving the doors of the game.
 */

#include "Door.h"
#include "Camera.h"
#include "StageState.h"
#include <assert.h>
#include "Logger.h"

/**
 * Objective: Method responsible for testing float parameters received in functions.
 *
 * @param float testFloat - Value to be tested.
 * @return - False whether the value is valid or true if the value is valid.
 */
bool CheckFloatDoor(float testFloat) {
    bool veryValue = false;
    if ((testFloat >= FLOAT_SIZE_MIN ) && (testFloat <= FLOAT_SIZE_MAX)) {
        veryValue = true;
        Log::instance.info("Valid value! Method CheckFloatDoor Door");          
    } else {
        Log::instance.error("Tested value higher or lower than allowed!");          
        // It does nothing.
    }
    assert(veryValue == false || veryValue == true);    
    return veryValue;
}

/**
 *  Objective: Constructor method that defines the initial port parameters.
 *
 * @param int doorPositionX  - Initial position of the door on the x axis.
 * @param int doorPositionY - Initial position of the door on the y axis.
 * @return - none.
 */
Door::Door(int doorPositionX, int doorPositionY):
  Interactive(doorPositionX, doorPositionY,"Door") {
    name = "Door"; // Defines name of the door.
    doorOpen = false;  // Initializes of the door closed.
    Log::instance.info("Door builder started!");      
}

/**
 * Objective: Destructor method that frees memory used by the class.
 *
 * @param - No parameters.
 * @return - none.
 */
Door::~Door() {
}

/**
 * Objective: Turned on or off the door led according to the state of your enable.
 *
 * @param - No parameters.
 * @return - none.
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
 * Function Objective: Define door movement.
 *
 * @param TileMap* worldMap - Game Map.
 * @param float delayTime -  Trigger to update the game screen.
 * @return: none.
 */
void Door::Update(TileMap* worldMap, float delayTime) {
    doorOpen = false; // Closes the door

    if ((worldMap) && (CheckFloatDoor(delayTime))) {
        assert(worldMap != NULL);
        assert(delayTime >= FLOAT_MIN_SIZE && delayTime <= FLOAT_MAX_SIZE);
        // Checks if the port is enabled.
        if (Active()) {
            Rect doorMovementRadius = Rect(box.x - MOVE_DOOR_POSITION_XY, box.y - MOVE_DOOR_POSITION_XY,
                                      box.w + MOVE_DOOR_HW, box.h + MOVE_DOOR_HW); // Sets door opening movement.
            GameObject* player = StageState::GetPlayer();

            // Checks if the door activation button are pressed.
            if (doorMovementRadius.OverlapsWith(player->box)) {
                assert(player != NULL);
                doorOpen = true; // Opens the door 
                Log::instance.info("Door enabled and open!");                                  
            } else {
                // It does nothing.
            }
        } else {
            Log::instance.info("Port disabled!");                                             
            // It does nothing.
        }
        graphicsComponent->Update(this, delayTime); // Updates game screen.
        assert(worldMap != NULL);
    } else {
        Log::instance.error("Check the time parameter!");                                         
        // It does nothing.
    }
}

/**
 * Objective: Draws the door on the map.
 *
 * @param - No parameters.
 * @return - none.
 */
void Door::Render() {

    // Checks whether the door is closed or inactive.
    if (!doorOpen || !Active()) {
        graphicsComponent->Render(GetPosition() - Camera::CheckInstance().screenPosition); // Renders port on screen.
        Log::instance.info("Door closed rendered!");                                                 
    } else {                                                   
        // It does nothing.
    }
}
