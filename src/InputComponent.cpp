#include "InputComponent.h"

InputComponent::InputComponent()
{

}

InputComponent::~InputComponent()
{
	
}

void InputComponent::Update(Player* obj_, float dt_)
{
	obj = obj_;
	dt = dt_;
}

void InputComponent::MoveLeft()
{
	obj->physicsComponent.velocity.x -= 0.002*dt;
	obj->facing = GameObject::LEFT;
}

void InputComponent::MoveRight()
{
	obj->physicsComponent.velocity.x += 0.002*dt;
	obj->facing = GameObject::RIGHT;
}

void InputComponent::MoveUp(){
	obj->physicsComponent.velocity.y -= 0.002*dt;
}

void InputComponent::MoveDown(){
	obj->physicsComponent.velocity.y += 0.002*dt;
}

void InputComponent::StayStill()
{
	obj->physicsComponent.velocity.x = 0;
}

void InputComponent::Crouch(bool c)
{
	if (c == true)
		obj->Crouch();
	else
		obj->Stand();
}

void InputComponent::Attack()
{
	if(!obj->Attacking() && !obj->Cooling())
	{
		obj->Attack();
	}
}

void InputComponent::Jump()
{
	// Ground Jump
	if(obj->footing == GameObject::GROUNDED)
	{
		obj->physicsComponent.velocity.y = -0.6;
	}
	// Wall-Jump from a wall to the left
	else if(obj->footing == GameObject::LEFT_WALLED && obj->lastFooting != GameObject::LEFT_WALLED)
	{
		obj->physicsComponent.velocity.y = -0.6;
		obj->physicsComponent.velocity.x = 0.6;
		obj->facing = GameObject::RIGHT;
		obj->lastFooting = GameObject::LEFT_WALLED;
	}
	// Wall-Jump from a wall to the right
	else if(obj->footing == GameObject::RIGHT_WALLED && obj->lastFooting != GameObject::RIGHT_WALLED)
	{
		obj->physicsComponent.velocity.y = -0.6;
		obj->physicsComponent.velocity.x = -0.6;
		obj->facing = GameObject::RIGHT;
		obj->lastFooting = GameObject::RIGHT_WALLED;
	}
}

void InputComponent::Active(){
	
}

void InputComponent::Save(bool s)
{
	obj->saveComponent.Save(s);
	obj->saveComponent.Update(obj, "savefile.txt");
}
