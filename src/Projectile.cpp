#include "Projectile.h"
#include "Camera.h"
#include "StageState.h"
#include "Animation.h"

#include <cmath>
#include <math.h>

Projectile::Projectile(GameObject* owner, Vec2 speed, int lifetime, int power, bool pierce) {
	name = "Projectile";
	ownerN = owner->name;
	facing = owner->facing;
	if(facing == LEFT){
		speed.x *= -1;
	}
	physicsComponent = PhysicsComponent(true);
	physicsComponent.velocity = speed;
	graphicsComponent = new ProjectileGraphicsComponent(ownerN);
	Projectile::lifetime = Timer(lifetime);
	Projectile::lifetime.Start();
	Projectile::power = power;
	Projectile::pierce = pierce;
	Vec2 size = graphicsComponent->GetSize();
	if(facing == LEFT){
		box.x = owner->box.x - size.x;
	}
	else{
		box.x = owner->box.x + owner->box.w;
	}
	box.y = owner->box.y + (owner->box.h/2 - size.y/2);
	box.w = size.x;
	box.h = size.y;
}

Projectile::~Projectile() {

}

bool Projectile::IsDead() {
	if(!lifetime.IsRunning()) {
		StageState::AddObject(new Animation(box.GetCenter().x,
											box.GetCenter().y,
											ownerN+"ProjectileEnd.png",
											8,
											80,
											true));
	}
	return (!lifetime.IsRunning());
}

int Projectile::Power() {
	return power;
}

std::string Projectile::GetOwner() {
	return ownerN;
}

bool Projectile::GetColisionData(SDL_Surface** surface_,
								 SDL_Rect &clipRect_,
								 Vec2 &pos_,
								 bool &mirror) {
	
	*surface_ = graphicsComponent->GetSurface();
	clipRect_ = graphicsComponent->GetClip();
	pos_ = box.GetXY();
	mirror = graphicsComponent->GetMirror();
	return true;
}

void Projectile::NotifyTileCollision(int tile, Face face) {
	if(tile >= SOLID_TILE){
		lifetime.Stop();
	}
}

void Projectile::NotifyObjectCollision(GameObject* other) {
	if(!other->Is(ownerN)) {
		if(other->Is("Projectile")) {
			Projectile* p = (Projectile*) other;
			if(p->GetOwner() != ownerN) {
				if(!pierce){
					lifetime.Stop();
				}
			}
		} else if(!other->Is("BoxSpawner")) {
			if(!pierce){
				lifetime.Stop();
			}
		}
	}
}

void Projectile::UpdateTimers(float dt) {
	lifetime.Update(dt);
}

void Projectile::Update(TileMap* world, float dt) {
	UpdateTimers(dt);
	physicsComponent.Update(this,world,dt);
	graphicsComponent->Update(this,dt);
}

void Projectile::Render() {
	float angle = atan(physicsComponent.velocity.y/physicsComponent.velocity.x) * 180/M_PI;
	graphicsComponent->Render(Vec2(box.x - Camera::GetInstance().pos.x,
								   box.y - Camera::GetInstance().pos.y),
							  angle);
}
