#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include <GameObject.h>

class PhysicsComponent
{
	public:
		PhysicsComponent();
		void Update(GameObject *obj,float dt);
		bool MapColisionX(GameObject *obj);
		bool MapColisionY(GameObject *obj);
};

#endif // PHYSICSCOMPONENT_H
