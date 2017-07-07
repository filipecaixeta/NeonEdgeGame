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
	startingX = x;
	startingY = y;
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

bool Interactive::OutOfBounds(TileMap* map)
{
	return (box.x < 0 || box.x > (map->GetWidth()-1)*map->GetTileWidth() ||
			box.y < 0 || box.y > (map->GetHeight()-1)*map->GetTileHeight());
}

void Interactive::Update(TileMap* map, float dt)
{
	if(OutOfBounds(map))
		SetPosition(Vec2(startingX,startingY));
	graphicsComponent->Update(this,dt);
}

void Interactive::Render()
{
	graphicsComponent->Render(GetPosition()-Camera::GetInstance().pos);
}
