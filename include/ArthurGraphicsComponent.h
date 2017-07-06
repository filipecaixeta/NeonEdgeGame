#ifndef ARTHURGRAPHICSCOMPONENT_H
#define ARTHURGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class ArthurGraphicsComponent: public GraphicsComponent
{
public:
	ArthurGraphicsComponent(std::string baseName_);
	~ArthurGraphicsComponent();
	void Update(GameObject* obj, float dt);
};

#endif /*ARTHURGRAPHICSCOMPONENT_H*/