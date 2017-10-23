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
	TurretPiece(Character* center, int x = 0, int y = 0, int type = 0);
	~TurretPiece();
	void Shoot();
	void Rotate(float angle = 0.0);
	float Rotation();
	int Type();
	void Kill();
	void NotifyObjectCollision(GameObject* other = NULL);
	void Update(TileMap* world, float deltaTime = 0.0);
	void Render();
	void TowerDamageOnPlayer(GameObject* other = NULL);
	void HeadTowerDamage(GameObject* other = NULL);

private:
	Character* center;
	int type;
	int refX, refY;
	float rotation;
};

#endif
