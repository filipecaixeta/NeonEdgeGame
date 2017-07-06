#include "Door.h"
#include "Animation.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"
#include <unordered_map>
#include <string>

Door::Door(int x, int y, std::string sprite, bool locked)
{
	name = "Door";
	sp = Sprite(sprite);
	Vec2 size = sp.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
	hard = true;
	Door::locked = locked;
}

Door::~Door()
{

}

bool Door::IsDead()
{
	return dead;
}

void Door::NotifyObjectCollision(GameObject* other)
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
}

void Door::Update(TileMap* map, float dt)
{

}

void Door::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
