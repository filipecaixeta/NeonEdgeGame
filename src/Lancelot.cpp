#include "Lancelot.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Lancelot::Lancelot(ItensManager* itemManager, int x, int y):
	Player(itemManager,x,y),
	blocking(1000),
	charges(0)
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
}

void Lancelot::Block()
{
	blocking.Start();
	energy -= 1;
	clamp(energy,0,5);
}

void Lancelot::Charge()
{
	charges++;
}

bool Lancelot::Blocking()
{
	return blocking.IsRunning();
}

int Lancelot::Charged()
{
	return charges;
}

void Lancelot::UpdateTimers(float dt)
{
	attacking.SetLimit(60+(200*charges));
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	if(attacking.GetElapsed() == 1)
	{
		charges = 0;
		attacking.Reset();
		attackCD.Start();
	}
	attackCD.Update(dt);
	regenCD.Update(dt);
	blocking.Update(dt);
}
