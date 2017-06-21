#ifndef DroneGRAPHICSCOMPONENT_H
#define DroneGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "Character.h"
#include "GraphicsComponent.h"

class DroneGraphicsComponent: public GraphicsComponent
{
public:
	DroneGraphicsComponent(std::string baseName_);
	~DroneGraphicsComponent();
	void Update(Character* obj, float dt);
};

#endif // DroneGRAPHICSCOMPONENT_H
