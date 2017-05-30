#include "Projectile.h"
#include "Camera.h"
#include "Sprite.h"
#include "Timer.h"

Projectile::Projectile(std::string file, int frames, int frameTime,  GameObject* owner,
					   Vec2 speed, int lifetime, int power, bool pierce):
	physicsComponent(true)
{
	name = "Projectile";
	sp = Sprite(file, frames, frameTime);
	Projectile::owner = owner;
	facing = owner->facing;
	if(facing == LEFT)
		speed.x *= -1;
	physicsComponent.velocity = speed;
	Projectile::lifetime = Timer(lifetime);
	Projectile::lifetime.Start();
	Projectile::power = power;
	Projectile::pierce = pierce;
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
	box.y = owner->box.y + (owner->box.h/2 - size.y/2);
	box.w = size.x;
	box.h = size.y;
}

Projectile::~Projectile()
{

}

void Projectile::NotifyTileCollision(int tile, Face face)
{
	if(!pierce)
		lifetime.Stop();
}

void Projectile::NotifyObjectCollision(GameObject* other)
{
	if(!pierce)
		lifetime.Stop();
}

void Projectile::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	physicsComponent.Update(this,world,dt);
}

void Projectile::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
