#include "TurretPiece.h"

#include "StageState.h"

TurretPiece::TurretPiece(Character* center, int x, int y, int type):
	Character(x,y)
{
	this->type = type;
	this->physicsComponent.kinetic = true;
	graphicsComponent = new TurretPieceGraphicsComponent("TurretBoss", type);
	name = "TurretBoss";
	box.SetWH(graphicsComponent->GetSize());
	this->center = center;
}

TurretPiece::~TurretPiece(){

}

void TurretPiece::Shoot(){

}

