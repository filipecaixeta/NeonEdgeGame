#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Animation : public GameObject
{
private:
	Sprite* sp;
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;

public:
	Animation(float x, float y, std::string sprite, float frameCount, float frameTime, bool ends);
	~Animation();
	bool IsDead();
	void Update(float dt);
	void Render();
	
};

#endif /* ANIMATION_H_ */
