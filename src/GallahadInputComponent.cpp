#include "GallahadInputComponent.h"
#include "InputManager.h"
#include "Gallahad.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

GallahadInputComponent::GallahadInputComponent()
{

}

void GallahadInputComponent::Update(Player* obj_, float dt_)
{
	InputComponent::Update(obj_,dt_);
	InputManager &input = InputManager::GetInstance();

	if(input.IsKeyDown(ACTIVE_KEY, true))
		Active();

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

	if(input.IsKeyDown(ATTACK_KEY,  true))
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

	if(input.MousePress(LEFT_MOUSE_BUTTON))
		Save(true);
	if(input.MousePress(RIGHT_MOUSE_BUTTON))
		Save(false);
}

void GallahadInputComponent::Hide()
{
	Gallahad *g = (Gallahad*)obj;
	if(g->GetEnergy() > 0 && !g->Hiding())
	{
		g->Hide();
	}
}

void GallahadInputComponent::Active(){
	Gallahad* g = (Gallahad*) obj;
	if(g->GetActive() == true)
		g->SetActive(false);
	else
		g->SetActive(true);
}