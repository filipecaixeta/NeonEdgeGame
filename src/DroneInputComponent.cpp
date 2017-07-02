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

	if(input.KeyPress(ACTIVE_KEY, true))
		Active();

	if(input.IsKeyDown(MOVE_LEFT_KEY, true))
		MoveLeft();
	else if(input.IsKeyDown(MOVE_RIGHT_KEY, true))
		MoveRight();
	else if(input.IsKeyDown(MOVE_UP_KEY, true))
		MoveUp();
	else if(input.IsKeyDown(MOVE_DOWN_KEY, true))
		MoveDown();
	else{
		StayStill();
		obj->physicsComponent.velocity.y = 0;
	}

	ProcessItems();
}

void DroneInputComponent::Active(){
	Drone* d = (Drone*) obj;
	if(d->GetActive() == true)
		d->SetActive(false);
	else
		d->SetActive(true);
}
