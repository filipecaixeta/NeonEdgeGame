#include "Interactive.h"
#include "Camera.h"

Interactive::Interactive(int x,int y,std::string name):
	GameObject()
{
	box.SetXY(Vec2(x,y));
	facing = RIGHT;
	state = false;
	graphicsComponent = new InteractiveGraphicsComponent(name);
	box.SetWH(graphicsComponent->GetSize());
}

Interactive::~Interactive()
{

}

void Interactive::On()
{
	state = true;
}

void Interactive::Off()
{
	state = false;
}

bool Interactive::Active()
{
	return state;
}

void Interactive::Trigger()
{

}

bool Interactive::GetColisionData(SDL_Surface** surface_,SDL_Rect &clipRect_,Vec2 &pos_, bool &mirror)
{
	*surface_ = graphicsComponent->GetSurface();
	clipRect_ = graphicsComponent->GetClip();
	pos_ = box.GetXY();
	mirror = graphicsComponent->GetMirror();
	return true;
}

void Interactive::NotifyObjectCollision(GameObject* other)
{
	
}

void Interactive::Update(TileMap* map, float dt)
{
	graphicsComponent->Update(this,dt);
}

void Interactive::Render()
{
	graphicsComponent->Render(GetPosition()-Camera::GetInstance().pos);
}
