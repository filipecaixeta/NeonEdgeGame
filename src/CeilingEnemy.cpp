#include "CeilingEnemy.h"
#include "StageState.h"
#include "GraphicsComponent.h"
#include "Gallahad.h"

CeilingEnemy::CeilingEnemy(int x,int y):
    Character(x,y)
{
    name = "SpiderMan";
    graphicsComponent = new CeilingEnemyGraphicsComponent("DroneInimigoSprite");
    box.SetWH(graphicsComponent->GetSize());
    physicsComponent.SetKinetic(true);
    state = WAITING;
    physicsComponent.velocity.y = 0;
}

bool CeilingEnemy::Attacking()
{
    return true;
}

void CeilingEnemy::NotifyTileCollision(int tile, Face face)
{
    if(tile >= 0)
    {
        if(face == UPPER && state == REARMING)
        {
            state = WAITING;
        }
        if(face == BOTTOM && state == ATTACKING)
        {
            state = REARMING;
        }
    }
}

void CeilingEnemy::UpdateAI(float dt)
{
    if(StageState::GetPlayer())
    {
        if(!stunned.IsRunning())
        {
            bool visible = true;
            if(StageState::GetPlayer()->Is("Gallahad"))
            {
                Gallahad* g = (Gallahad*) StageState::GetPlayer();
                if(g->Hiding())
                {
                    visible = false;
                }
            }
            if(visible)
            {
                if(state == WAITING && StageState::GetPlayer()->box.GetCenter().x > this->box.x - 25 &&
                   StageState::GetPlayer()->box.GetCenter().x < this->box.x + box.w + 25)
                {
                    state = ATTACKING;
                }
                else if(state == ATTACKING)
                {
                    physicsComponent.velocity.y += 0.006*dt;
                    clamp(physicsComponent.velocity.y,-0.4f,0.4f);
                }
                else if(state == REARMING)
                {
                    physicsComponent.velocity.y -= 0.012*dt;
                    clamp(physicsComponent.velocity.y,-0.2f,0.2f);
                }
            }
        }
        else
        {
            physicsComponent.velocity.y = 0;
        }
    }
}

void CeilingEnemy::Update(TileMap* world, float dt)
{
    UpdateTimers(dt);
    UpdateAI(dt);
    physicsComponent.Update(this,world,dt);
    if(OutOfBounds(world))
        SetPosition(Vec2(startingX,startingY));
    graphicsComponent->Update(this,dt);
}
