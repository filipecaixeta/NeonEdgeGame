#include "Attack.h"
#include "Camera.h"

Attack::Attack(std::string file, int frames, int x, int y, int power, int lifetime, Face facing)
{
	sp = new Sprite(file, frames);
	box = Rect(x, y, sp->GetWidth(), sp->GetHeight());
	Attack::power = power;
	Attack::lifetime = Timer(lifetime);
	Attack::lifetime.Start();
	Attack::facing = facing;
	if(facing == LEFT)
	{
		sp->SetFrame(1);
		speed = Vec2(-0.4, 0);
	}
	else
	{
		sp->SetFrame(2);
		speed = Vec2(0.4, 0);
	}
}

Attack::~Attack()
{
	delete sp;
}

bool Attack::IsDead()
{
	return (!lifetime.IsRunning());
}

void Attack::UpdateTimers(float dt)
{
	lifetime.Update(dt);
}

void Attack::Update(float dt)
{
	UpdateTimers(dt);
}

void Attack::Render()
{
	sp->Render(box.x - Camera::GetInstance().pos.x -1, box.y - Camera::GetInstance().pos.y -1);
}
