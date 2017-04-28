#ifndef VEC2_H_
#define VEC2_H_

#include <math.h>

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
};

#endif /* VEC2_H_ */
