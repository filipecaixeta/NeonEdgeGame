#include "GameObject.h"

GameObject::~GameObject() {

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
