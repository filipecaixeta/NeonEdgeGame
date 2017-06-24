#include "Item.h"
#include "Camera.h"

Item::Item(int id, int x, int y):
	sp(new Sprite("items.png",12)),
	dead(false)
{
	sp->SetFrame(id-100);
	box.SetXY(Vec2(x,y));
	box.SetWH(sp->GetSize());
	name = "Item";
}

void Item::Eval(Player* player)
{
//	player->itemManager->AddItem(*this);
	std::cerr << "Eval Item" <<std::endl;
}

void Item::SetActive(bool b)
{

}

Item::Item(const Item &obj)
{
	sp = new Sprite();
	dead = obj.dead;
	name = obj.name;
}

bool Item::GetActive()
{
	return !IsDead();
}

bool Item::Is(std::string type)
{
	return type=="Item";
}

bool Item::IsDead()
{
	return dead;
}

void Item::NotifyObjectCollision(GameObject* other)
{
	dead = true;
}

void Item::Update(TileMap* map, float dt)
{

}

void Item::Render()
{
	sp->Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
