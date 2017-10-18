/**
 *   Copyright (c) 2017 Neon Edge
 *   File Name: InputComponent.cpp
 *   Header File Name: InputComponent.h
 *   Class Name: InputComponent
 *   Objective: it manages the inputs components.
 */
#include <assert.h>

#include "InputComponent.h"
#include "InputManager.h"

/**
 * Objective: it constructs Character object in some given axes.
 *
 * @param none.
 * @return none.
 */
InputComponent::InputComponent() {
}

InputComponent::~InputComponent() {
}

/**
 * Objective: it will updates the player.
 *
 * @param Player *player - is data reference of a player object.
 * @param float deltaTime - is the default number of your position.
 * @return none.
 */
void InputComponent::Update(Player *player, float deltaTime) {
	assert(this->player != NULL);
	this->player = player;
    this->deltaTime = deltaTime;
}

/**
 * Objective: it manages the left movimentation.
 *
 * @param none.
 * @return none.
 */
void InputComponent::MoveLeft() {
	assert(player != NULL);
    // It sets less 0.002 to your current position in x.
    player->physicsComponent.velocity.x -= 0.002 * deltaTime;
    // It Turns the face object to left.
    player->facing = GameObject::LEFT;
}

/**
 * Objective: it manages the right movimentation.
 *
 * @param none.
 * @return none.
 */
void InputComponent::MoveRight() {
	assert(player != NULL);
    player->physicsComponent.velocity.x += 0.002 * deltaTime; //Sets plus 0.002 to your current position in x.
    player->facing = GameObject::RIGHT;  // Turn the face object to right.
}

/**
 * Objective: it manages the up direction movimentation.
 *
 * @param none.
 * @return none.
 */
void InputComponent::MoveUp() {
	assert(player != NULL);
    player->physicsComponent.velocity.y -= 0.002 * deltaTime;  // Sets less 0.002 to your current position in y.
}

/**
 * Objective: it manages the down direction movimentation..
 *
 * @param none.
 * @return none.
 */
void InputComponent::MoveDown() {
	assert(player != NULL);
    player->physicsComponent.velocity.y += 0.002 * deltaTime;  // Sets plus 0.002 to your current position in y.
}

/**
 * Objective: it manages the stop movimentation.
 *
 * @param none.
 * @return none.
 */
void InputComponent::StayStill() {
	assert(player != NULL);
    player->physicsComponent.velocity.x = 0; // set 0 to your current position in 0.
}

/**
 * Objective: it manages the crouch movimentation.
 *
 * @param bool crouchStatus - The data that have the event information.
 * @return none.
 */
void InputComponent::Crouch(bool crouchStatus) {
	assert(player != NULL);
	// It verifies if the character will be croush or stand up.
    if (crouchStatus == true) {
        // If yes, it makes the object character be croush.
        player->Crouch();
    } else {
        // Else, it makes the object character be stand up.
        player->Stand();
    }
}

/**
 * Objective: it manages the attack skill.
 *
 * @param none.
 * @return none.
 */
void InputComponent::Attack() {
	assert(player != NULL);
	// It validate the attack skill, if the character object isn't attacking and isn't cooling, he attacks.
    if (!player->Attacking() && !player->Cooling()) {
        player->Attack();
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it manages the severals ways that the object can jump..
 *
 * @param none.
 * @return none.
 */
void InputComponent::Jump() {
	assert(player != NULL);
    // Ground Jump
    if (player->footing == GameObject::GROUNDED) {
        player->soundComponent->SoundJump();  // display the jump sound.
        player->physicsComponent.velocity.y = - 1.0;
    // Wall-Jump from a wall to the left
    } else if (player->footing == GameObject::LEFT_WALLED && player->lastFooting != GameObject::LEFT_WALLED) {
        player->physicsComponent.velocity.y = - 0.6;
        player->physicsComponent.velocity.x = 0.6;
        player->facing = GameObject::RIGHT;  // Sets the face object to the right direction.
        player->lastFooting = GameObject::LEFT_WALLED;
    // Wall-Jump from a wall to the right
    } else if (player->footing == GameObject::RIGHT_WALLED && player->lastFooting != GameObject::RIGHT_WALLED) {
        player->physicsComponent.velocity.y = - 0.6;
        player->physicsComponent.velocity.x = - 0.6;
        player->facing = GameObject::RIGHT;  // Sets the face object to the right direction.
        player->lastFooting = GameObject::RIGHT_WALLED;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it manages the save.
 *
 * @param none.
 * @return none.
 */
void InputComponent::Active() {
}

/**
 * Objective: it manages the save.
 *
 * @param bool saveStatus - save status.
 * @return none.
 */
void InputComponent::Save(bool saveStatus) {
	assert(player != NULL);
    player->saveComponent.Save(saveStatus);
    player->saveComponent.Update(player, "savefile.txt");
}

/**
 * Objective: it manages the process of items.
 *
 * @param none.
 * @return none.
 */
void InputComponent::ProcessItems() {
    InputManager &input = InputManager::GetInstance();
    int hotItemPos = -1;
    if (input.KeyPress(HOT_KEY_1, true)) {
        hotItemPos = 0;
    } else {
        // It does nothing.
    }

    if (input.KeyPress(HOT_KEY_2, true)) {
        hotItemPos = 1;
    } else {
        // It does nothing.
    }

    if (input.KeyPress(HOT_KEY_3, true)) {
        hotItemPos = 2;
    } else {
        // It does nothing.
    }

    if (hotItemPos != -1) {
		assert(player != NULL);
        player->EvalItem(player->itemManager->hotItens[hotItemPos]);
        player->itemManager->ConsumeItem(hotItemPos);
    } else {
        // It does nothing.
    }
}
