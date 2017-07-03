#include "Life.h"
#include "Camera.h"

Life::Life(int x, int y, std::string sprite, float frameCount, float frameTime, bool loops, float lifetime, bool dies)
{
	name = "Life";
	sp = Sprite(sprite, frameCount, frameTime);
	Vec2 size = sp.GetSize();
	box = Rect(x, y, size.x, size.y);
	endTimer = Timer(lifetime);
	if(loops)
		endTimer.Start();
	Life::loops = loops;
	Life::dies = dies;
}

Life::~Life()
{

}

bool Life::IsDead()
{
	return dead;
}

void Life::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Gallahad") || other->Is("Lancelot"))
	{
		if(dies)
		{
			dead = true;
		}
	}
}

void Life::UpdateTimers(float dt)
{
	endTimer.Update(dt);
}

void Life::Update(TileMap* world, float dt)
{
	UpdateTimers(dt);
	if(!loops && !endTimer.IsRunning())
		dead = true;
	sp.Update(dt);
}

void Life::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
