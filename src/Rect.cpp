/**
    Copyright 2017 Neon Edge Game
    File Name: Rect.cpp
    Header File Name: Rect.h
    Class Name: Rect
    Function Objective:: Define a class to represent retangles.

*/

#include "Rect.h"

/**
    Objective: Constructor of the class Rect.
    @param None.
    @return: Instance of Rect.

*/
Rect::Rect() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

/**
     Objective: overload of the constructor of Rect class.
     @param float x -position x axis ofthe rect instance)
     @param float y - position y axis of the rect instance
     @param float w- width of the rect 
     @param float h - height of the rect
     @return: Instance of Rect.

*/
Rect::Rect(float x, float y, float w, float h) {
    Rect::x = x;
    Rect::y = y;
    Rect::w = w;
    Rect::h = h;
}

/**
    Objective: Destructor of the class Rect.
    @param None.
    @return: Void

*/
Rect::~Rect() {

}

/**
    Objective: Return the vector acting in the position of the rect.
    @param: None
    @return: Vec2(x,y)

*/
Vec2 Rect::GetXY() {
    return Vec2(x, y);
}

/**
    Objective:: Set the position vector that act in the rect.
    @param: Vec2 v - vector to be setble.
    @return: void.

*/
void Rect::SetXY(Vec2 v) {
    x = v.x;
    y = v.y;
}

/**
    Objective: Return the vector acting in the height and width of the rect.
    @param None.
    @return: Void

*/
Vec2 Rect::GetWH() {
    return Vec2(w, h);
}

/**
    Objective:  Set the heigth and width vector that act in the rect.
    @param: Vec2 v.
    @return: void.

*/
void Rect::SetWH(Vec2 v) {
    w = v.x;
    h = v.y;
}

/**
    Objective: Return the center point of the rect.
    @param None.
    @return Vec2 center - the center point of the rect.

*/
Vec2 Rect::GetCenter() {
	Vec2 center = Vec2(x + w / 2, y + h / 2);
    return center; //Calculate the center and return.
}

/**
    Objective: Return the left botton of the rect.
    @param None.
    @return  point of the botton left.

*/
Vec2 Rect::GetBottomLeft() {
	Vec2 bottomLeft = Vec2(x, y + h);
	return bottomLeft;
}

/**
    Objective:: Check if  a point is inside the rect.
    @param Vec2 dot - dot to be checked.
    @return bool(True if is inside. False if is not)

*/
bool Rect::IsInside(Vec2 dot) {
	bool checkPositionX = (dot.x > x);
	bool checkPositionY (dot.y > y);
	bool checkWeigth (dot.x < x + w);
	bool checkHeight = (dot.y < y + h);

	bool isInside = (checkPositionX && checkWeigth && checkPositionY && checkPositionY);
	return isInside;
}

/**
    Objective: Overlap a rect.
    @param: Rect r - rect to be overlaped.
    @return: Rect Overlaped.

*/
Rect Rect::GetOverlap(const Rect &r) {
    float minX = std::max(x, r.x);
    float maxX = std::min(x + w, r.x + r.w);
    float minY = std::max(y, r.y);
    float maxY = std::min(y + h, r.y + r.h);
    return Rect(minX, minY, maxX - minX, maxY - minY);
}

/**
    Objective: Check with rect is overlaped.
    @param: Rect r - Rect to be checked.
    @return: bool - true if is overlaped, false if is not.

*/
bool Rect::OverlapsWith(const Rect &r) {
    float distX = x - r.x;
    float distY = y - r.y;
    if(distX >= r.w || -distX >= w || distY >= r.h || -distY >= h) {
        return false;
    }
    return true;
}

/**
    Objective: Sum a point with the position of the rect.
    @param Vec2 v1 - (point to be summed)
    @return: Rect - position summed.
*/

Rect Rect::operator+(const Vec2& v1) {
    return Rect(x + v1.x, y + v1.y, w + v1.x, h + v1.y);
}

/**
    Objective: Subtract position of the rect with a dot.
    @param: Vec2 v1 - Dot to be subtracted.
    @return: Rect - Return the new rect in new position.

*/
Rect Rect::operator-(const Vec2& v1) {
    return Rect(x - v1.x, y - v1.y, w - v1.x, h - v1.y);
}
