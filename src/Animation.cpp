/**
    Copyright (c) 2017 Neon Edge Game.
    File Name: Animation.cpp
    Header File Name: Animation.h
    Class Name: Animation
    Objective: its manages the animation of the game.

*/

#include "Animation.h"
#include "Camera.h"
#include "Logger.h"

#include <cstdlib>
#include <sys/time.h>
#include <assert.h>

/**
 * Objective: Method responsible for testing float parameters received in functions.
 *
 * @param float testFloat - Value to be tested.
 * @return - False whether the value is valid or true if the value is valid.
 */
 bool CheckFloatAnimation(float testFloat) {
    bool veryValue = false;
    if ((testFloat >= FLOAT_SIZE_MIN ) && (testFloat <= FLOAT_SIZE_MAX)) {
        Log::instance.info("Valid value! Method CheckFloat Animation");  
        veryValue = true;
    } else {
        Log::instance.error("Tested value higher or lower than allowed!");  
        // It does nothing.
    }
    assert(veryValue == false || veryValue == true);
    return veryValue;
}

/**
 * Objective: Method responsible for testing boolean parameters received in functions.
 *
 * @param bool testBool - Boolean to be tested.
 * @return - False whether the boolean is valid or true if the boolean is valid.
 */
bool CheckBoolean(bool testBool) {
    bool veryBool = false;
    if (testBool || !testBool) {
        Log::instance.info("Valid bool! Method CheckBoolean Animation");  
        veryBool = true;
    } else {
        Log::instance.error("Tested bool higher or lower than allowed!");  
        // It does nothing.
    }
    assert(veryBool == false || veryBool == true);
    return veryBool;
}

/**
 *  Objective: it constructs Animation components.
 *
 * @param float x - The measures in x of animation.
 * @param float y - The measures in y of animation.
 * @param string sprite - sprit that will be animated.
 * @param float frameCount - a count to the frame.
 * @param float frameTime - a time to the frame.
 * @param bool end - the end of animation.
 * @return none.
 */
Animation::Animation(float x, float y, std::string sprite, float frameCount, float frameTime, bool ends) {

    if (CheckFloatAnimation(x) && CheckFloatAnimation(y) && CheckFloatAnimation(frameCount) && CheckFloatAnimation(frameTime) 
    && CheckBoolean(ends)) {
        name = "Animation"; 
        sp = new Sprite(sprite, frameCount, frameTime);  // Making a new object sprite

        // A box rectangle is created receving the height and de the width of sprite in x and in y.
        box = Rect(x - sp->GetWidth()/2, y - sp->GetHeight()/2, sp->GetWidth(), sp->GetHeight());
        timeLimit = 0;  // Sets a time limit 0 to default.
        oneTimeOnly = ends;
        endTimer = Timer(frameTime*frameCount);

        // Manager the end of animation
        if(ends) {
            // If the time of animation over, start the end time.
            endTimer.Start();
        } else {
            // It does nothing
        }
        timeval t1;
        gettimeofday(&t1, NULL);
        srand(t1.tv_usec * t1.tv_sec);
        if(rand()%2 == 0) {
            sp->Mirror(true);
        } else {
            sp->Mirror(false);
        }
    } else {
        Log::instance.error("Boolean or float invalid in Animation!");          
    }
}

/**
 * Objective: it destroys the sprite animation.
 *
 * @param none.
 * @return none.
 */
Animation::~Animation() {
	delete sp;
}

/**
 * Objective: it checks if the animation is dead.
 *
 * @param none.
 * @return none.
 */
bool Animation::IsDead() {
	return (oneTimeOnly && !endTimer.IsRunning());  // If the time of animation over will return true.
}

/**
 * Objective: This method update the animation.
 *
 * @param none.
 * @return none.
 */
void Animation::Update(TileMap* world, float dt) {
    if (CheckFloatAnimation(dt)) {
	    sp->Update(dt);
        endTimer.Update(dt);
    } else {
        Log::instance.info("Float is not valid!");          
    }
}

/**
 * Objective: Render the box sprites by the focus camera in position y an x.
 * @param none.
 * @return none.
 */
void Animation::Render() {
    if (CheckFloatAnimation(box.x - Camera::CheckInstance().screenPosition.x) 
    && (box.y - Camera::CheckInstance().screenPosition.y)) {
        sp->RenderTexture(box.x - Camera::CheckInstance().screenPosition.x, box.y - Camera::CheckInstance().screenPosition.y);
    } else{
        Log::instance.info("Float is not valid!");                  
    }
}


