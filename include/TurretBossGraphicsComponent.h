#ifndef TurretBossGRAPHICSCOMPONENT_H
#define TurretBossGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class TurretBossGraphicsComponent: public GraphicsComponent
{
public:
	TurretBossGraphicsComponent(std::string baseName_);
	~TurretBossGraphicsComponent();
	void Update(GameObject* obj, float dt);
};

#endif /*TurretBossGRAPHICSCOMPONENT_H*/