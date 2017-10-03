#ifndef LANCELOTINPUTCOMPONENT_H
#define LANCELOTINPUTCOMPONENT_H

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
