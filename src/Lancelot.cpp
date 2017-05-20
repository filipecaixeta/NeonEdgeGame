#include "Lancelot.h"
#include "Camera.h"

Lancelot::Lancelot(int x, int y):
	inputComponent(),
	physicsComponent(),
	graphicsComponent("Lancelot"),
	saveComponent(SaveComponent::GetInstance())
{
	name = "Lancelot";
	Vec2 size = graphicsComponent.GetSize();
	box = Rect(x, y, size.x, size.y);
	facing = RIGHT;
	speed = Vec2(0, 0.6);
}

Lancelot::~Lancelot()
{

}

Lancelot* Lancelot::Get()
{
	return this;
}

bool Lancelot::IsDead()
{
	return (hitpoints < 1);
}

int Lancelot::GetHealth()
{
	return hitpoints;
}

void Lancelot::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning()) 
	{
		hitpoints -= (damage);
		invincibilityTimer.Start();
	}
}

void Lancelot::NotifyTileCollision(int tile, Face face)
{
	if(tile > 11)
	{
		Damage(1);
	}
}

void Lancelot::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Notattack"))
		Damage(1);
}

void Lancelot::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
}

void Lancelot::Update(float dt)
{
	UpdateTimers(dt);
	inputComponent.Update(this,dt);
	physicsComponent.Update(this,dt);
	graphicsComponent.Update(this,dt);
	saveComponent.Update(this,dt);
}

void Lancelot::Render()
{
	graphicsComponent.Render(GetPosition()-Camera::GetInstance().pos);
}
