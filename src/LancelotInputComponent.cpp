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
		clamp(obj->physicsComponent.velocity.x,-1.6f,1.6f);
	else
		clamp(obj->physicsComponent.velocity.x,-0.4f,0.4f);

	if(input.IsKeyDown(CROUCH_KEY,  true))
		Crouch(true);
	else
		Crouch(false);

	if(input.KeyPress(ATTACK_KEY,  true))
	{
		if(input.IsKeyDown(MOVE_LEFT_KEY,  true) || input.IsKeyDown(MOVE_RIGHT_KEY,  true))
		{	
			if(obj_->skills[6])
				Combo("Axe");
			else
				Combo("Chop");
		}
		else if(input.IsKeyDown(SDLK_w))
		{
			if(obj_->skills[5])
				Combo("Sword");
			else
				Combo("Uppercut");
		}
		else
		{
			if(obj_->skills[4])
				Combo("Spear");
			else
				Combo("Straight");
		}
		Attack();
	}
	
	if(input.IsKeyDown(SPECIAL_KEY, true))
		Block();
	else
		Stop();

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
	Lancelot *l = (Lancelot*) obj;
	if(l->GetEnergy() > 0)
	{
		l->Block();
	}
	else
	{
		l->Stop();
	}
}

void LancelotInputComponent::Stop()
{
	Lancelot *l = (Lancelot*) obj;
	l->Stop();
}

void LancelotInputComponent::Combo(std::string c)
{
	Lancelot *l = (Lancelot*) obj;
	l->Combo(c);
}
