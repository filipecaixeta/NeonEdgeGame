#ifndef LANCELOT_H_
#define LANCELOT_H_

#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "LancelotInputComponent.h"
#include "LancelotGraphicsComponent.h"


class Lancelot : public Player
{
public:
	Lancelot(int x, int y);
	~Lancelot();
	void Attack();
	void Block();
	void Charge();
	bool Blocking();
	int Charged();
	void UpdateTimers(float dt);

private:
	Timer blocking;
	int charges;
};

#endif /* LANCELOT_H_ */
