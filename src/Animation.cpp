#include "Animation.h"
#include "Camera.h"

Animation::Animation(float x, float y, std::string sprite, float frameCount, float frameTime, bool ends) {
	sp = Sprite(sprite, frameCount, frameTime);
	box = Rect(x - sp.GetWidth()/2, y - sp.GetHeight()/2, sp.GetWidth(), sp.GetHeight());
	timeLimit = 0;
	oneTimeOnly = ends;
	endTimer = Timer(frameTime*frameCount);
}

Animation::~Animation() {

}

void Animation::Update(float dt) {
	sp.Update(dt);
	endTimer.Update(dt);
}

void Animation::Render() {
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}

void Animation::NotifyCollision(GameObject* other) {

}

bool Animation::Is(std::string type) {
	return (type == "Animation");
}

bool Animation::IsDead() {
	return (oneTimeOnly) ? (endTimer.GetTime() >= endTimer.GetLimit()) : false;
}

Animation* Animation::get() {
	return this;
}

