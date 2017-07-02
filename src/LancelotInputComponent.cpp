#include "LancelotInputComponent.h"
#include "InputManager.h"
#include "Lancelot.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

LancelotInputComponent::LancelotInputComponent()
{

}

void LancelotInputComponent::Update(Player* obj_, float dt_)
{
	InputComponent::Update(obj_,dt_);
	InputManager &input = InputManager::GetInstance();

	if(input.IsKeyDown(MOVE_LEFT_KEY, true))
		MoveLeft();
	else if(input.IsKeyDown(MOVE_RIGHT_KEY, true))
		MoveRight();
	else
		StayStill();
	if(obj->Crouching())
		clamp(obj->physicsComponent.velocity.x,-0.2f,0.2f);
	else
		clamp(obj->physicsComponent.velocity.x,-0.4f,0.4f);

	if(input.IsKeyDown(CROUCH_KEY,  true))
		Crouch(true);
	else
		Crouch(false);

	if(input.KeyPress(ATTACK_KEY,  true))
	{
		Attack();
		Lancelot *l = (Lancelot*)obj;
		if(l->Charged() < 6)
			l->Charge();
	}
	
	if(input.IsKeyDown(SPECIAL_KEY, true))
		Block();

	if(input.KeyPress(JUMP_KEY, true))
		Jump();

	if(input.MousePress(LEFT_MOUSE_BUTTON))
		Save(true);
	if(input.MousePress(RIGHT_MOUSE_BUTTON))
		Save(false);

	ProcessItems();
}

void LancelotInputComponent::Block()
{
	Lancelot *l = (Lancelot*)obj;
	if(l->GetEnergy() > 0 && !l->Blocking())
	{
		l->Block();
	}
}
