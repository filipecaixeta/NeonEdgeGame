#ifndef PLAYER_H
#define PLAYER_H

#define MAX_HITPOINTS 10
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f

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

    enum {SkillBlocking3 = 0, SkillBlocking2, SkillBlocking1, Skill, SkillWeapon_1, SkillWeapon_2,
        SkillWeapon_3};  // The skills options of the player.

    InputComponent* inputComponent;
    ItensManager* itemManager;

    bool skills[7];
    int skillPoints;

protected:
    int energy;
    Timer regenCD;
    bool isCrouching;
    bool isStading;
};

#endif /* PLAYER_H_ */
