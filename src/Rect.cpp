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

Rect Rect::operator+(const Vec2& v1)
{
	return Rect(x+v1.x,y+v1.y,w+v1.x,h+v1.y);
}
Rect Rect::operator-(const Vec2& v1)
{
	return Rect(x-v1.x,y-v1.y,w-v1.x,h-v1.y);
}

bool Rect::OverlapsWith(const Rect &r)
{
	float distX = x-r.x;
	float distY = y-r.y;
	if ( distX>=r.w || -distX>=w )
		return false;
	if ( distY>=r.h || -distY>=h )
		return false;
	return true;
}

void Rect::SetXY(Vec2 v)
{
	x=v.x;
	y=v.y;
}
Vec2 Rect::GetXY()
{
	return Vec2(x,y);
}
void Rect::SetWH(Vec2 v)
{
	w=v.x;
	h=v.y;
}
Vec2 Rect::GetWH()
{
	return Vec2(w,h);
}

Vec2 Rect::GetOpverlap(const Rect &r)
{
	float minX = std::max(x,r.x);
	float maxX = std::min(x+w,r.x+r.w);
	float minY = std::max(y,r.y);
	float maxY = std::min(y+h,r.y+r.h);
	return Vec2(maxX-minX,maxY-minY);
}
