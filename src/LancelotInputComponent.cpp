#include "LancelotInputComponent.h"
#include "InputManager.h"
#include "StageState.h"
#include "Lancelot.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

LancelotInputComponent::LancelotInputComponent()
{

}

void LancelotInputComponent::Update(GameObject* obj, float dt)
{
	Lancelot* l = (Lancelot*) obj;
	InputManager &input = InputManager::GetInstance();
	// Move Left
	if(input.IsKeyDown(MOVE_LEFT_KEY,true))
	{
		l->physicsComponent.velocity.x -= 0.002*dt;
		l->facing = GameObject::LEFT;
	}
	// Move Right
	else if(input.IsKeyDown(MOVE_RIGHT_KEY,true))
	{
		l->physicsComponent.velocity.x += 0.002*dt;
		l->facing = GameObject::RIGHT;
	}
	// Stay Still
	else
	{
		l->physicsComponent.velocity.x = 0;
	}
	clamp(l->physicsComponent.velocity.x,-0.4f,0.4f);
	
	// Attack
	if(input.IsKeyDown(ATACK_KEY,true))
	{
		if(!l->Attacking())
		{
			//Starts attack timer
			l->Attack();
			//Generates attack object
			StageState::AddObject(new Melee("notattack.png", 2, 0, l->facing, 500, 1, l));
		}
	}
	
	// Jump
	if(input.KeyPress(JUMP_KEY,true))
	{
		// Ground Jump
		if(l->footing == GameObject::GROUNDED)
		{
			l->physicsComponent.velocity.y = -0.6;
		}
		// Wall-Jump from a wall to the left
		else if(l->footing == GameObject::LEFT_WALLED && l->lastFooting != GameObject::LEFT_WALLED)
		{
			l->physicsComponent.velocity.y = -0.6;
			l->physicsComponent.velocity.x = 0.6;
			l->facing = GameObject::RIGHT;
			l->lastFooting = GameObject::LEFT_WALLED;
		}
		// Wall-Jump from a wall to the right
		else if(l->footing == GameObject::RIGHT_WALLED && l->lastFooting != GameObject::RIGHT_WALLED)
		{
			l->physicsComponent.velocity.y = -0.6;
			l->physicsComponent.velocity.x = -0.6;
			l->facing = GameObject::RIGHT;
			l->lastFooting = GameObject::RIGHT_WALLED;
		}
	}

	// Fica invisivel
	//	if(input.IsKeyDown(SDLK_s))
	//		InvisibleState(dt);
}
