#ifndef LANCELOTINPUTCOMPONENT_H
#define LANCELOTINPUTCOMPONENT_H

#include "GameObject.h"
#include "InputComponent.h"

class LancelotInputComponent: public InputComponent
{
public:
	LancelotInputComponent();
	void Update(Character* obj_, float dt_);
	void Block();
};

#endif // LANCELOTINPUTCOMPONENT_H
