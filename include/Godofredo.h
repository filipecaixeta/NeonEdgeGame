#ifndef GODOFREDO_H_
#define GODOFREDO_H_

#include "Attack.h"

class Godofredo : public GameObject{
private:
	Sprite healthBar;
	Sprite stealthBar;

	bool jumping = false;
	int jumpingPower = 0;

	int wallJumping = 0;
	int lastWallJumping = 0;

	bool hidden = false;
	Timer hiddenT;

	void RunState(StateT s, float dt);
	void AttackState(float dt);
	void JumpState(float dt);
	void InvisibleState(float dt);

public:
	static Godofredo* player;

	Godofredo(int x, int y);
	~Godofredo();
	void Update(float dt);
	void UpdateTimers(float dt);
	void UpdateCommands(float dt);
	void UpdatePosition(float dt);
	void UpdateSprite(std::string sprite);
	void Render();
	void Damage(int damage);
	bool NotifyTileCollision(Face face);
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	bool IsHidden();
	bool IsDead();
	Godofredo* get();
};

#endif /* GODOFREDO_H_ */
