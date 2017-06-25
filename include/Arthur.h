#ifndef ARTHUR_H
#define ARTHUR_H

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "ArthurGraphicsComponent.h"

enum State{IDLE,SLASHING,DASHING,PUNCHING};

class Arthur : public Character{
public:
	Arthur(int x, int y);
	~Arthur();
	void UpdateTimers(float dt);
	void Update(TileMap* world, float dt);
private:

};

#endif /*ARTHUR_H*/