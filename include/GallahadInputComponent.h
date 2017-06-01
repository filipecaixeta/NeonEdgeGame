#ifndef GALLAHADINPUTCOMPONENT_H
#define GALLAHADINPUTCOMPONENT_H

#include "Gallahad.h"
#include "InputComponent.h"

class GallahadInputComponent: public InputComponent
{
public:
	GallahadInputComponent();
	void Update(Character* obj_, float dt_);
	void Hide();
};

#endif // GALLAHADINPUTCOMPONENT_H
