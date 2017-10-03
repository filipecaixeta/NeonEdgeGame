/**
    Copyright (c) 2017 Neon Edge
    File Name: InputComponent.cpp
    Header File Name: InputComponent.h
    Class Name: InputComponent
    Objective: It manages the inputs components.

*/

#include "InputComponent.h"
#include "InputManager.h"

InputComponent::InputComponent() {
}

/**
    Objective: it destroys a input component.
    @param none.
    @return none.

*/
InputComponent::~InputComponent() {
}

/**
    Objective: it a contructor function that will update the player.
    @param Player* obj_ - is data reference of a player object.
    @param float dt_ - is the default number of your position.
    @return none.

*/
void InputComponent::Update(Player* obj_, float dt_) {
	obj = obj_;
	dt = dt_;
}

/**
    Objective: it manages the left movimentation.
    @param none.
    @return none.

*/
void InputComponent::MoveLeft() {
	obj->physicsComponent.velocity.x -= 0.002*dt;  //Sets less 0.002 to your current position in x.
	obj->facing = GameObject::LEFT;  // Turn the face object to left.
}

/**
    Objective: it manages the right movimentation.
    @param none.
    @return none.

*/
void InputComponent::MoveRight() {
	obj->physicsComponent.velocity.x += 0.002*dt; //Sets plus 0.002 to your current position in x.
	obj->facing = GameObject::RIGHT;  // Turn the face object to right.
}

/**
    Objective: it manages the up direction movimentation.
    @param none.
    @return none.

*/
void InputComponent::MoveUp() {
	obj->physicsComponent.velocity.y -= 0.002*dt;  // Sets less 0.002 to your current position in y.
}

/**
    Objective: it manages the down direction movimentation..
    @param none.
    @return none.

*/
void InputComponent::MoveDown() {
	obj->physicsComponent.velocity.y += 0.002*dt;  // Sets plus 0.002 to your current position in y.
}

/**
    Objective: it manages the stop movimentation.
    @param none.
    @return none.

*/
void InputComponent::StayStill() {
	obj->physicsComponent.velocity.x = 0; // set 0 to your current position in 0.
}

/**
    Objective: it manages the crouch movimentation.
    @param bool c - The data that have the event information.
    @return none.

*/
void InputComponent::Crouch(bool c) {
    // It verifies if the character will be croush or stand up.
	if (c == true) {
        // If yes, it makes the object character be croush.
		obj->Crouch();
	}
	else{
        // Else, it makes the object character be stand up.
		obj->Stand();
    }
}

/**
    Objective: it manages the attack skill.
    @param none.
    @return none.

*/
void InputComponent::Attack() {
    // It validate the attack skill, if the character object isn't attacking and isn't cooling, he attacks.
	if (!obj->Attacking() && !obj->Cooling()) {
		obj->Attack();
	}
}

/**
    Objective: it manages the severals ways that the object can jump..
    @param none.
    @return none.

*/
void InputComponent::Jump() {
	// Ground Jump
	if (obj->footing == GameObject::GROUNDED) {
		obj->soundComponent->SoundJump(); // display the jump sound.
		obj->physicsComponent.velocity.y = -1.0;
	}
	// Wall-Jump from a wall to the left
	else if (obj->footing == GameObject::LEFT_WALLED && obj->lastFooting != GameObject::LEFT_WALLED) {
		obj->physicsComponent.velocity.y = -0.6;
		obj->physicsComponent.velocity.x = 0.6;
		obj->facing = GameObject::RIGHT;  // Sets the face object to the right direction.
		obj->lastFooting = GameObject::LEFT_WALLED;
	}
	// Wall-Jump from a wall to the right
	else if (obj->footing == GameObject::RIGHT_WALLED && obj->lastFooting != GameObject::RIGHT_WALLED) {
		obj->physicsComponent.velocity.y = -0.6;
		obj->physicsComponent.velocity.x = -0.6;
		obj->facing = GameObject::RIGHT;  // Sets the face object to the right direction.
		obj->lastFooting = GameObject::RIGHT_WALLED;
	}
}

void InputComponent::Active() {
}

/**
    Objective: it manages the save.
    @param none.
    @return none.

*/
void InputComponent::Save(bool s) {
	obj->saveComponent.Save(s);
	obj->saveComponent.Update(obj, "savefile.txt");
}

/**
    Objective: it manages the process of items.
    @param none.
    @return none.

*/
void InputComponent::ProcessItems() {
	InputManager &input = InputManager::GetInstance();
	int hotItemPos = -1;
	if (input.KeyPress(HOT_KEY_1, true)) {
		hotItemPos = 0;
	}
	if (input.KeyPress(HOT_KEY_2, true)) {
		hotItemPos = 1;
	}
	if (input.KeyPress(HOT_KEY_3, true)) {
		hotItemPos = 2;
	}
	if (hotItemPos != -1) {
		obj->EvalItem(obj->itemManager->hotItens[hotItemPos]);
		obj->itemManager->ConsumeItem(hotItemPos);
	}
}
