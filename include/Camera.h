#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

class Camera {
private:
	GameObject* focus;

	static Camera* instance;

	Camera();
public:
	Vec2 pos;
	Vec2 speed;

	~Camera();
	void Follow(GameObject* newFocus);
	void Unfollow();
	void Update(float dt);
	GameObject* GetFocus();
	static Camera& GetInstance();
};

#endif /* CAMERA_H_ */
