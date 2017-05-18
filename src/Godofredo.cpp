#include "Godofredo.h"
#include "InputManager.h"
#include "Camera.h"
#include "StageState.h"
#include "SaveSystem.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

Godofredo* Godofredo::player = nullptr;

Godofredo::Godofredo(int x, int y):
	healthBar("healthBar2.png",5,15,10),
	inputComponent(),
	graphicsComponent("Lancelot"),
	physicsComponent(),
	saveComponent(SaveComponent::GetInstance())
{
	if(player) 
	{
		printf("Multiple Player Instances\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		player = this;
	}
	Vec2 size = graphicsComponent.GetSize();
	box = Rect(x, y, size.x, size.y);

	hitpoints = 10;
	power = 1;
	defense = 0;
	speed = Vec2(0, 0.6);

	facing = RIGHT;

	healthBar.SetPercentage(1.0f);
	stealthBar = Sprite("stealthBar.png", 11);
	stealthBar.SetFrameNormalized(0.0f);

	invincibilityT = Timer(500);
	attackT = Timer(500);
	hiddenT = Timer(1000);
}

Godofredo::~Godofredo()
{
	player = nullptr;
}

void Godofredo::Update(float dt)
{
	UpdateTimers(dt);
	inputComponent.Update(this,dt);
	physicsComponent.Update(this,dt);
	graphicsComponent.Update(this,dt);
	saveComponent.Update(this,dt);
}

void Godofredo::UpdateTimers(float dt)
{
	invincibilityT.Update(dt);
	attackT.Update(dt);
	hiddenT.Update(dt);
}

void Godofredo::UpdateCommands(float dt)
{

	if(InputManager::GetInstance().IsKeyDown(SDLK_e))
		AttackState(dt);

	if(InputManager::GetInstance().IsKeyDown(SDLK_SPACE))
	{
		Save("suamae.txt");
		Load("suamae.txt");
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_s))
		InvisibleState(dt);

	if(hiddenT.isRunning())
	{
		stealthBar.SetFrameNormalized(1-hiddenT.getElapsed());
		sp->SetTransparency(0.3);
	}
	else
	{
		stealthBar.SetFrameNormalized(0);
		sp->SetTransparency(1.0);
	}
}

void Godofredo::AttackState(float dt)
{
	if(!attackT.isRunning())
	{
		StageState::AddObject(new Attack("notattack.png", 2, box.x+(box.w/2), box.y, power, 200, speed.x<0?LEFT:RIGHT));
		attackT.Start();
	}
}

void Godofredo::InvisibleState(float dt)
{
	NotifyTileCollision(SPECIAL);
}

void Godofredo::Render()
{
	graphicsComponent.Render(GetPosition()-Camera::GetInstance().pos);
	healthBar.Render(5, 5);
	stealthBar.Render(5, 10+stealthBar.GetHeight());
}

void Godofredo::Damage(int damage)
{
	if(!invincibilityT.isRunning()) 
	{
		hitpoints -= (damage-defense);
		invincibilityT.Start();
	}
}

void Godofredo::NotifyCollision(GameObject* other) {
	if(other->Is("Notattack"))
		Damage(other->power);
}

bool Godofredo::Is(std::string type) {
	return (type == "Godofredo");
}

bool Godofredo::IsHidden() {
	return hidden;
}

bool Godofredo::IsDead() {
	return (hitpoints < 1);
}

Godofredo* Godofredo::get() {
	return this;
}
