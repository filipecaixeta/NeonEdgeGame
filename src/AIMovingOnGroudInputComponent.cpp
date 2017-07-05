#include "AIMovingOnGroudInputComponent.h"

AIMovingOnGroudInputComponent::AIMovingOnGroudInputComponent()
{

}

void AIMovingOnGroudInputComponent::Update(Character* obj_, float dt_)
{
	obj = obj_;
	dt = dt_;
	MoveLeft();
}
