#include "Notfredo.h"
#include "Camera.h"
#include "StageState.h"
#include "Gallahad.h"
#include "Lancelot.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"
#include "IAComponent.h"
#include "Room.h"

typedef struct Node node;

struct Node{
  int x,y,z;
  float graph_distance;
  float physical_distance;
  float combined_distance;
  bool discovered;
  node* going_through;
  node* next;
};

Notfredo::Notfredo(int x, int y):
	Character(x,y),
	radius(),
	looking(1500),
	idle(1500)
{
	inputComponent = new IAComponent();
	graphicsComponent = new NotfredoGraphicsComponent("EnemyGallahad");
	name = "Notfredo";
	box.SetWH(graphicsComponent->GetSize());
	idle.Start();
}

Notfredo::~Notfredo()
{

}

void Notfredo::Attack()
{
	//Starts attack timer
	attacking.Start();
	//Generates attack object
	StageState::AddObject(new Melee("Melee.png", 2, 0, this, 500, 1));
}

void Notfredo::NotifyTileCollision(int tile, Face face)
{
	if(tile >= SOLID_TILE && (face == LEFT || face == RIGHT))
	{
		if(physicsComponent.velocity.y >= 0.6)
		{
			physicsComponent.velocity.y = -0.5;
		}
	}
}

void Notfredo::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
	if(looking.IsRunning())
	{	
		looking.Update(dt);
		if(!looking.IsRunning())
			idle.Start();
	}
	else if(idle.IsRunning())
	{
		idle.Update(dt);
		if(!idle.IsRunning())
			looking.Start();
	}
}

node* Notfredo::New(int x,int y,int z,float physical_distance)
{
    node* aux = new node;
    aux->x = x;
    aux->y = y;
    aux->z = z;
    aux->combined_distance = MAX_VALUE;
    aux->discovered = false;
    aux->going_through = nullptr;
    aux->graph_distance = 0;
    aux->next = nullptr;
    aux->physical_distance = physical_distance;

    return aux;
}


node* Notfredo::Pop(node* stack)
{
    node* aux = stack;

    stack = stack->next;

    return aux;
}

void Notfredo::Push(int x,int y,int z,node* stack,float physical_distance)
{
    node* aux = stack;

    while(aux->next != nullptr){
        aux = aux->next;
    }

    aux->next = New(x,y,z,physical_distance);
}

void Notfredo::CopyNode(node* source,node* target){

    target->combined_distance = source->combined_distance;
    target->discovered = source->discovered;
    target->going_through = source->going_through;
    target->graph_distance = source->graph_distance;
    target->next = source->next;
    target->physical_distance = source->physical_distance;
    target->x = source->x;
    target->y = source->y;
    target->z = source->z;

}

void Notfredo::QuickSort(node* tileStack, int start, int end)
{

    int pivot, i, j, half;

    node* aux;

    i = start;
    j = end;


    half = (int) ((i + j) / 2);
    pivot = tileStack[half].combined_distance;

    do
    {
      while (tileStack[i].combined_distance < pivot) i = i + 1;
      while (tileStack[j].combined_distance > pivot) j = j - 1;

      if(i <= j)
      {
         CopyNode(&tileStack[i],aux);

         CopyNode(&tileStack[j],&tileStack[i]);

         CopyNode(aux,&tileStack[j]);

         i = i + 1;
         j = j - 1;
      }
    }while(j > i);

    if(start < j) QuickSort(tileStack, start, j);
    if(i < end) QuickSort(tileStack, i, end);
}

void Notfredo::PathFind()
{

     int mapWidth = StageState::GetCurrentRoom()->GetMap()->GetWidth();

     int mapHeight =  StageState::GetCurrentRoom()->GetMap()->GetHeight();

     int x,y,tileStackSize = 0;

    node tileStack;
    node* aux;

    //for all tiles in current tilemap
        //push new node with tile coordinates,
        //combined distance of MAX_VALUE(to be determined),
        //and physical_distance as the distance between the
        //tile and the target(player)

    for(x = 0;x < mapWidth; x++)
    {
        for(y = 0;y < mapHeight; y++)
        {
           Push(x,y,0,&tileStack,StageState::GetCurrentRoom()->GetMap()->GetTileBox(x,y).GetCenter().distance(StageState::GetPlayer()->box.GetCenter()));
        }
    }

    aux = &tileStack;

    while(aux->next != nullptr)
    {
        aux = aux->next;
        tileStackSize ++;
    }

    QuickSort(&tileStack,0,tileStackSize-1);


    //starting with start tile(fredo's tile)
    //while top of stack is not the target's tile
        //pop top of stack. That is the current node

        //for all nodes adjacent to current node
            //if node is undiscovered(discovered == false)
                //tile's graph distance is current node's graph distance plus distance
                //between current node and adjacent node

                //tile's combined distance is it's graph distance plus its physical distance

            //else if tile's graph distance is lower than current tile's graph distance plus
            //distance between current node and adjacent node
                //replace graph distance in tile and update combined distance
                //else, do nothing
        //order stack by total distance

    //return sequence of tiles to target

}

void Notfredo::UpdateAI(float dt)
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

			if(!Attacking())
			{
				Attack();
			}
		}
		else if(looking.IsRunning() && looking.GetElapsed() == 0)
		{
			if(facing == LEFT)
				physicsComponent.velocity.x = -0.2;
			else
				physicsComponent.velocity.x = 0.2;
		}
		else
		{
			if(idle.IsRunning() && idle.GetElapsed() == 0)
			{
				physicsComponent.velocity.x = 0;
				if(facing == LEFT)
				{
					facing = RIGHT;
				}
				else
				{
					facing = LEFT;
				}
			}
		}
	}
}

void Notfredo::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	UpdateAI(dt);
	inputComponent->Update(this,dt);
	physicsComponent.Update(this,world,dt);
	graphicsComponent->Update(this,dt);
}

bool Notfredo::Is(std::string type)
{
	return (type=="Enemy");
}
