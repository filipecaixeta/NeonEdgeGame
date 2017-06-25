#include <iostream>

#include "Gallahad.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Projectile.h"

Gallahad::Gallahad(int x, int y):
	Player(x,y),
	hiding(1500),
	shooting(false)
{
	inputComponent = new GallahadInputComponent();
	graphicsComponent = new GallahadGraphicsComponent("Gallahad");
	name = "Gallahad";
	box.SetWH(graphicsComponent->GetSize());
	std::cout << x << " " << y << "\n";
}

Gallahad::~Gallahad()
{

}

void Gallahad::Attack()
{
	std::cout << box.x << " " << box.y << "\n";
	//Starts attack timer
	attackCD.Start();
	//Generates attack object
	StageState::AddObject(new Projectile("GallahadProjectile.png", 4, 80, this, Vec2(0.8, 0), 800, 1, false));
}

void Gallahad::Hide()
{
	hiding.Start();
	energy -= 1;
	clamp(energy,0,5);
}

void Gallahad::Shoot()
{
	shooting = true;
}

void Gallahad::Hold()
{
	shooting = false;
}

bool Gallahad::Hiding()
{
	return hiding.IsRunning();
}

bool Gallahad::Shooting()
{
	return shooting;
}

void Gallahad::UpdateTimers(float dt)
{
	std::cout << box.x << " " << box.y << "\n";
	Player::UpdateTimers(dt);
	hiding.Update(dt);
}
