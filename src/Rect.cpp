#include "Rect.h"

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
	Rect::x = x;
	Rect::y = y;
	Rect::w = w;
	Rect::h = h;
}

Rect::~Rect() {

}

bool Rect::IsInside(Vec2 dot) {
	return((dot.x > x) && (dot.x < x+w) && (dot.y > y) && (dot.y < y+h));
}

Vec2 Rect::GetCenter() {
	return Vec2(x+w/2, y+h/2);
}

Vec2 Rect::GetV1() {
	return Vec2(x, y);
}

Vec2 Rect::GetV2() {
	return Vec2(x+w, y);
}

Vec2 Rect::GetV3() {
	return Vec2(x+w, y+h);
}

Vec2 Rect::GetV4() {
	return Vec2(x, y+h);
}

float Rect::GetDX(float x) {
	return x-Rect::x;
}

float Rect::GetDY(float y) {
	return y-Rect::y;
}

float Rect::GetDS(Vec2 pos) {
	return pow(pow(GetDX(pos.x), 2)+pow(GetDY(pos.y), 2), 0.5);
}
