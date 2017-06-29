#include "Box.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

Box::Box(int x, int y, std::string sprite)
{
	name = "Box";
	sp = Sprite(sprite);
	Vec2 size = sp.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
	hitpoints = 10;
}

Box::~Box()
{

}

bool Box::IsDead()
{
	return false;
}

void Box::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Gallahad") || other->Is("Lancelot") || other->Is("Player"))
	{
		Character* c = (Character*) other;
		if((c->physicsComponent.velocity.x > 0) && (other->footing == GROUNDED))
		{
			box.x += 5;
		}
		else if((c->physicsComponent.velocity.x < 0) && (other->footing == GROUNDED))
		{
			box.x -= 5;
		}
	}
	Character* C = (Character*)other;
	if(C->Attacking())
	{
		hitpoints -= 1;
	}
}

void Box::Update(TileMap* map, float dt)
{
	physicsComponent.Update(this,map,dt);
}

void Box::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
