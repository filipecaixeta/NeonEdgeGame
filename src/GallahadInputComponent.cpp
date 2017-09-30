#include "GallahadInputComponent.h"
#include "InputManager.h"
#include "Gallahad.h"
#include "Camera.h"
#include "Drone.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

GallahadInputComponent::GallahadInputComponent()
{

}

void GallahadInputComponent::Update(Player* obj_, float dt_)
{
	InputComponent::Update(obj_,dt_);
	InputManager& input = InputManager::GetInstance();

	if(input.KeyPress(ACTIVE_KEY, true))
	{
		Toggle();
		//Camera::GetInstance().CreateFocus(); PEGAR PONTEIRO PARA O DRONE
	}

	Gallahad *g = (Gallahad*) obj_;
	if(g->Active()) 
	{
		if(input.IsKeyDown(MOVE_LEFT_KEY, true))
			MoveLeft();
		else if(input.IsKeyDown(MOVE_RIGHT_KEY, true))
			MoveRight();
		else
			StayStill();
		if(obj_->Crouching())
			clamp(obj->physicsComponent.velocity.x,-0.2f,0.2f);
		else
			clamp(obj->physicsComponent.velocity.x,-0.4f,0.4f);
		
		if(input.IsKeyDown(CROUCH_KEY, true))
			Crouch(true);
		else
			Crouch(false);

		if(input.IsKeyDown(ATTACK_KEY, true))
		{
			Gallahad* g = (Gallahad*) obj_;
			g->Shoot();
			Attack();
		}
		else
		{
			Gallahad* g = (Gallahad*) obj_;
			g->Hold();
		}

		if(input.KeyPress(SPECIAL_KEY, true))
			Hide();

		if(input.KeyPress(JUMP_KEY, true))
			Jump();
	}

	ProcessItems();
}

void GallahadInputComponent::Hide()
{
	Gallahad *g = (Gallahad*)obj;
	if(g->GetEnergy() > 0 && !g->Hiding())
	{
		g->Hide();
	}
}

void GallahadInputComponent::Toggle()
{
	Gallahad* g = (Gallahad*) obj;
	if(g->Active())
	{
		g->Activate(false);
		g->GetDrone()->DroneActivate(true);
		Camera::CheckInstance().CreateFocus(g->GetDrone());
	}
	else
	{
		g->Activate(true);
		g->GetDrone()->DroneActivate(false);
		Camera::CheckInstance().CreateFocus(g);
	}
}
