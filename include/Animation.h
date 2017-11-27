#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "TileMap.h"

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f

class Animation : public GameObject {
private:
	Sprite* sp;
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	void Render();
	void Update(TileMap* world, float dt);	
	bool IsDead();	
	
public:
	Animation(float x, float y, std::string sprite, float frameCount, float frameTime, bool ends);
	~Animation();	
};

#endif /* ANIMATION_H_ */
