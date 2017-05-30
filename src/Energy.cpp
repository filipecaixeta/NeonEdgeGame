#include "Energy.h"
#include "Camera.h"

Energy::Energy(float x, float y, std::string sprite, float frameCount, float frameTime, bool loops, float lifetime, bool dies)
{
	name = "Energy";
	sp = Sprite(sprite, frameCount, frameTime);
	Vec2 size = sp.GetSize();
	box = Rect(x, y, size.x, size.y);
	endTimer = Timer(lifetime);
	if(loops)
		endTimer.Start();
	Energy::loops = loops;
	Energy::dies = dies;
}

Energy::~Energy()
{

}

bool Energy::IsDead()
{
	return dead;
}

void Energy::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Gallahad") || other->Is("Lancelot"))
	{
		if(dies)
		{
			dead = true;
		}
	}
}

void Energy::UpdateTimers(float dt)
{
	endTimer.Update(dt);
}

void Energy::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	if(!loops && !endTimer.IsRunning())
		dead = true;
	sp.Update(dt);
}

void Energy::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
