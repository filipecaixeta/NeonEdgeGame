#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "GameObject.h"

class Animation : public GameObject {
private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;

public:
	Animation(float x, float y, std::string sprite, float frameCount, float frameTime, bool ends);
	~Animation();
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	bool IsDead();
	Animation* get();
};

#endif /* ANIMATION_H_ */
