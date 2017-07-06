#include "TurretPiece.h"

#include "StageState.h"

TurretPiece::TurretPiece(Character* center, int x, int y, int type):
	Character(0,0)
{
	name = "TurretBoss";
	this->center = center;
	this->type = type;
	refX = x;
	refY = y;
	physicsComponent.SetKinetic(true);
	graphicsComponent = new TurretPieceGraphicsComponent("TurretBoss", type);
	Vec2 size = graphicsComponent->GetSize();
	box.SetXY(Vec2(center->box.GetCenter().x+refX-(size.x/2),center->box.GetCenter().y+refY-(size.y/2)));
	box.SetWH(size);
}

TurretPiece::~TurretPiece()
{

}

void TurretPiece::Shoot()
{

}

void TurretPiece::NotifyObjectCollision(GameObject* other)
{

}

void TurretPiece::Update(TileMap* world, float dt)
{
	Vec2 size = graphicsComponent->GetSize();
	box.SetXY(Vec2(center->box.GetCenter().x+refX-(size.x/2),center->box.GetCenter().y+refY-(size.y/2)));
	graphicsComponent->Update(this, dt);
}
