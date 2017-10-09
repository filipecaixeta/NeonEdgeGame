#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define MAX_SCREEN 999999.0f
#define INITIAL_POSITION_FOCUS 0.0f
#define FOCUS_CENTER 2

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
	void FocusUpdate(float delayTime);
	void SetPosition(Vec2 screenPosition);
	GameObject* GetFocus();
	static Camera& CheckInstance();
};

#endif /* CAMERA_H_ */
