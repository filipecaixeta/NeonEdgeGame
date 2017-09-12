/*
  Copyright 2017 Neon Edge Game
  File Name: Timer.cpp
  Header File Name: Timer.h
  Class Name: Timer
  Objective: manages the timers.
*/

#include <algorithm>
#include "Timer.h"

Timer::Timer() {
}

Timer::Timer(float limit) {
    Timer::limit = limit;
}

Timer::~Timer() {
}

/*
  Function Objective: start timer.
  param: none.
  return: none.
*/

void Timer::Start() {
    time = 0;
    running = true;
}

/*
  Function Objective: stop timer.
  param: none.
  return: none.
*/

void Timer::Stop() {
    running = false;
}

/*
  Function Objective: reset timer.
  param: none.
  return: none.
*/

void Timer::Reset() {
    time = 0;
    running = false;
}

/*
  Function Objective: update timer.
  param: none.
  return: none.
*/

void Timer::Update(float dt) {
    if (running) {
        time += dt;
        if (time >= limit) {
            running = false;
        }
    }
}

/*
  Function Objective: set timer limite.
  param: none.
  return: none.
*/

void Timer::SetLimit(float l) {
    limit = l;
}

/*
  Function Objective: check if timer is running.
  param: none.
  return: none.
*/

bool Timer::IsRunning() {
    return running;
}

/*
  Function Objective: get timer remaining.
  param: none.
  return: none.
*/

float Timer::GetElapsed() {
    return std::min(1.0f, time/limit);
}

/*
  Function Objective: get timer.
  param: none.
  return: none.
*/

float Timer::GetTime() {
    return time;
}
