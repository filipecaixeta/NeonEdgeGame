// Copyright 2017 Neon Edge Game

#include "GallahadGraphicsComponent.h"
#include "Gallahad.h"
#include "Rect.h"

GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_) {
	AddSprite(baseName, "Idle", 8, 80);
	AddSprite(baseName, "Running", 8, 80);
	AddSprite(baseName, "Crouching", 4, 80, true);
	AddSprite(baseName, "Active", 4, 80, true);
	AddSprite(baseName, "Jumping", 8, 80, true);
	AddSprite(baseName, "Shot", 4, 80, true);
	AddSprite(baseName, "RunningShot", 8, 80);
	AddSprite(baseName, "JumpingShot", 8, 80, true);
	AddSprite(baseName, "Dying", 8, 100, true);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

GallahadGraphicsComponent::~GallahadGraphicsComponent() {
}

void GallahadGraphicsComponent::Update(GameObject* obj, float dt) {
	Gallahad* g = (Gallahad*) obj;
    mirror = (obj->facing == GameObject::LEFT);
	if (g->Shooting()) {
		if (g->physicsComponent.velocity.x != 0) {
			UpdateSprite(obj, "RunningShot");
        }
		else if (obj->footing == GameObject::AIRBORNE) {
			UpdateSprite(obj, "JumpingShot");
        }
		else {
			UpdateSprite(obj, "Shot");
		}
        if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
			obj->footing = GameObject::AIRBORNE;
        }
	}
	else if (g->Crouching()) {
		UpdateSprite(obj, "Crouching");
		if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
			obj->footing = GameObject::AIRBORNE;
        }
	}
	else if (!g->Active()) {
		UpdateSprite(obj, "Active");
		if (obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED) {
			obj->footing = GameObject::AIRBORNE;
        }
	}
	else if (obj->footing == GameObject::AIRBORNE) {
		UpdateSprite(obj, "Jumping");
	}
	else if (g->physicsComponent.velocity.x == 0) {
		UpdateSprite(obj, "Idle");
	}
	else {
		UpdateSprite(obj, "Running");
	}
	if (g->Hiding()) {
		sp->SetTransparency(0.3);
	}
	else {
		sp->SetTransparency(1);
	}

	if (obj->dieTimer.IsRunning()) {
		UpdateSprite(obj, "Dying");
	}
	sp->Mirror(mirror);
	sp->Update(dt);
}
