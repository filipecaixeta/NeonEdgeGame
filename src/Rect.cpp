/*
 +  Copyright 2017 Neon Edge Game
 +  File Name: Rect.cpp
 +  Header File Name: Rect.h
 +  Class Name: Rect
 +  Function Objective:: Define a class to represent retangles.
 +*/

#include "Rect.h"

/*
  Function Objective: Constructor of the class Rect.
  param: None
  return: Instance of Rect.
*/
Rect::Rect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

/*
  Function Objective: overload of the constructor of Rect class.
  param: float x(position x axis ofthe rect instance),y(position y axis of the rect instance),
            w(width of the rect), h(height of the rect).
  return: Instance of Rect.
*/
Rect::Rect(float x, float y, float w, float h)
{
	Rect::x = x;
	Rect::y = y;
	Rect::w = w;
	Rect::h = h;
}

/*
  Function Objective: Destructor of the class Rect.
  param: None
  return: None
*/
Rect::~Rect()
{

}

/*
  Function Objective: Return the vector acting in the position of the rect.  
  param: None
  return: Vec2(x,y)
*/
Vec2 Rect::GetXY()
{
	return Vec2(x,y);
}

/*
  Function Objective:: Set the position vector that act in the rect.
  param: Vec2 v (vector to be setble).
  return: None.
*/
void Rect::SetXY(Vec2 v)
{
	x = v.x;
	y = v.y;
}

/*
  Function Objective: Return the vector acting in the height and width of the rect.
  param: None
  return: None
*/
Vec2 Rect::GetWH()
{
	return Vec2(w,h);
}

/*
  Function Objective:  Set the heigth and width vector that act in the rect.
  param: Vec2 v
  return: None
*/
void Rect::SetWH(Vec2 v)
{
	w = v.x;
	h = v.y;
}

/*
  Function Objective: Return the center point of the rect.
  param: None
  return: Vec2(x+w/2,y+h/2) (the center point of the rect).
*/
Vec2 Rect::GetCenter()
{
	return Vec2(x+w/2, y+h/2); //Calculate the center and return.
}

/*
  Function Objective: Return the left botton of the rect.
  param: None
  return: point of the botton left.
*/
Vec2 Rect::GetBottomLeft()
{
	return Vec2(x,y+h);
}

/*
  Function Objective:: Check if  a point is inside the rect.
  param: Vec2 dot (dot to be checked).
  return: bool(True if is inside. False if is not) 
*/
bool Rect::IsInside(Vec2 dot)
{
	// check if a one of the points(x,y,height,weigth) is inside of the other rect.
	return((dot.x > x) && (dot.x < x+w) && (dot.y > y) && (dot.y < y+h));   
}

/*
  Function Objective: Overlap a rect.
  param: Rect r(rect to be overlaped).
  return: Rect Overlaped.
*/
Rect Rect::GetOverlap(const Rect &r)
{
	float minX = std::max(x, r.x);
	float maxX = std::min(x+w, r.x+r.w);
	float minY = std::max(y, r.y);
	float maxY = std::min(y+h, r.y+r.h);
	return Rect(minX, minY, maxX-minX, maxY-minY);
}

/*
  Function Objective: Check with rect is overlaped.
  param: Rect r(Rect to be checked).
  return: bool (true if is overlaped, false if is not).
*/
bool Rect::OverlapsWith(const Rect &r)
{
	float distX = x - r.x;
	float distY = y - r.y;
	if(distX >= r.w || -distX >= w || distY >= r.h || -distY >= h)
		return false;
	return true;
}

/*
  Function Objective: Sum a point with the position of the rect.
  param: Point v1 (point to be summed)
  return: Rect position summed.
*/

Rect Rect::operator+(const Vec2& v1)
{
	return Rect(x+v1.x, y+v1.y, w+v1.x, h+v1.y);
}

/*
  Function Objective: Subtract position of the rect with a dot. 
  param: Dot to be subtracted.
  return: Return the new rect in new position.
*/
Rect Rect::operator-(const Vec2& v1)
{
	return Rect(x-v1.x, y-v1.y, w-v1.x, h-v1.y);
}
