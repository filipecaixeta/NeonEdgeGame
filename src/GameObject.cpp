#include "GameObject.h"

GameObject::~GameObject() {

}

void GameObject::UpdateTimers(float dt)
{

}

void GameObject::UpdatePosition(float dt)
{

}

bool GameObject::NotifyTileCollision(GameObject::Face face)
{

}

void GameObject::NotifyCollision(GameObject* other) {

}

bool GameObject::Is(std::string type) {
	return true;
}

bool GameObject::IsDead() {
	return true;
}

GameObject* GameObject::get() {
	return this;
}

Vec2 GameObject::GetPosition()
{
	return box.GetXY();
}

void GameObject::SetPosition(Vec2 position)
{
	box.SetXY(position);
}
