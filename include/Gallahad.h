#ifndef GALLAHAD_H_
#define GALLAHAD_H_

#include "Timer.h"
#include "Character.h"
#include "TileMap.h"
#include "GallahadInputComponent.h"
#include "GallahadGraphicsComponent.h"

class Gallahad : public Character
{
public:
	Gallahad(int x, int y);
	~Gallahad();
	void Attack();
	bool Hiding();
	void Hide();
	void UpdateTimers(float dt);
private:
	Timer hiding;
};

#endif /* GALLAHAD_H_ */
