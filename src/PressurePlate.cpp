/**
    Copyright (c) 2017 Neon Edge
    File Name: PressurePlate.cpp
    Header File Name: PressurePlate.h
    Class Name: PressurePlate
    Objective: Class responsible for manager the pressure plate.

*/

#include "PressurePlate.h"
#include "Camera.h"

/**
    Objective: Construction method that invoke the components of the class PressurePlate
    @param int x - The dimension of pressure plate in x.
    @param int y - The dimension of pressure plate in y.
    @param Interactive* d - A Interactive object..
    @return - none.

*/
PressurePlate::PressurePlate(int x, int y, Interactive* d):
	Interactive(x,y,"PressurePlate")
{
	name = "PressurePlate";
	door = d;
}

/**
    Objective: Function that destroy the PressurePlate.
    @param - none.
    @return - none.

*/
PressurePlate::~PressurePlate() {

}

/**
    Objective: Function used to set the state On or Off in the trigger.
    @param - none.
    @return - none.

*/
void PressurePlate::Trigger() {
    // Control the trigger to inform the stage
	if (Active()) {
		door->On();  // Receive the data information that the stage trigger is on.
	} else {
		door->Off();  // Receive the data information that the stage trigger is off.

	}
}

/**
    Objective: Used to ensure a object collision.
    @param GameObject* other - A data reference of a game object.
    @return - none.

*/
void PressurePlate::NotifyObjectCollision(GameObject* other) {
	On();
}

/**
    Objective: Used to update putting the stages in correct state.
    @param string fase - Refers to the stage of game.
    @return - none.

*/
void PressurePlate::Update(TileMap* map, float dt) {
	Interactive::Update(map,dt);
	Trigger();
	Off();
}
