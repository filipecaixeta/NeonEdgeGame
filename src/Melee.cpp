#include "Melee.h"
#include "Camera.h"
#include "Sprite.h"
#include "Timer.h"

Melee::Melee(std::string file, int frames, int frameTime, GameObject* owner, int lifetime, int power)
{
	name = "Melee";
	sp = Sprite(file, frames, frameTime);
	Melee::owner = owner;
	facing = owner->facing;
	Melee::lifetime = Timer(lifetime);
	Melee::lifetime.Start();
	Melee::power = power;
	Vec2 size = sp.GetSize();
	if(facing == LEFT)
	{
		sp.SetFrame(1);
		box.x = owner->box.x - size.x;
	}
	else
	{
		sp.SetFrame(2);
		box.x = owner->box.x + owner->box.w;
	}
	box.y = owner->box.y;
	box.w = size.x;
	box.h = size.y;
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
