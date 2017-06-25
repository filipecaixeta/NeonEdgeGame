#ifndef ARTHUR_H
#define ARTHUR_H

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "ArthurGraphicsComponent.h"

enum ArthurState{IDLE,SLASHING,DASHINGLEFT,DASHINGRIGHT,PUNCHING};

class Arthur : public Character{
public:
	Arthur(int x, int y);
	~Arthur();
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	void Attack();
	ArthurState GetState();
private:
	Timer idle;
	Timer slash;
	Timer dash;
	Timer punch;
	Rect radius;
	ArthurState state;
	bool triggered;
};

#endif /*ARTHUR_H*/