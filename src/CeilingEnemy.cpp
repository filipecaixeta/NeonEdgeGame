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

void CeilingEnemy::NotifyTileCollision(int tile, Face face){
    if(tile >= 0){
        if(face == UPPER && state == REARMING){
            std::cout << "waiting";
            state = WAITING;
        }
        if(face == BOTTOM && state == ATTACKING){
            std::cout << "rearming";
            state = REARMING;
        }
    }
}

void CeilingEnemy::UpdateAI(float dt)
{
    if(state == WAITING && StageState::GetPlayer()->box.GetCenter().x > this->box.x - 20 && StageState::GetPlayer()->box.GetCenter().x < this->box.x + box.w + 20 )
    {
        //std::cout << "entrou aqui0";
        state = ATTACKING;
    }
    else if(state == ATTACKING)
    {
        //std::cout << "entrou aqui1";
        physicsComponent.velocity.y+=0.006*dt;
        clamp(physicsComponent.velocity.y,-0.4f,0.4f);
    }
    else if(state == REARMING)
    {
        physicsComponent.velocity.y-=0.012*dt;
        clamp(physicsComponent.velocity.y,-0.2f,0.2f);
    }
}
