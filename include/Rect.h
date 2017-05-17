#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"
#include <iostream>

class Rect {
public:
	float x;
	float y;
	float w;
	float h;

	Rect();
	Rect(float x, float y, float w, float h);
	~Rect();
	bool IsInside(Vec2 dot);
	Vec2 GetCenter();
	Vec2 GetV1();
	Vec2 GetV2();
	Vec2 GetV3();
	Vec2 GetV4();
	float GetDX(float x);
	float GetDY(float y);
	float GetDS(Vec2 pos);
	Rect operator+(const Vec2& v1);
	Rect operator-(const Vec2& v1);
	void SetXY(Vec2 v);
	Vec2 GetXY();
	void SetWH(Vec2 v);
	Vec2 GetWH();
	Vec2 GetOpverlap(const Rect& r);
	bool OverlapsWith(const Rect& r);
	friend std::ostream& operator<<(std::ostream& os, const Rect& v)
	{
		os <<'('<< v.x <<','<< v.y <<','<< v.w <<','<< v.h <<')';
		return os;
	}
};

#endif /* RECT_H_ */
