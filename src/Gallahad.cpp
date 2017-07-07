#include <iostream>

#include "Gallahad.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include "SoundComponent.h"

Gallahad::Gallahad(ItensManager* itemManager, int x, int y, GameObject* d):
	Player(itemManager,x,y),
	hiding(1500),
	shooting(false)
{
	name = "Gallahad";
	inputComponent = new GallahadInputComponent();
	graphicsComponent = new GallahadGraphicsComponent("Gallahad");
	soundComponent = new SoundComponent(name);
	box.SetWH(graphicsComponent->GetSize());
	drone = d;//new Drone(itemManager, x, y);
	//StageState::AddObject(drone);
	active = true;
}

Gallahad::~Gallahad()
{

}

void Gallahad::Attack()
{
	//Starts attack timer
	attackCD.Start();
	//Generates attack object
	StageState::AddObject(new Projectile(this, Vec2(0.8, 0), 800, 1, false));
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

void Gallahad::Activate(bool on)
{
	active = on;
}

bool Gallahad::Active()
{
	return active;
}

Drone* Gallahad::GetDrone()
{
	Drone* d = (Drone*) drone;
	return d;
}

void Gallahad::UpdateTimers(float dt)
{
	Player::UpdateTimers(dt);
	hiding.Update(dt);
}

void Gallahad::Update(TileMap* map, float dt)
{
	UpdateTimers(dt);
	inputComponent->Update(this,dt);
	physicsComponent.Update(this,map,dt);
	if(OutOfBounds(map))
		SetPosition(Vec2(startingX,startingY));
	graphicsComponent->Update(this,dt);
}
