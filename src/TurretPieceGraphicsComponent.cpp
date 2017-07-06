#include "TurretPieceGraphicsComponent.h"

#include "TurretPiece.h"

TurretPieceGraphicsComponent::TurretPieceGraphicsComponent(std::string baseName_, int type):
	GraphicsComponent(baseName_)
{
	switch(type){
		case 0:
			AddSprite(baseName, "Segment0", 9, 80);
			sp = sprites["Segment0"];
			surface = surfaces["Segment0"];
		break;
		case 1:
			AddSprite(baseName, "Segment1", 2, 80);
			sp = sprites["Segment1"];
			surface = surfaces["Segment1"];
		break;
		case 2:
			AddSprite(baseName, "Head", 13, 80);
			sp = sprites["Head"];
			surface = surfaces["Head"];
		break;
		case 3:
			AddSprite(baseName, "GunFront", 1, 80);
			sp = sprites["GunFront"];
			surface = surfaces["GunFront"];
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