#ifndef GALLAHADGRAPHICSCOMPONENT_H
#define GALLAHADGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class GallahadGraphicsComponent: public GraphicsComponent
{
public:
	GallahadGraphicsComponent(std::string baseName_);
	~GallahadGraphicsComponent();
	void Update(GameObject* obj, float dt);
};

#endif // GALLAHADGRAPHICSCOMPONENT_H
