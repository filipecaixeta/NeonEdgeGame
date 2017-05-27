#include "Gallahad.h"
#include "Camera.h"

Gallahad::Gallahad(int x, int y):
	inputComponent(),
	physicsComponent(),
	graphicsComponent("Gallahad"),
	saveComponent(SaveComponent::GetInstance())
{
	name = "Gallahad";
	Vec2 size = graphicsComponent.GetSize();
	box = Rect(x, y, size.x, size.y);
	facing = RIGHT;
}

Gallahad::~Gallahad()
{

}

bool Gallahad::IsDead()
{
	return (hitpoints < 1);
}

int Gallahad::GetHealth()
{
	return hitpoints;
}

void Gallahad::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning()) 
	{
		hitpoints -= (damage);
		invincibilityTimer.Start();
	}
}

void Gallahad::NotifyTileCollision(int tile, Face face)
{
	if(tile > 11)
	{
		Damage(1);
	}
}

void Gallahad::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Notattack"))
		Damage(1);
}

void Gallahad::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
}

void Gallahad::Update(float dt)
{
	UpdateTimers(dt);
	inputComponent.Update(this,dt);
	physicsComponent.Update(this,dt);
	graphicsComponent.Update(this,dt);
	saveComponent.Update(this,dt);
}

void Gallahad::Render()
{
	graphicsComponent.Render(GetPosition()-Camera::GetInstance().pos);
}
