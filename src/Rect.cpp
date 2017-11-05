/**
 * Copyright 2017 Neon Edge Game
 * File Name: Rect.cpp
 * Header File Name: Rect.h
 * Class Name: Rect
 * Function Objective:: Define a class to represent retangles.
 */

 #include "Rect.h"
 #include "Logger.h"
 
 /**
  * Objective: Method responsible for testing float parameters received in functions.
  *
  * @param float testFloat - Value to be tested.
  * @return - False whether the value is valid or true if the value is valid.
  */
  bool CheckFloatRect(float testFloat) {
    bool veryValue = false;
    if ((testFloat >= FLOAT_SIZE_MIN) && (testFloat <= FLOAT_SIZE_MAX)) {
        veryValue = true;
    } else {
        // It does nothing.
    }
    return veryValue;
}


 /**
  * Objective: Constructor of the class Rect.
  *
  * @param None.
  * @return: Instance of Rect.
  */
 Rect::Rect() {
    if (CheckFloatRect(VALUE_INITIAL_FLOAT)) {
        x = VALUE_INITIAL_FLOAT;
        y = VALUE_INITIAL_FLOAT;
        w = VALUE_INITIAL_FLOAT;
        h = VALUE_INITIAL_FLOAT;
    } else {
        Log::instance.error("Float out of bounds!");          
    }
 }


 /**
  * Objective: overload of the constructor of Rect class.
  *
  * @param float x -position x axis ofthe rect instance)
  * @param float y - position y axis of the rect instance
  * @param float w- width of the rect
  * @param float h - height of the rect
  * @return: Instance of Rect.
  */
 Rect::Rect(float x, float y, float w, float h) {

     if (CheckFloatRect(y) && CheckFloatRect(x) && CheckFloatRect(w) && CheckFloatRect(h)) {
         Rect::x = x;
         Rect::y = y;
         Rect::w = w;
         Rect::h = h;
     } else {
        Log::instance.error("Float out of bounds!");                  
     }
 }

 /**
  * Objective: Destructor of the class Rect.
  *
  * @param None.
  * @return: Void
  */
 Rect::~Rect() {

 }

 /**
  * Objective: Return the vector acting in the position of the rect.
  *
  * @param: None
  * @return: Vec2(x,y)
  */
 Vec2 Rect::GetXY() {
     if (CheckFloatRect(x) && CheckFloatRect(y)) {
        return Vec2(x, y);
     } else {
        Log::instance.error("Float out of bounds!");        
     }
 }

 /**
  * Objective:: Set the position vector that act in the rect.
  *
  * @param: Vec2 v - vector to be setble.
  * @return: void.
  */
 void Rect::SetXY(Vec2 v) {
     if (CheckFloatRect(v.x) && CheckFloatRect(v.y)) {
         x = v.x;
         y = v.y;
     } else {
        Log::instance.error("Float out of bounds!");                  
     }

 }

 /**
  * Objective: Return the vector acting in the height and width of the rect.
  *
  * @param None.
  * @return: Void
  */
 Vec2 Rect::GetWH() {
    if (CheckFloatRect(w) && CheckFloatRect(h)) {
        return Vec2(w, h);
    } else {
        Log::instance.error("Float out of bounds!");        
    }
 }

 /**
  * Objective:  Set the heigth and width vector that act in the rect.
  *
  * @param: Vec2 v.
  * @return: void.
  */
 void Rect::SetWH(Vec2 v) {
     if (CheckFloatRect(v.x) && CheckFloatRect(v.y)) {
         w = v.x;
         h = v.y;
     } else {
        Log::instance.error("Float out of bounds!");                  
     }
 }

 /**
  * Objective: Return the center point of the rect.
  *
  * @param None.
  * @return Vec2 center - the center point of the rect.
  */
 Vec2 Rect::GetCenter() {
     if (CheckFloatRect(x + w) && CheckFloatRect(y + h)) {
        Vec2 center = Vec2(x + w / CENTER_AJUST, y + h / CENTER_AJUST);
        return center; //Calculate the center and return.
    } else {
        Log::instance.error("Float out of bounds!");                  
    } 
 }

 /**
  * Objective: Return the left botton of the rect.
  *
  * @param None.
  * @return  point of the botton left.
  */
 Vec2 Rect::GetBottomLeft() {
     if (CheckFloatRect(x) && CheckFloatRect(y+h)) {
        Vec2 bottomLeft = Vec2(x, y + h);
        return bottomLeft;
    } else {
        Log::instance.error("Float out of bounds!");                  
    } 
 }

 /**
  * Objective:: Check if  a point is inside the rect.
  *
  * @param Vec2 dot - dot to be checked.
  * @return bool(True if is inside. False if is not)
  */
 bool Rect::IsInside(Vec2 dot) {
     bool isInside = false;
     if (CheckFloatRect(dot.x) && CheckFloatRect(dot.y)) {
         bool checkPositionX = (dot.x > x);
         bool checkPositionY = (dot.y > y);
         bool checkWeigth = (dot.x < x + w);
         bool checkHeight = (dot.y < y + h);
         isInside = (checkPositionX && checkWeigth && checkPositionY && checkPositionY);
     } else {
         // It does nothing.
     }
     return isInside;
 }

 /**
  * Objective: Overlap a rect.
  *
  * @param: Rect r - rect to be overlaped.
  * @return: Rect Overlaped.
  */
 Rect Rect::GetOverlap(const Rect &r) {
     if (CheckFloatRect(VALUE_INITIAL_FLOAT)) {
        float minX = VALUE_INITIAL_FLOAT;
        float maxX = VALUE_INITIAL_FLOAT;
        float minY = VALUE_INITIAL_FLOAT;
        float maxY = VALUE_INITIAL_FLOAT;
        if (CheckFloatRect(r.x) && CheckFloatRect(r.y) && CheckFloatRect(r.w) && CheckFloatRect(r.h)
        && CheckFloatRect(x + w) && CheckFloatRect(r.x + r.w) && CheckFloatRect(y + h)
        && CheckFloatRect(r.y + r.h)) {
            minX = std::max(x, r.x);
            maxX = std::min(x + w, r.x + r.w);
            minY = std::max(y, r.y);
            maxY = std::min(y + h, r.y + r.h);
        } else {
            // It does nothing.
        } 
        if (CheckFloatRect(maxX - minX && maxY - minY)) {  
            return Rect(minX, minY, maxX - minX, maxY - minY);
        } else {
            Log::instance.error("Float out of bounds!");                      
        }
    } else {
        Log::instance.error("Float out of bounds!");          
        
    }
 }

 /**
  * Objective: Check with rect is overlaped.
  *
  * @param: Rect r - Rect to be checked.
  * @return: bool - true if is overlaped, false if is not.
  */
 bool Rect::OverlapsWith(const Rect &r) {
     bool testBoolean = true;
     if ((CheckFloatRect(r.x)) && (CheckFloatRect(r.y)) && CheckFloatRect(r.w) && CheckFloatRect(r.h) ) {
         float distX = x - r.x;
         float distY = y - r.y;
         if ((distX >= r.w || -distX >= w || distY >= r.h || -distY >= h)) {
             testBoolean = false;
         } else {
             // It does nothing.
         }
     } else {
         // It does nothing.
     }
     return testBoolean;
 }

 /**
  * Objective: Sum a point with the position of the rect.
  *
  * @param Vec2 v1 - (point to be summed)
  * @return: Rect - position summed.
  */
 Rect Rect::operator+(const Vec2& v1) {

    if (CheckFloatRect(VALUE_INITIAL_FLOAT)) {
        float sumX = VALUE_INITIAL_FLOAT;
        float sumY = VALUE_INITIAL_FLOAT;
        float sumW = VALUE_INITIAL_FLOAT;
        float sumH = VALUE_INITIAL_FLOAT;

        if (CheckFloatRect(v1.x) && CheckFloatRect(v1.y) && CheckFloatRect(x) && CheckFloatRect(y) 
        && CheckFloatRect(w) && CheckFloatRect(h) && CheckFloatRect(x + v1.x) && CheckFloatRect(y + v1.y) 
        && CheckFloatRect(w + v1.x) && CheckFloatRect(h + v1.y)) {
            sumX = x + v1.x;
            sumY = y + v1.y;
            sumW = w + v1.x;
            sumH = h + v1.y;
        } else {
            Log::instance.error("Float out of bounds!");                      
        }
        if (CheckFloatRect(sumX) && CheckFloatRect(sumY) && CheckFloatRect(sumW) && CheckFloatRect(sumH)) {
            return Rect(sumX, sumY, sumW, sumH);
        } else {
            Log::instance.error("Float out of bounds!");                      
        }
    } else {
        Log::instance.error("Float out of bounds!");          
    }
 }

 /**
  * Objective: Subtract position of the rect with a dot.
  *
  * @param: Vec2 v1 - Dot to be subtracted.
  * @return: Rect - Return the new rect in new position.
  */
 Rect Rect::operator-(const Vec2& v1) {

     if (CheckFloatRect(VALUE_INITIAL_FLOAT)) {
        float subX = VALUE_INITIAL_FLOAT;
        float subY = VALUE_INITIAL_FLOAT;
        float subW = VALUE_INITIAL_FLOAT;
        float subH = VALUE_INITIAL_FLOAT;

        if (CheckFloatRect(v1.x) && CheckFloatRect(v1.y) && CheckFloatRect(x) && CheckFloatRect(y) 
        && CheckFloatRect(w) && CheckFloatRect(h) && CheckFloatRect(x - v1.x) && CheckFloatRect(y - v1.y) 
        && CheckFloatRect(w - v1.x) && CheckFloatRect(h - v1.y)) {
            subX = x - v1.x;
            subY = y - v1.y;
            subW = w - v1.x;
            subH = h - v1.y;
        } else {
            Log::instance.error("Float out of bounds!");                      
        }
        if (CheckFloatRect(subX) && CheckFloatRect(subY) && CheckFloatRect(subW) && CheckFloatRect(subH)) {
            return Rect(subX, subY, subW, subH);
        } else {
            Log::instance.error("Float out of bounds!");                      
        }
    } else {
        Log::instance.error("Float out of bounds!");          
    }
 }
