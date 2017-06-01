#ifndef LANCELOT_H_
#define LANCELOT_H_

#include "Timer.h"
#include "LancelotInputComponent.h"
#include "LancelotGraphicsComponent.h"
#include "TileMap.h"
#include "Character.h"

class Lancelot : public Character
{
public:
	Lancelot(int x, int y);
	~Lancelot();
	void Attack();
	void Block();
	bool Blocking();
	void UpdateTimers(float dt);
private:
	Timer blocking;
};

#endif /* LANCELOT_H_ */
