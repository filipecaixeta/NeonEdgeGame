#include <iostream>

#include "CeilingEnemy.h"
#include "StageState.h"
#include "GraphicsComponent.h"

CeilingEnemy::CeilingEnemy(int x,int y):
    Character(x,y),
    timer(4000)
{
    graphicsComponent = new CeilingEnemyGraphicsComponent("DroneInimigoSprite");
    name = "SpiderMan";
    box.SetWH(graphicsComponent->GetSize());
    physicsComponent.SetKinetic(true);
    state = WAITING;
    physicsComponent.velocity.y = 0;

}

void CeilingEnemy::Update(TileMap* world, float dt)
{
    timer.Update(dt);
    UpdateAI(dt);
    physicsComponent.Update(this,world,dt);
    if(OutOfBounds(world))
        SetPosition(Vec2(startingX,startingY));
    graphicsComponent->Update(this,dt);
    if(this->box.OverlapsWith(StageState::GetPlayer()->box))
    {
        Player* p = (Player*) StageState::GetPlayer();
        p->Damage(1);
    }

}

void CeilingEnemy::UpdateAI(float dt)
{
    if(state == WAITING && !timer.IsRunning() && StageState::GetPlayer()->box.GetCenter().x > this->box.x - 20 && StageState::GetPlayer()->box.GetCenter().x < this->box.x + 20 )
    {
        //std::cout << "entrou aqui0";
        state = ATTACKING;
    }
    else if(state == ATTACKING && this->footing != GROUNDED)
    {
        //std::cout << "entrou aqui1";
        physicsComponent.velocity.y+=0.006*dt;
        clamp(physicsComponent.velocity.x,-0.2f,0.2f);
    }
    else if(state == ATTACKING && this->footing == GROUNDED)
    {
        //std::cout << "entrou aqui2";
        state = REARMING;
        physicsComponent.velocity.y-=0.012*dt;
        clamp(physicsComponent.velocity.x,-0.2f,0.2f);
        timer.Reset();
    }
    else if(state == REARMING && timer.GetTime() <= 3000 && timer.IsRunning())
    {
        //std::cout << "entrou aqui3";
        physicsComponent.velocity.y-=0.012*dt;
        clamp(physicsComponent.velocity.x,-0.2f,0.2f);
    }
    else if(state == REARMING && (timer.GetTime() > 3000 || !timer.IsRunning()))
    {
        //std::cout << "entrou aqui4";
        state = WAITING;
        timer.Reset();
        physicsComponent.velocity.y = 0;
    }
}

