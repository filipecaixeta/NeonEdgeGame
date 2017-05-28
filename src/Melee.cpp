#include "Melee.h"
#include "Camera.h"
#include "Sprite.h"
#include "Timer.h"

Melee::Melee(std::string file, int frames, int frameTime, Face facing, int lifetime, int power, GameObject* owner)
{
	name = "Attack";
	sp = Sprite(file, frames, frameTime);
	Melee::facing = facing;
	if(facing == LEFT)
	{
		sp.SetFrame(1);
		box.x = owner->box.x - sp.GetWidth();
	}
	else
	{
		sp.SetFrame(2);
		box.x = owner->box.x + owner->box.w;
	}
	box.y = owner->box.y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	Melee::lifetime = Timer(lifetime);
	Melee::lifetime.Start();
	Melee::power = power;
	Melee::owner = owner;
}

Melee::~Melee()
{

}

void Melee::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	if(facing == LEFT)
		box.x = owner->box.x - box.w;
	else
		box.x = owner->box.x + owner->box.w;
	box.y = owner->box.y;
}

void Melee::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
