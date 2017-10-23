#ifndef PLAYER_H
#define PLAYER_H

#define MAX_HITPOINTS 10

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "InputComponent.h"
#include "ItensManager.h"
#include "SoundComponent.h"

class InputComponent;
class ItensManager;

class Player : public Character {
public:
    Player(ItensManager* itemManager, int x, int y);
    virtual ~Player();
    virtual bool IsPlayer();
    virtual int GetEnergy();
    virtual void Crouch();
    virtual void Stand();
    virtual bool IsCrouching();
    virtual void EvalItem(std::string itemName);
    virtual void NotifyObjectCollision(GameObject* other);
    virtual void UpdateTimers(float dt);
    virtual void Update(TileMap* map,float dt);

    enum {SkillBlocking3 = 0, SkillBlocking2 = 0, SkillBlocking1 = 0, Skill = 0, SkillWeapon_1 = 0, SkillWeapon_2 = 0,
        SkillWeapon_3 = 0};  // The skills options of the player.

    InputComponent* inputComponent;
    ItensManager* itemManager;

    bool skills[7];
    int skillPoints;

protected:
	int const INITIAL_ENERGY_VALUE = 0;
    int energy = INITIAL_ENERGY_VALUE;
    Timer regenCD = 0;
    bool isCrouching = false;
    bool isStading = false;
};

#endif /* PLAYER_H_ */
