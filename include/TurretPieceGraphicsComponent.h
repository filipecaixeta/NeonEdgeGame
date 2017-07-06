#ifndef TURRETPIECEGRAPHICSCOMPONENT_H
#define TURRETPIECEGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class TurretPieceGraphicsComponent: public GraphicsComponent
{
public:
	TurretPieceGraphicsComponent(std::string baseName_, int type);
	~TurretPieceGraphicsComponent();
	void Update(GameObject* obj, float dt);
};

#endif /*TURRETPIECEGRAPHICSCOMPONENT_H*/