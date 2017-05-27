#include "Attack.h"
#include "Camera.h"

Attack::~Attack()
{

}

bool Attack::IsDead()
{
	return (!lifetime.IsRunning());
}

void Attack::UpdateTimers(float dt)
{
	lifetime.Update(dt);
}
