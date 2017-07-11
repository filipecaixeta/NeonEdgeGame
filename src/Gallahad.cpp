#include <iostream>

#include "Gallahad.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include "Cutscene.h"
#include "SoundComponent.h"

Gallahad::Gallahad(ItensManager* itemManager, int x, int y, GameObject* d):
	Player(itemManager,x,y),
	hiding(500),
	shooting(false)
{
	name = "Gallahad";
	inputComponent = new GallahadInputComponent();
	graphicsComponent = new GallahadGraphicsComponent("Gallahad");
	soundComponent = new SoundComponent(name);
	box.SetWH(graphicsComponent->GetSize());
	drone = d;
	active = true;
	dieTimer = Timer(800);
}

Gallahad::~Gallahad()
{
	Game::GetInstance().GetCurrentState()->quitRequested = true;
	Game::GetInstance().AddState(new Cutscene(7, false));
}

void Gallahad::Attack()
{
	//Starts attack timer
	attackCD.Start();
	soundComponent->Attack();
	//Generates attack object
	StageState::AddObject(new Projectile(this, Vec2(0.8, 0), 1200, 1, false));
}

void Gallahad::Hide()
{
	if(skills[0])
		hiding.SetLimit(2000);
	else if(skills[1])
		hiding.SetLimit(1500);
	else if(skills[2])
		hiding.SetLimit(1000);
	else
		hiding.SetLimit(500);
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
	/*Rect checkStateTrasition;
	if(StageState::stage == "cidadeGalahad" && !done){	
		checkStateTrasition.x = 18565;
		checkStateTrasition.y = 769;
		checkStateTrasition.w = 116;
		checkStateTrasition.h = 181;

		if(box.OverlapsWith(checkStateTrasition) == true){
			Game::GetInstance().GetCurrentState()->quitRequested = true;
			Game::GetInstance().AddState(new Cutscene(4, false));
			done = true;
		}
	}*/
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

	std::cerr << Is("Gallahad") <<std::endl;
}
