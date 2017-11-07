#ifndef LANCELOT_H_
#define LANCELOT_H_

#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "LancelotInputComponent.h"
#include "LancelotGraphicsComponent.h"

#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

class Lancelot : public Player
{
private:
	void BlockingAttack();
	bool isBlocking;
	std::string combo;
	bool done = false;
	void UpdateTimers(float dt);
	void Damage(int damage);

public:
	Lancelot(ItemsManager *itemManager,int x, int y);
	~Lancelot();
	void Attack();
	void StartBlock();
	void StopBlock();
	void SetCombo(std::string setCombo);
	bool IsBlocking();
	std::string GetCombo();
};

#endif /* LANCELOT_H_ */
