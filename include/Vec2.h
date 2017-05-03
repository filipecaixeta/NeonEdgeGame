#ifndef VEC2_H_
#define VEC2_H_

#include <math.h>
#include <iostream>

class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);
	~Vec2();
	float GetDX(float x);
	float GetDY(float y);
	float GetDS(Vec2 pos);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const float rhs) const;

    float dot(const Vec2& v1);
    float abs();
    float norm();
    Vec2 normalized();
    float distance(const Vec2& v1);
    float angle();
    Vec2 rotated(float ang);
    friend bool operator==(const Vec2 &v1, const Vec2 &v2);
    friend bool operator!=(const Vec2 &v1, const Vec2 &v2);
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
};

#endif /* VEC2_H_ */
