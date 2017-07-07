#include "TurretPiece.h"
#include "StageState.h"
#include "Camera.h"
#include "Player.h"
#include "Projectile.h"

#include <cmath>
#include <math.h>

TurretPiece::TurretPiece(Character* center, int x, int y, int type):
	Character(0,0)
{
	name = "TurretBoss";
	this->center = center;
	this->type = type;
	facing = center->facing;
	refX = x;
	refY = y;
	physicsComponent.SetKinetic(true);
	graphicsComponent = new TurretPieceGraphicsComponent("TurretBoss", type);
	Vec2 size = graphicsComponent->GetSize();
	box.SetXY(Vec2(center->box.GetCenter().x+refX-(size.x/2),center->box.GetCenter().y+refY-(size.y/2)));
	box.SetWH(size);
	rotation = 0;
}

TurretPiece::~TurretPiece()
{

}

void TurretPiece::Shoot()
{
	if(type > 2)
	{
		float Vx = cos(rotation * M_PI/180) * 0.6;
		float Vy = sin(rotation * M_PI/180) * 0.6;
		StageState::AddObject(new Projectile(this, Vec2(Vx, -Vy), 1200, 1, true));
	}
}

void TurretPiece::Rotate(float angle)
{
	rotation = angle;
}

float TurretPiece::Rotation()
{
	return rotation;
}

int TurretPiece::Type()
{
	return type;
}

void TurretPiece::Kill()
{
	isDead = true;
}

void TurretPiece::NotifyObjectCollision(GameObject* other)
{
	if(type == 0)
	{
		if(other->IsPlayer())
		{
			Player* c = (Player*) other;
			if(c->Attacking())
			{
				center->Damage(c->Power());
			}
		}
		if(other->Is("Projectile"))
		{
			Projectile* p = (Projectile*) other;
			if(p->GetOwner()->IsPlayer())
			{
				center->Damage(p->Power());
			}
		}
	}
}

void TurretPiece::Update(TileMap* world, float dt)
{
	Vec2 size = graphicsComponent->GetSize();
	box.SetXY(Vec2(center->box.GetCenter().x+refX-(size.x/2),center->box.GetCenter().y+refY-(size.y/2)));
	graphicsComponent->Update(this, dt);
}

void TurretPiece::Render()
{
	graphicsComponent->Render(GetPosition()-Camera::GetInstance().pos, rotation);
}
