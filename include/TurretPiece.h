#ifndef TURRETPIECE_H_
#define TURRETPIECE_H_
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767

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
	void TowerDamageOnPlayer(GameObject* other);
	void HeadTowerDamage(GameObject* other);

private:
	Character* center;
	int type;
	int refX, refY;
	float rotation;
};

#endif
