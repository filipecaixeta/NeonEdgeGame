#include "Door.h"
#include "Camera.h"
#include "StageState.h"

Door::Door(int x, int y):
	Interactive(x,y,"Door")
{
	name = "Door";
	open = false;
}

Door::~Door()
{

}

void Door::Trigger()
{
	if(Active())
		Off();
	else
		On();
}

void Door::Update(TileMap* map, float dt)
{
	open = false;
	if(Active())
	{
		Rect radius = Rect(box.x-100, box.y-100, box.w+200, box.h+200);
		GameObject* player = StageState::GetPlayer();
		if(radius.OverlapsWith(player->box))
		{
			open = true;
		}
	}
	graphicsComponent->Update(this,dt);
}

void Door::Render()
{
	if(!open || !Active())
	{
		graphicsComponent->Render(GetPosition()-Camera::GetInstance().pos);
	}
}

/*void Door::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Player"))
	{
		if(locked)
		{
			Player* p = (Player*) other;
			std::unordered_map<std::string,ItensManager::itemType>::const_iterator got = p->itemManager->itens.find("Arco");
			if(got != p->itemManager->itens.end())
			{
				sp = Sprite();
				hard = false;
				dead = false;
				p->itemManager->itens.erase("Arco");
			}
		}
		else
		{
			hard = false;
			sp = Sprite();
			dead = true;
		}
	}
}*/
