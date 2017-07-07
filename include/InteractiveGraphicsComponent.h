#ifndef INTERACTIVEGRAPHICSCOMPONENT_H
#define INTERACTIVEGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"

class InteractiveGraphicsComponent: public GraphicsComponent
{
public:
	InteractiveGraphicsComponent(std::string baseName_);
	~InteractiveGraphicsComponent();
	void Update(GameObject* obj, float dt);
};

#endif /* INTERACTIVEGRAPHICSCOMPONENT_H */