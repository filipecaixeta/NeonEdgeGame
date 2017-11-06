/**
    Copyright 2017 Neon Edge Game
    File Name: Timer.cpp
    Header File Name: Timer.h
    Class Name: Timer
    Objective: manages the timers.
*/

#include <algorithm>
#include <assert.h>
#include "Timer.h"

Timer::Timer() {
}

Timer::Timer(float limit) {
	assert(limit > MIN_FLOAT || limit < MAX_FLOAT);
    Timer::limit = limit;
}

Timer::~Timer() {
}

/*
    Objective: start timer.
    @param: none.
    @return: none.

*/
void Timer::Start() {
    time = 0;
	assert(time > MIN_FLOAT || time < MAX_FLOAT);
    running = true;
}

/*
    Objective: stop timer.
    @param: none.
    @return: none.

*/
void Timer::Stop() {
    running = false;
}

/*
    Objective: reset timer.
    @param: none.
    @return: none.

*/
void Timer::Reset() {
    time = 0;
	assert(time > MIN_FLOAT || time < MAX_FLOAT);
    running = false;
}

/*
    Objective: update timer.
    @param: float dt.
    @return: none.

*/
void Timer::Update(float dt) {
    if (running) { // check if is running
        time += dt;
		assert(time > MIN_FLOAT || time < MAX_FLOAT);
        if (time >= limit) { // check if time >= limit
            running = false;
        }
    }
}

/*
    Objective: set timer limite.
    @param: float 1.
    @return: none.

*/
void Timer::SetLimit(float main_limit) {
	assert(main_limit > MIN_FLOAT || main_limit < MAX_FLOAT);
    limit = main_limit;
}

/*
    @Objective: check if timer is running.
    @param: none.
    @return: bool running.

*/
bool Timer::IsRunning() {
    return running;
}

/*
    Objective: get timer remaining.
    @param: none.
    @return: float time remainig.

*/
float Timer::GetElapsed() {
    return std::min(1.0f, time/limit);
}

/*
    Objective: get timer.
    @param: none.
    @return: float time.

*/
float Timer::GetTime() {
	assert(time > MIN_FLOAT || time < MAX_FLOAT);
    return time;
}
