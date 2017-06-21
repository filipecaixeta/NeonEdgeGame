#include "Box.h"
#include "Camera.h"
/*
Box::Box(float x, float y, std::string sprite, float frameCount, float frameTime, bool loops, float lifetime, bool dies)
{
	name = "Box";
	sp = Sprite(sprite, frameCount, frameTime);
	Vec2 size = sp.GetSize();
	box = Rect(x, y, size.x, size.y);
	endTimer = Timer(lifetime);
	if(loops)
		endTimer.Start();
	Box::loops = loops;
	Box::dies = dies;
}

Box::~Box()
{

}

bool Box::IsDead()
{
	return dead;
}

void Box::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Gallahad") || other->Is("Lancelot"))
	{
		if(other->facing == RIGHT)
		{
			//Box::SetPosition(Box::GetPosition().x + 10, Box::GetPosition().y);
		}
		else
		{
			//Box::SetPosition(Box::GetPosition().x - 10, Box::GetPosition().y);
		}
	}
}

void Box::UpdateTimers(float dt)
{
	endTimer.Update(dt);
}

void Box::Update(float dt)
{
	UpdateTimers(dt);
	sp.Update(dt);
}

void Box::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
*/