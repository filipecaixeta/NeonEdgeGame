#ifndef TURRETPIECE_H_
#define TURRETPIECE_H_

#include "Character.h"
#include "TurretPieceGraphicsComponent.h"

class TurretPiece: public Character
{
public:
	TurretPiece(Character* center, int x, int y, int type);
	~TurretPiece();
	void Shoot();
	void Rotate(float angle);
	float Rotation();
	int Type();
	void Kill();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* world, float dt);
	void Render();

private:
	Character* center;
	int type;
	int refX, refY;
	float rotation;
};

#endif