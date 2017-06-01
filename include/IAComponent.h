#ifndef IACOMPONENT_H
#define IACOMPONENT_H

#include "InputComponent.h"

class IAComponent : public InputComponent
{
public:
	IAComponent();
	void Update(Character* obj_, float dt_);
};

#endif // IACOMPONENT_H
