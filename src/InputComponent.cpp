#include <InputComponent.h>
#include <InputManager.h>

InputComponent::InputComponent()
{

}

void InputComponent::Update(GameObject *obj, float dt)
{
	InputManager &input = InputManager::GetInstance();
	// Anda para esquerda
	if(input.IsKeyDown(SDLK_a))
	{
		obj->speed.x -= 0.002*dt;
	}
	// Anda para direita
	else if(input.IsKeyDown(SDLK_d))
	{
		obj->speed.x += 0.002*dt;
	}
	// Fica parado
	else
	{
		obj->speed.x = 0;
	}
	// Ataca
	if(input.IsKeyDown(SDLK_e))
	{
		obj->attacking = true;
	}
	// Pula
	if(input.KeyPress(SDLK_SPACE))
	{
		obj->jumping = true;
		obj->speed.y = -0.6;
		if(obj->wallJumping == 1)
			obj->speed.x = 0.4;
		if(obj->wallJumping == 2)
			obj->speed.x = -0.4;
		obj->lastWallJumping = obj->wallJumping;
		obj->wallJumping = 0;
		obj->jumpingPower = 1;
	}
	else if(input.KeyRelease(SDLK_SPACE))
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
	}

	// Fica invisivel
	//	if(input.IsKeyDown(SDLK_s))
	//		InvisibleState(dt);
	clamp(obj->speed.x,-0.4f,0.4f);
}
