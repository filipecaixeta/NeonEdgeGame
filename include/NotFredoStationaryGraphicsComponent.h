#ifndef NOTFREDOSTATIONARYGRAPHICSCOMPONENT_H
#define NOTFREDOSTATIONARYGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class NotFredoStationaryGraphicsComponent: public GraphicsComponent
{
public:
    NotFredoStationaryGraphicsComponent(std::string baseName_);
    ~NotFredoStationaryGraphicsComponent();
    void Update(GameObject* obj, float dt);
};


#endif // NOTFREDOSTATIONARYGRAPHICSCOMPONENT_H
