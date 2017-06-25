#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "InputComponent.h"
#include "ItensManager.h"

class InputComponent;
class ItensManager;

class Player : public Character
{
public:
	Player(int x, int y);
	virtual ~Player();
	virtual int GetEnergy();
	virtual void Crouch();
	virtual void Stand();
	virtual bool Crouching();
	virtual void NotifyObjectCollision(GameObject* other);
	virtual void UpdateTimers(float dt);
	virtual void Update(TileMap* map,float dt);
	virtual bool Is(std::string type);

	InputComponent* inputComponent;
	ItensManager* itemManager;

protected:
	int energy;
	Timer regenCD;
	bool crouching;
};

#endif /* PLAYER_H_ */
