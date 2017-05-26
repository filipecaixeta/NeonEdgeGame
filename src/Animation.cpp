#include "Animation.h"
#include "Camera.h"

Animation::Animation(float x, float y, std::string sprite, float frameCount, float frameTime, bool ends)
{
	sp = new Sprite(sprite, frameCount, frameTime);
	box = Rect(x - sp->GetWidth()/2, y - sp->GetHeight()/2, sp->GetWidth(), sp->GetHeight());
	timeLimit = 0;
	oneTimeOnly = ends;
	endTimer = Timer(frameTime*frameCount);
	if(ends)
		endTimer.Start();
}

Animation::~Animation()
{
	delete sp;
}

bool Animation::IsDead()
{
	return (oneTimeOnly && !endTimer.IsRunning());
}

void Animation::Update(float dt)
{
	sp->Update(dt);
	endTimer.Update(dt);
}

void Animation::Render()
{
	sp->Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
