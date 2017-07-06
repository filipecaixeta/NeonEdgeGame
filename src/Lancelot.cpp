#include "Lancelot.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include "Cutscene.h"

Lancelot::Lancelot(ItensManager* itemManager, int x, int y):
	Player(itemManager,x,y),
	blocking(1000)
{
	name = "Lancelot";
	inputComponent = new LancelotInputComponent();
	graphicsComponent = new LancelotGraphicsComponent("Lancelot");
	box.SetWH(graphicsComponent->GetSize());
	attackCD.SetLimit(0);
}

Lancelot::~Lancelot()
{

}

void Lancelot::Attack()
{
	if(combo == "Straight")
	{
		attacking.SetLimit(240);
		attackCD.SetLimit(100);
		Empower(1);
	}
	else if(combo == "Uppercut")
	{
		attacking.SetLimit(240);
		attackCD.SetLimit(500);
		Empower(2);
	}
	else if(combo == "Chop")
	{
		attacking.SetLimit(320);
		attackCD.SetLimit(800);
		Empower(3);
	}
	//Starts attack timer
	attacking.Start();
}

void Lancelot::Block()
{
	blocking.Start();
	energy -= 1;
	clamp(energy,0,5);
}

void Lancelot::Combo(std::string c)
{
	combo = c;
}

bool Lancelot::Blocking()
{
	return blocking.IsRunning();
}

std::string Lancelot::WhichCombo()
{
	return combo;
}

void Lancelot::UpdateTimers(float dt)
{
	Rect checkStateTrasition;
	if(StageState::stage == "cidadeLancelot"){
		checkStateTrasition.x = 18504;
		checkStateTrasition.y = 2369;
		checkStateTrasition.w = 112;
		checkStateTrasition.h = 180;

		if(box.OverlapsWith(checkStateTrasition) == true){
			Game::GetInstance().GetCurrentState()->quitRequested = true;
			Game::GetInstance().AddState(new Cutscene(2, false));

		}
	}

	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	if(attacking.GetElapsed() == 1)
	{
		attacking.Reset();
		attackCD.Start();
	}
	attackCD.Update(dt);
	regenCD.Update(dt);
	blocking.Update(dt);
}
