#include "Arthur.h"

Arthur::Arthur(int x, int y):
	Character(x,y)
{
	box.SetWH(graphicsComponent->GetSize());
}

Arthur::~Arthur(){

}

void Arthur::UpdateTimers(float dt){

}

void Arthur::Update(TileMap* world, float dt){
	
}