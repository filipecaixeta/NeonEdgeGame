#ifndef GODOFREDO_H_
#define GODOFREDO_H_

#include "Attack.h"
#include <LoadingBar.h>
#include <InputComponent.h>
#include <GraphicsComponent.h>
#include <PhysicsComponent.h>
#include <SaveComponent.h>

class Godofredo : public GameObject{
public:
	LoadingBar healthBar;
	Sprite stealthBar;

	bool hidden = false;
	Timer hiddenT;

	void AttackState(float dt);
	void InvisibleState(float dt);

public:
	static Godofredo* player;

	Godofredo(int x, int y);
	~Godofredo();
	void Update(float dt);
	void UpdateTimers(float dt);
	void UpdateCommands(float dt);
	void Render();
	void Damage(int damage);
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	bool IsHidden();
	bool IsDead();
	Godofredo* get();

	InputComponent inputComponent;
	GraphicsComponent graphicsComponent;
	PhysicsComponent physicsComponent;
	SaveComponent &saveComponent;
};

#endif /* GODOFREDO_H_ */
