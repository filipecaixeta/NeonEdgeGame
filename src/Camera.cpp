#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Camera* Camera::instance = nullptr;

Camera::Camera() {
	focus = nullptr;
	pos = Vec2();
	speed = Vec2(1, 1);
}

Camera::~Camera() {
	focus = nullptr;
}

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if(!focus) {
		if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
			pos.y -= speed.y*dt;
		if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
			pos.y += speed.y*dt;
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
			pos.x -= speed.x*dt;
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
			pos.x += speed.x*dt;
	}else{
		/*speed.x = focus->speed.x;
		speed.y = focus->speed.y;
		if(speed.x < 0)
			speed.x *= -1;
		if(speed.y < 0)
			speed.y *= -1;*/
		int w, h;
		SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &w, &h);
		if(pos.x > focus->box.GetCenter().x-w/2) {
			if(pos.x-speed.x*dt < focus->box.GetCenter().x-w/2)
				pos.x = focus->box.GetCenter().x-w/2;
			else
				pos.x -= speed.x*dt;
		}else{
			if(pos.x+speed.x*dt > focus->box.GetCenter().x-w/2)
				pos.x = focus->box.GetCenter().x-w/2;
			else
				pos.x += speed.x*dt;
		}
		if(pos.y > focus->box.GetCenter().y-h/2) {
			if(pos.y-speed.y*dt < focus->box.GetCenter().y-h/2)
				pos.y = focus->box.GetCenter().y-h/2;
			else
				pos.y -= speed.y*dt;
		}else{
			if(pos.y+speed.y*dt > focus->box.GetCenter().y-h/2)
				pos.y = focus->box.GetCenter().y-h/2;
			else
				pos.y += speed.y*dt;
		}
	}
}

GameObject* Camera::GetFocus() {
	return focus;
}

Camera& Camera::GetInstance() {
	if(instance == nullptr)
		instance = new Camera();
	return *instance;
}
