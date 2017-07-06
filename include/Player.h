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
	Player(ItensManager* itemManager,int x, int y);
	virtual ~Player();
	virtual int GetEnergy();
	virtual void Crouch();
	virtual void Stand();
	virtual bool Crouching();
	virtual void EvalItem(std::string itemName);
	virtual void NotifyObjectCollision(GameObject* other);
	virtual void UpdateTimers(float dt);
	virtual void Update(TileMap* map,float dt);
	virtual bool Is(std::string type);

	InputComponent* inputComponent;
	ItensManager* itemManager;
	enum {SkillBlocking3=0,SkillBlocking2,SkillBlocking1,Skill,SkillWeapon1,SkillWeapon2,SkillWeapon3};
	enum {SkillDrone3=0,SkillDrone2,SkillDrone1,SkillStealth1=4,SkillStealth2,SkillStealth3};
	bool skills[7];
	int skillPoints;

protected:
	int energy;
	Timer regenCD;
	bool crouching;
};

#endif /* PLAYER_H_ */
