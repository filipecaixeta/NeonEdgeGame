#ifndef GALLAHADINPUTCOMPONENT_H
#define GALLAHADINPUTCOMPONENT_H

#include "InputComponent.h"
#define VELOCITY_RANGED_LOW 0.2f
#define VELOCITY_RANGED_HIGH 0.4f
#define NO_ENERGY 0

class GallahadInputComponent: public InputComponent {
public:
    GallahadInputComponent();
    void Update(Player *player, float deltaTime);
    void Hide();
    void Toggle();
};

#endif // GALLAHADINPUTCOMPONENT_H
