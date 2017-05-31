#include "GameObject.h"

GameObject::~GameObject()
{

}

bool GameObject::Is(std::string type)
{
	return (type == name);
}

bool GameObject::IsDead()
{
	return false;
}

Vec2 GameObject::GetPosition()
{
	return Vec2(box.x, box.y);
}

void GameObject::SetPosition(Vec2 pos)
{
	box.x = pos.x;
	box.y = pos.y;
}

void GameObject::NotifyTileCollision(int tile, Face face)
{

}

void GameObject::NotifyObjectCollision(GameObject* other)
{

}

bool GameObject::GetColisionData(SDL_Surface** surface_, SDL_Rect& clipRect_, Vec2& pos_, bool& mirror)
{
	return false;
}

void GameObject::Render()
{

}
