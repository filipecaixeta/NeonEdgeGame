//  Copyright 2017 Neon Edge Game

#include <math.h>
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

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float rhs) const {
    return Vec2(x * rhs, y * rhs);
}

Vec2 Vec2::operator/(const float v) const {
    return Vec2(x / v, y / v);
}

float Vec2::dot(const Vec2 &v1) {
    return (x * v1.x + y * v1.y);
}

float Vec2::abs() {
    return sqrt(x * x + y * y);
}

float Vec2::norm() {
    return this->abs();
}

Vec2 Vec2::normalized() {
    float norm = abs();
    return Vec2(x / norm, y = y / norm);
}

float Vec2::distance(const Vec2 &v1) {
    return (*this - v1).abs();
}

float Vec2::angle() {
    return atan2(y, x);
}

Vec2 Vec2::rotated(float ang) {
    return Vec2(x * cos(ang) - y * sin(ang), y * cos(ang) + x * sin(ang));
}

bool operator==(const Vec2 &v1, const Vec2 &v2) {
    return (v1.x == v2.x) && (v1.y == v2.y);
}

bool operator!=(const Vec2 &v1, const Vec2 &v2) {
    return !(v1 == v2);
}

std::ostream &operator<<(std::ostream &os, const Vec2 &v) {
    os <<'('<< v.x <<','<< v.y <<')';
    return os;
}
