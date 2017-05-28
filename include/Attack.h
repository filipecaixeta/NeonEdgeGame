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

	~Attack();
	bool IsDead();
	void UpdateTimers(float dt);
	void Update(TileMap* world, float dt)=0;
	void Render() = 0;
};

#endif /* ATTACK_H_ */
