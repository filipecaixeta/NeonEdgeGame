#include "Lancelot.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"

#include <cstdlib>
#include <ctime>

Lancelot::Lancelot(ItensManager* itemManager, int x, int y):
	Player(itemManager,x,y),
	blocking(1000)
{
	name = "Lancelot";
	inputComponent = new LancelotInputComponent();
	graphicsComponent = new LancelotGraphicsComponent("Lancelot");
	box.SetWH(graphicsComponent->GetSize());
	attackCD.SetLimit(0);
	srand(time(NULL));
}

Lancelot::~Lancelot()
{

}

void Lancelot::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning())
	{
		if(blocking)
		{
			int n = rand()%100 + 1;
			if(skills[0])
			{
				if(n < 61)
					energy -= 1;
			}
			else if(skills[1])
			{
				if(n < 76)
					energy -= 1;
			}
			else if(skills[2])
			{
				if(n < 91)
					energy -= 1;
			}
			else
			{
				energy -= 1;
			}
			clamp(energy,0,5);
		}
		else
		{
			hitpoints -= (damage);
		}
		invincibilityTimer.Start();
	}
}

void Lancelot::Attack()
{
	attacking.SetLimit(0);
	attackCD.SetLimit(0);
	if(combo == "Straight")
	{
		attacking.SetLimit(240);
		attackCD.SetLimit(100);
		Empower(1);
	}
	else if(combo == "Uppercut")
	{
		attacking.SetLimit(240);
		attackCD.SetLimit(400);
		Empower(2);
	}
	else if(combo == "Chop")
	{
		attacking.SetLimit(320);
		attackCD.SetLimit(800);
		Empower(3);
	}
	else if(combo == "Spear")
	{
		attacking.SetLimit(240);
		attackCD.SetLimit(100);
		Empower(2);
	}
	else if(combo == "Sword")
	{
		attacking.SetLimit(240);
		attackCD.SetLimit(400);
		Empower(3);
	}
	else if(combo == "Axe")
	{
		attacking.SetLimit(320);
		attackCD.SetLimit(800);
		Empower(5);
	}	
	//Starts attack timer
	attacking.Start();
}

void Lancelot::Block()
{
	blocking = true;
	clamp(physicsComponent.velocity.x,-0.2f,0.2f);
}

void Lancelot::Stop()
{
	blocking = false;
}

void Lancelot::Combo(std::string c)
{
	combo = c;
}

bool Lancelot::Blocking()
{
	return blocking;
}

std::string Lancelot::WhichCombo()
{
	return combo;
}

void Lancelot::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	if(attacking.GetElapsed() == 1)
	{
		attacking.Reset();
		attackCD.Start();
	}
	attackCD.Update(dt);
	regenCD.Update(dt);
}
