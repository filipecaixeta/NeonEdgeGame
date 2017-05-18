#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"
#include "Sprite.h"
#include "Sound.h"
#include "Timer.h"

class GameObject {
public:
	enum Face : short int {UPPER, BOTTOM, LEFT, RIGHT, SPECIAL};
	enum StateT : short int {NONE, MOVE_LEFT, MOVE_RIGHT};
	enum Status : short int {NORMAL, STUNNED};

	std::unordered_map<std::string, Sprite*> sprites;
	Sprite* sp = new Sprite();
	Rect box = Rect();
	Face facing;

	std::string objName;

	int hitpoints = 10;
	int power = 0;
	int defense = 0;
	Vec2 speed = Vec2();

	int wallJumping = 0;
	int lastWallJumping = 0;

	Timer invincibilityT = Timer();

	bool attacking = false;
	Timer attackT = Timer();

	bool jumping = false;
	int jumpingPower = 0;

	Status status = NORMAL;
	Timer statusTimer = Timer(2000);

	virtual ~GameObject() = 0;
	virtual void Update(float dt) = 0;
	virtual void UpdateTimers(float dt);
	virtual void UpdatePosition(float dt);
	virtual void Render() = 0;
	virtual bool NotifyTileCollision(Face face);
	virtual void NotifyCollision(GameObject* other);
	virtual Vec2 GetPosition();
	virtual void SetPosition(Vec2 position);
	virtual bool Is(std::string type) = 0;
	virtual bool IsDead() = 0;
	virtual GameObject* get() = 0;
};

#endif /* GAMEOBJECT_H_ */
