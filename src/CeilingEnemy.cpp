#include "CeilingEnemy.h"
#include "StageState.h"
#include "GraphicsComponent.h"

CeilingEnemy::CeilingEnemy(int x,int y):
    Character(x,y),
    timer()
{
    graphicsComponent = new CeilingEnemyGraphicsComponent("DroneInimigoSprite");
    name = "SpiderMan";
    box.SetWH(graphicsComponent->GetSize());
    physicsComponent.SetKinetic(true);

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
    if(state == WAITING && timer.GetElapsed() > 3000 && StageState::GetPlayer()->box.x == this->box.x)
    {
        state = ATTACKING;
    }
    else if(state == ATTACKING && this->footing != GROUNDED)
    {
        physicsComponent.velocity.y+=20;
    }
    else if(state == ATTACKING && this->footing == GROUNDED)
    {
        state = REARMING;
        physicsComponent.velocity.y-=10;
        timer.Reset();
    }
    else if(state == REARMING && timer.GetElapsed() <= 3000)
    {
        physicsComponent.velocity.y-=10;
    }
    else if(state == REARMING && timer.GetElapsed() > 3000)
    {
        state = WAITING;
        timer.Reset();
    }
}

