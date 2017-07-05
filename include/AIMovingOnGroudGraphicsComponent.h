#ifndef AIMOVINGONGROUDGRAPHICSCOMPONENT_H
#define AIMOVINGONGROUDGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class AIMovingOnGroudGraphicsComponent: public GraphicsComponent
{
public:
	AIMovingOnGroudGraphicsComponent(std::string baseName_);
	~AIMovingOnGroudGraphicsComponent();
	void Update(Character* obj, float dt);
};

#endif // AIMOVINGONGROUDGRAPHICSCOMPONENT_H
