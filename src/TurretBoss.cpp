#include "TurretBoss.h"

#include "StageState.h"

TurretBoss::TurretBoss(int x, int y):
	Character(x,y),
	spawn(3000),
	shoot(3000),
	idle(3000)
{
	name = "TurretBoss";
	box.x = x;
	box.y = y;
	box.w = 0;
	box.h = 0;
	state = tIDLE;
	triggered = false;
	physicsComponent.SetKinetic(true);
	physicsComponent.velocity.y = 0;
}

TurretBoss::~TurretBoss()
{

}

void TurretBoss::AddPiece(TurretPiece* piece)
{
	pieces.emplace_back(piece);
}

void TurretBoss::NotifyObjectCollision(GameObject* other)
{

}

void TurretBoss::UpdateAI(float dt)
{
	radius = Rect(box.x-800, box.y-800, box.w+1000, box.h+1000);

	if(StageState::GetPlayer()){
		Rect player = StageState::GetPlayer()->box;
		if(player.OverlapsWith(radius)){
			triggered = true;
		}

		if(triggered){
			if(state == tIDLE){
				if(!idle.IsRunning()){
					shoot.Start();
					state = tSHOOTING;
				}
			}
			if(state == tSHOOTING){

			}
			if(state == tSPAWNING){

			}
		}
	}
}

void TurretBoss::UpdateTimers(float dt)
{
	idle.Update(dt);
	spawn.Update(dt);
	shoot.Update(dt);
}

void TurretBoss::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	//UpdateAI(dt);
	physicsComponent.Update(this,world,dt);
	if(OutOfBounds(world))
        SetPosition(Vec2(startingX,startingY));
}

void TurretBoss::Render()
{

}