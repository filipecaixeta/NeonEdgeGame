#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Character.h"

class Character;

class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void Update(Character* obj_, float dt_)=0;
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void StayStill();
	virtual void Crouch(bool c);
	virtual void Attack();
	virtual void Jump();
	virtual void Save(bool s);
protected:
	Character* obj;
	float dt;
};

#endif // INPUTCOMPONENT_H