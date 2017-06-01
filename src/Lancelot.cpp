#include "Lancelot.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Lancelot::Lancelot(int x, int y):
	Character(x,y),
	blocking(1000)
{
	inputComponent = new LancelotInputComponent();
	graphicsComponent = new LancelotGraphicsComponent("Lancelot");
	name = "Lancelot";
	box.SetWH(graphicsComponent->GetSize());
}

Lancelot::~Lancelot()
{

}

void Lancelot::Attack()
{
	//Starts attack timer
	attacking.Start();
	//Generates attack object
	StageState::AddObject(new Melee("Melee.png", 2, 0, this, 500, 1));
}

void Lancelot::Block()
{
	blocking.Start();
	energy -= 1;
	clamp(energy,0,5);
}

bool Lancelot::Blocking()
{
	return blocking.IsRunning();
}

void Lancelot::UpdateTimers(float dt)
{
	Character::UpdateTimers(dt);
	blocking.Update(dt);
}
