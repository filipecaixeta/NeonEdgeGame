#include "TurretPieceGraphicsComponent.h"

#include "TurretPiece.h"

TurretPieceGraphicsComponent::TurretPieceGraphicsComponent(std::string baseName_, int type):
	GraphicsComponent(baseName_)
{
	switch(type){
		case 0:
			AddSprite(baseName, "Head", 13, 80);
			sp = sprites["Head"];
			surface = surfaces["Head"];
		break;
		case 1:
			AddSprite(baseName, "Body1", 9, 80);
			sp = sprites["Body1"];
			surface = surfaces["Body1"];
		break;
		case 2:
			AddSprite(baseName,"Body2", 2, 80);
			sp = sprites["Body2"];
			surface = surfaces["Body2"];
		break;
		case 3:
			AddSprite(baseName, "GunFront", 1, 80);
			sp = sprites["GunFront"];
			surface = surfaces["GunFront"];
		break;
		case 4:
			AddSprite(baseName, "GunBack", 1, 80);
			sp = sprites["GunBack"];
			surface = surfaces["GunBack"];
		break;
	}
}

TurretPieceGraphicsComponent::~TurretPieceGraphicsComponent(){

}

void TurretPieceGraphicsComponent::Update(GameObject* obj, float dt){
	mirror = (obj->facing == GameObject::LEFT);

	sp->Mirror(mirror);
	sp->Update(dt);
}