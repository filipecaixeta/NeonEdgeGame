#ifndef GALLAHAD_H_
#define GALLAHAD_H_

#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "GallahadInputComponent.h"
#include "GallahadGraphicsComponent.h"

class Gallahad : public Player
{
public:
	Gallahad(int x, int y);
	~Gallahad();
	void Attack();
	void Hide();
	void Shoot();
	void Hold();
	bool Hiding();
	bool Shooting();
	void UpdateTimers(float dt);

private:
	Timer hiding;
	bool shooting;
};

#endif /* GALLAHAD_H_ */
