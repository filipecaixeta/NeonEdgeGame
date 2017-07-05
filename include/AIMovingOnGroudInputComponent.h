#ifndef AIMOVINGONGROUDINPUTCOMPONENT_H
#define AIMOVINGONGROUDINPUTCOMPONENT_H

#include "InputComponent.h"

class AIMovingOnGroudInputComponent : public InputComponent
{
public:
	AIMovingOnGroudInputComponent();
	void Update(Character* obj_, float dt_);
protected:
	Character* obj;
};

#endif // AIMOVINGONGROUDINPUTCOMPONENT_H
