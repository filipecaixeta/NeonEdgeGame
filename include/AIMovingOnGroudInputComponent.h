#ifndef AIMOVINGONGROUDINPUTCOMPONENT_H
#define AIMOVINGONGROUDINPUTCOMPONENT_H

#include "InputComponent.h"

class AIMovingOnGroudInputComponent : public InputComponent {
public:
    AIMovingOnGroudInputComponent();
    void Update(Character *character, float deltaTime);
protected:
    Character *character;
};

#endif // AIMOVINGONGROUDINPUTCOMPONENT_H
