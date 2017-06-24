#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "InputComponent.h"

class InputComponent;

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
	virtual bool OutOfBounds(TileMap* map);
	virtual void UpdateTimers(float dt);
	virtual void Update(TileMap* map,float dt);
	virtual bool Is(std::string type);

	InputComponent* inputComponent;

protected:
	int energy;
	Timer regenCD;
	bool crouching;
};

#endif /* PLAYER_H_ */
