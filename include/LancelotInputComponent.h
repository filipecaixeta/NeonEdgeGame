#ifndef LANCELOTINPUTCOMPONENT_H
#define LANCELOTINPUTCOMPONENT_H

#include "GameObject.h"

class LancelotInputComponent
{
public:
	LancelotInputComponent();
	void Update(GameObject* obj, float dt);
};

#endif // LANCELOTINPUTCOMPONENT_H
