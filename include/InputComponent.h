#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Player.h"

class Player;

class InputComponent {
public:
    InputComponent();
    virtual ~InputComponent();
    virtual void Update(Player *player, float deltaTime);
    virtual void MoveLeft();
    virtual void MoveRight();
    virtual void MoveUp();
    virtual void MoveDown();
    virtual void StayStill();
    virtual void Crouch(bool crouchStatus);
    virtual void Attack();
    virtual void Jump();
    virtual void Save(bool saveStatus);
    virtual void Active();
    virtual void ProcessItems();

protected:
    Player* player;
    float deltaTime;
};

#endif // INPUTCOMPONENT_H
