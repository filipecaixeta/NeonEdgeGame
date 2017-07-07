#ifndef INTERACTIVE_H_
#define INTERACTIVE_H_

#include "GameObject.h"
#include "InteractiveGraphicsComponent.h"

class Interactive : public GameObject
{
private:
	bool state;	
	int startingX, startingY;

public:
	Interactive(int x, int y, std::string name);
	virtual ~Interactive();
	virtual void On();
	virtual void Off();
	virtual bool Active();
	virtual void Trigger() = 0;
	virtual bool GetColisionData(SDL_Surface** surface_, SDL_Rect& clipRect_, Vec2& pos_, bool& mirror);
	virtual void NotifyObjectCollision(GameObject* other);
	virtual bool OutOfBounds(TileMap* map);
	virtual void Update(TileMap* map, float dt);
	virtual void Render();

	InteractiveGraphicsComponent* graphicsComponent;
};

#endif /* INTERACTIVE_H_ */