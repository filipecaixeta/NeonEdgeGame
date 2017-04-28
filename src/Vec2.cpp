#include "Vec2.h"

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y) {
	Vec2::x = x;
	Vec2::y = y;
}

Vec2::~Vec2() {

}

float Vec2::GetDX(float x) {
	return x-Vec2::x;
}

float Vec2::GetDY(float y) {
	return y-Vec2::y;
}

float Vec2::GetDS(Vec2 pos) {
	return pow(pow(GetDX(pos.x), 2)+pow(GetDY(pos.y), 2), 0.5);
}

 Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
 }

 Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
 }

 Vec2 Vec2::operator*(const float rhs) const {
    return Vec2(x * rhs, y * rhs);
 }

