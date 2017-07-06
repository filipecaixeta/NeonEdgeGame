#ifndef PROJECTILEGRAPHICSCOMPONENT_H
#define PROJECTILEGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"

class ProjectileGraphicsComponent: public GraphicsComponent
{
public:
	ProjectileGraphicsComponent(std::string baseName_);
	~ProjectileGraphicsComponent();
	void Update(GameObject* obj, float dt);
};

#endif /* PROJECTILEGRAPHICSCOMPONENT_H */