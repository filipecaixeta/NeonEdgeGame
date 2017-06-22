#include "DroneInputComponent.h"
#include "InputManager.h"
#include "Drone.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

DroneInputComponent::DroneInputComponent()
{

}

void DroneInputComponent::Update(Player* obj_, float dt_)
{
	InputComponent::Update(obj_,dt_);
	InputManager &input = InputManager::GetInstance();

	if(input.IsKeyDown(MOVE_LEFT_KEY, true))
		MoveLeft();
	else if(input.IsKeyDown(MOVE_RIGHT_KEY, true))
		MoveRight();
	else if(input.IsKeyDown(MOVE_UP_KEY, true))
		MoveUp();
	else if(input.IsKeyDown(MOVE_DOWN_KEY, true))
		MoveDown();
	else
		StayStill();
}
