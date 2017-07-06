#ifndef TURRETPIECE_H_
#define TURRETPIECE_H_

#include "Character.h"
#include "TurretPieceGraphicsComponent.h"

class TurretPiece: public Character{
public:
	TurretPiece(Character* center, int x, int y, int type);
	~TurretPiece();
	void Shoot();

private:
	Character* center;
	int type;
};

#endif