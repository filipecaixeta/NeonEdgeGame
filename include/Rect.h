#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"
#include <iostream>

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define CENTER_AJUST 2
#define VALUE_INITIAL_FLOAT 0.0f

class Rect {
public:
	float x = VALUE_INITIAL_FLOAT;
	float y = VALUE_INITIAL_FLOAT;
	float w = VALUE_INITIAL_FLOAT;
	float h = VALUE_INITIAL_FLOAT;

	Rect();
	Rect(float x, float y, float w, float h);
	~Rect();
	Vec2 GetXY();
	void SetXY(Vec2 v);
	Vec2 GetWH();
	void SetWH(Vec2 v);
	Vec2 GetCenter();
	Vec2 GetBottomLeft();
	bool IsInside(Vec2 dot);
	Rect GetOverlap(const Rect& r);
	bool OverlapsWith(const Rect& r);
	Rect operator+(const Vec2& v1);
	Rect operator-(const Vec2& v1);

	friend std::ostream& operator<<(std::ostream& os, const Rect& v)
	{
		os <<'('<< v.x <<','<< v.y <<','<< v.w <<','<< v.h <<')';
		return os;
	}
};

#endif /* RECT_H_ */
