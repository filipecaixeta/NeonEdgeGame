#include "AIMovingOnGroudInputComponent.h"

AIMovingOnGroudInputComponent::AIMovingOnGroudInputComponent() {
}

void AIMovingOnGroudInputComponent::Update(Character *character, float deltaTime) {
	this->character = character;
	this->deltaTime = deltaTime;
	MoveLeft();
}
