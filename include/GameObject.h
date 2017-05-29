#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "Rect.h"
#include "Vec2.h"
#include "TileMap.h"

class GameObject
{
public:
	enum Face : short int {UPPER, BOTTOM, LEFT, RIGHT, SPECIAL};
	enum Footing : short int {GROUNDED, LEFT_WALLED, RIGHT_WALLED, AIRBORNE};

	std::string name = "GameObject";
	Rect box = Rect();
	Face facing = RIGHT;
	Footing footing = GROUNDED; 
	Footing lastFooting = AIRBORNE;

	bool jumping = false;

	virtual ~GameObject() = 0;
	virtual bool Is(std::string type);
	virtual bool IsDead();
	virtual Vec2 GetPosition();
	virtual void SetPosition(Vec2 position);
	virtual void NotifyTileCollision(int tile, Face face);
	virtual void NotifyObjectCollision(GameObject* other);
	virtual void Update(TileMap* world, float dt)=0;
	virtual void Render() = 0;
};

#endif /* GAMEOBJECT_H_ */
