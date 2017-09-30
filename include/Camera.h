#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

class Camera {
private:
	GameObject* cameraFocus;

	static Camera* instance;

	Camera();
public:
	Vec2 screenPosition;
	Vec2 screenSpeed;
    Vec2 maxScreenPosition;

	~Camera();
	void CreateFocus(GameObject* newFocus);
	void StopFocus();
	void FocusUpdate(float dt);
	void SetPosition(Vec2 screenPosition);
	GameObject* GetFocus();
	static Camera& CheckInstance();
};

#endif /* CAMERA_H_ */
