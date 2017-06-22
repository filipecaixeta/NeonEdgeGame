#ifndef DroneINPUTCOMPONENT_H
#define DroneINPUTCOMPONENT_H

#include "InputComponent.h"

class DroneInputComponent: public InputComponent
{
public:
	DroneInputComponent();
	void Update(Player* obj_, float dt_);
	void Block();
};

#endif // DroneINPUTCOMPONENT_H
