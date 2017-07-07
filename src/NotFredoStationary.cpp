#include "NotFredoStationary.h"
#include "Camera.h"
#include "StageState.h"
#include "Gallahad.h"
#include "Lancelot.h"
#include "Vec2.h"
#include "Rect.h"
#include "Player.h"
#include "Projectile.h"
#include "Room.h"

NotFredoStationary::NotFredoStationary(int x, int y):
    Character(x,y),
    radius(),
    idle(1500)
{
    graphicsComponent = new NotFredoStationaryGraphicsComponent("EnemyGallahad");

    name = "Notfredo";
    box.SetWH(graphicsComponent->GetSize());
    idle.Start();
}

NotFredoStationary::~NotFredoStationary()
{

}

void NotFredoStationary::Attack()
{
    //Starts attack timer
    attacking.Start();
}

void NotFredoStationary::NotifyTileCollision(int tile, GameObject::Face face)
{
    if(tile >= SOLID_TILE && (face == LEFT || face == RIGHT))
    {
        if(physicsComponent.velocity.y >= 0.6)
        {
            physicsComponent.velocity.y = -0.5;
        }
    }
}

void NotFredoStationary::NotifyObjectCollision(GameObject* other)
{
    if(other->Is("Lancelot") || other->Is("Gallahad"))
    {
        Character* c = (Character*) other;
        if(c->Attacking())
            Damage(1);
    }
    if(other->Is("Projectile"))
    {
        Projectile* p = (Projectile*) other;
        if(!p->GetOwner()->Is("NotFredoStationary"))
        {
            Damage(1);
        }
    }
}


void NotFredoStationary::Update(TileMap* world, float dt)
{
    idle.Update(dt);
    UpdateAI(dt);
    physicsComponent.Update(this,world,dt);
    if(OutOfBounds(world))
        SetPosition(Vec2(startingX,startingY));
    graphicsComponent->Update(this,dt);
}

void NotFredoStationary::UpdateAI(float dt)
{
    radius = Rect(box.x-200, box.y-200, box.w+400, box.h+400);
    if(StageState::GetPlayer())
    {
        Rect player = StageState::GetPlayer()->box;
        bool visible = true;
        if(StageState::GetPlayer()->Is("Gallahad"))
        {
            Gallahad* p = (Gallahad*) StageState::GetPlayer();
            if(p->Hiding())
            {
                visible = false;
            }
        }
        if(player.OverlapsWith(radius) && visible)
        {
            if(player.x < box.x )
            {
                physicsComponent.velocity.x -= 0.003*dt;
                if(box.x - physicsComponent.velocity.x*dt < player.x)
                {
                    box.x = player.x;
                    physicsComponent.velocity.x = 0;
                }
                facing = LEFT;
            }
            else
            {
                physicsComponent.velocity.x += 0.003*dt;
                if(box.x + physicsComponent.velocity.x*dt > player.x)
                {
                    box.x = player.x;
                    physicsComponent.velocity.x = 0;
                }
                facing = RIGHT;
            }
            clamp(physicsComponent.velocity.x,-0.4f,0.4f);

            if(!Attacking() && !Cooling())
            {
                Attack();
            }
        }


    }
}

bool NotFredoStationary::Is(std::string type)
{
    return (type=="Enemy");
}
