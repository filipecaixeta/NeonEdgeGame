#include "Drone.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Drone::Drone(int x, int y):
	Player(x,y)
{
	inputComponent = new DroneInputComponent();
	graphicsComponent = new DroneGraphicsComponent("Drone");
	name = "Drone";
	box.SetWH(graphicsComponent->GetSize());
}

Drone::~Drone()
{

}

void Drone::UpdateTimers(float dt)
{

}
