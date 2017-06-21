#include "Gallahad.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Projectile.h"

Gallahad::Gallahad(int x, int y):
	Player(x,y),
	hiding(1500)
{
	inputComponent = new GallahadInputComponent();
	graphicsComponent = new GallahadGraphicsComponent("Gallahad");
	name = "Gallahad";
	box.SetWH(graphicsComponent->GetSize());
}

Gallahad::~Gallahad()
{

}

void Gallahad::Attack()
{
	//Starts attack timer
	attackCD.Start();
	//Generates attack object
	StageState::AddObject(new Projectile("Melee.png", 2, 0, this, Vec2(0.6, 0), 800, 1, true));
}

bool Gallahad::Hiding()
{
	return hiding.IsRunning();
}

void Gallahad::Hide()
{
	hiding.Start();
	energy -= 1;
	clamp(energy,0,5);
}

void Gallahad::UpdateTimers(float dt)
{
	Player::UpdateTimers(dt);
	hiding.Update(dt);
}
