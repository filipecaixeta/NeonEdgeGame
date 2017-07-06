#ifndef CEILINGENEMYGRAPHICSCOMPONENT_H
#define CEILINGENEMYGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"
#include "Character.h"


class CeilingEnemyGraphicsComponent: public GraphicsComponent
{
public:
    CeilingEnemyGraphicsComponent(std::string baseName_);
    ~CeilingEnemyGraphicsComponent();
    void Update(GameObject* obj, float dt);

};

#endif // CEILINGENEMYGRAPHICSCOMPONENT_H
