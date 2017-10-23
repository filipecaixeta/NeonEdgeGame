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
	Lancelot(ItemsManager *itemManager,int x, int y);
	~Lancelot();
	void Damage(int damage);
	void Attack();
	void StartBlock();
	void StopBlock();
	void SetCombo(std::string setCombo);
	bool IsBlocking();
	std::string GetCombo();
	void UpdateTimers(float dt);

private:
	bool isBlocking;
	std::string combo;
	bool done = false;
};

#endif /* LANCELOT_H_ */
