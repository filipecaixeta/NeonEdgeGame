#ifndef LANCELOTINPUTCOMPONENT_H
#define LANCELOTINPUTCOMPONENT_H

#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f

#include "InputComponent.h"

class LancelotInputComponent: public InputComponent {
public:
    LancelotInputComponent();
    void Update(Player* player, float deltaTime);
    void Block();
    void Stop();
    void Combo(std::string c);
};

#endif // LANCELOTINPUTCOMPONENT_H
