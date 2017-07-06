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
	state = TIDLE;
	triggered = false;
}

TurretBoss::~TurretBoss(){

}

void TurretBoss::UpdateAI(float dt){
	radius = Rect(box.x-800, box.y-800, box.w+1000, box.h+1000);

	if(StageState::GetPlayer()){
		Rect player = StageState::GetPlayer()->box;
		if(player.OverlapsWith(radius)){
			triggered = true;
		}

		if(triggered){
			if(state == TIDLE){
				if(!idle.IsRunning()){
					shoot.Start();
					state = SHOOTING;
				}
			}
			if(state == SHOOTING){

			}
			if(state == SPAWNING){

			}
		}
	}
}

void TurretBoss::UpdateTimers(float dt){
	idle.Update(dt);
	spawn.Update(dt);
	shoot.Update(dt);
}

void TurretBoss::Update(TileMap* world, float dt){
	UpdateTimers(dt);
	UpdateAI(dt);
	physicsComponent.Update(this,world,dt);
	if(OutOfBounds(world))
        SetPosition(Vec2(startingX,startingY));
    for(int i = 0; i < pieces.size(); i++){
    	pieces.at(i)->physicsComponent.Update(pieces.at(i),world,dt);
    	pieces.at(i)->graphicsComponent->Update(this, dt);
    }
}

void TurretBoss::AddPiece(TurretPiece* piece){
	pieces.emplace_back(piece);
}