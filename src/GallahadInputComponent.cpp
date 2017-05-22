#include "GallahadInputComponent.h"
#include "InputManager.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

GallahadInputComponent::GallahadInputComponent()
{

}

void GallahadInputComponent::Update(GameObject* obj, float dt)
{
	InputManager &input = InputManager::GetInstance();
	// Move Left
	if(input.IsKeyDown(SDLK_a))
	{
		obj->speed.x -= 0.002*dt;
		obj->facing = GameObject::LEFT;
	}
	// Move Right
	else if(input.IsKeyDown(SDLK_d))
	{
		obj->speed.x += 0.002*dt;
		obj->facing = GameObject::RIGHT;
	}
	// Stay Still
	else
	{
		obj->speed.x = 0;
	}
	clamp(obj->speed.x,-0.4f,0.4f);
	
	// Attack
	if(input.IsKeyDown(SDLK_e))
	{
		//obj->attacking = true;
	}
	
	// Jump
	if(input.KeyPress(SDLK_SPACE))
	{
		// Ground Jump
		if(obj->footing == GameObject::GROUNDED)
		{
			obj->speed.y = -0.6;
		}
		// Wall-Jump from a wall to the left
		else if(obj->footing == GameObject::LEFT_WALLED && obj->lastFooting != GameObject::LEFT_WALLED)
		{
			obj->speed.y = -0.6;
			obj->speed.x = 0.6;
			obj->facing = GameObject::RIGHT;
			obj->lastFooting = GameObject::LEFT_WALLED;
		}
		// Wall-Jump from a wall to the right
		else if(obj->footing == GameObject::RIGHT_WALLED && obj->lastFooting != GameObject::RIGHT_WALLED)
		{
			obj->speed.y = -0.6;
			obj->speed.x = -0.6;
			obj->facing = GameObject::RIGHT;
			obj->lastFooting = GameObject::RIGHT_WALLED;
		}
		obj->jumping = true;
		/*if(obj->wallJumping == 1)
			obj->speed.x = 0.4;
		if(obj->wallJumping == 2)
			obj->speed.x = -0.4;
		obj->lastWallJumping = obj->wallJumping;
		obj->wallJumping = 0;
		obj->jumpingPower = 1;*/
	}
	/*else if(input.KeyRelease(SDLK_SPACE))
	{
		obj->jumpingPower = 0;
	}
	else
	{
		if(obj->jumpingPower > 0 && obj->jumpingPower < 11)
		{
			obj->speed.y -= 0.03;
			obj->jumpingPower++;
		}
	}*/

	// Fica invisivel
	//	if(input.IsKeyDown(SDLK_s))
	//		InvisibleState(dt);
}
