#include "Rect.h"

Rect::Rect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float x, float y, float w, float h)
{
	Rect::x = x;
	Rect::y = y;
	Rect::w = w;
	Rect::h = h;
}

Rect::~Rect()
{

}

Vec2 Rect::GetXY()
{
	return Vec2(x,y);
}

void Rect::SetXY(Vec2 v)
{
	x = v.x;
	y = v.y;
}

Vec2 Rect::GetWH()
{
	return Vec2(w,h);
}

void Rect::SetWH(Vec2 v)
{
	w = v.x;
	h = v.y;
}

Vec2 Rect::GetCenter()
{
	return Vec2(x+w/2, y+h/2);
}

Vec2 Rect::GetBottomLeft()
{
	return Vec2(x,y+h);
}

bool Rect::IsInside(Vec2 dot)
{
	return((dot.x > x) && (dot.x < x+w) && (dot.y > y) && (dot.y < y+h));
}

Rect Rect::GetOverlap(const Rect &r)
{
	float minX = std::max(x, r.x);
	float maxX = std::min(x+w, r.x+r.w);
	float minY = std::max(y, r.y);
	float maxY = std::min(y+h, r.y+r.h);
	return Rect(minX, minY, maxX-minX, maxY-minY);
}

bool Rect::OverlapsWith(const Rect &r)
{
	float distX = x - r.x;
	float distY = y - r.y;
	if(distX >= r.w || -distX >= w || distY >= r.h || -distY >= h)
		return false;
	return true;
}

Rect Rect::operator+(const Vec2& v1)
{
	return Rect(x+v1.x, y+v1.y, w+v1.x, h+v1.y);
}

Rect Rect::operator-(const Vec2& v1)
{
	return Rect(x-v1.x, y-v1.y, w-v1.x, h-v1.y);
}
