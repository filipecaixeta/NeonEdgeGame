#ifndef LANCELOTGRAPHICSCOMPONENT_H
#define LANCELOTGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GameObject.h"
#include "GraphicsComponent.h"

class LancelotGraphicsComponent: public GraphicsComponent
{
public:
	LancelotGraphicsComponent(std::string baseName_);
	~LancelotGraphicsComponent();
	void Update(GameObject* obj, float dt);
};

#endif // LANCELOTGRAPHICSCOMPONENT_H
