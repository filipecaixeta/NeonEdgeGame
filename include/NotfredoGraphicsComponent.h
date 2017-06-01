#ifndef NOTFREDOGRAPHICSCOMPONENT_H
#define NOTFREDOGRAPHICSCOMPONENT_H

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class NotfredoGraphicsComponent: public GraphicsComponent
{
public:
	NotfredoGraphicsComponent(std::string baseName_);
	~NotfredoGraphicsComponent();
	void Update(Character* obj, float dt);
};

#endif // NOTFREDOGRAPHICSCOMPONENT_H
