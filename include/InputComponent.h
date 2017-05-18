#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H
#include <GameObject.h>

class InputComponent
{
	public:
		InputComponent();
		void Update(GameObject *obj,float dt);
};

#endif // INPUTCOMPONENT_H
