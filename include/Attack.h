#ifndef ATTACK_H_
#define ATTACK_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "TileMap.h"

class Attack : public GameObject
{
public:
	Sprite sp = Sprite();
	Timer lifetime = Timer();
	int power = 0;
	GameObject* owner = nullptr;

	Attack();
	virtual ~Attack();
	virtual bool IsDead();
	virtual void UpdateTimers(float dt);
	virtual void Update(TileMap* world, float dt) = 0;
};

#endif /* ATTACK_H_ */
