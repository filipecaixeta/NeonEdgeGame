#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"

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
};

#endif /* RECT_H_ */
