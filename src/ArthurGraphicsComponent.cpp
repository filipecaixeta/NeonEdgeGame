#include "ArthurGraphicsComponent.h"

ArthurGraphicsComponent::ArthurGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName, "Idle", 8, 80);

	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

ArthurGraphicsComponent::~ArthurGraphicsComponent(){

}

void ArthurGraphicsComponent::Update(Character* obj, float dt){
	
}