#include <algorithm>

#include "Timer.h"

Timer::Timer() {
}

Timer::Timer(float limit) {
    Timer::limit = limit;
}

Timer::~Timer() {
}

void Timer::Start() {
    time = 0;
    running = true;
}

void Timer::Stop() {
    running = false;
}

void Timer::Reset() {
    time = 0;
    running = false;
}

void Timer::Update(float dt) {
    if (running) {
        time += dt;
        if (time >= limit) {
            running = false;
        }
    }
}

void Timer::SetLimit(float l) {
    limit = l;
}

bool Timer::IsRunning() {
    return running;
}

float Timer::GetElapsed() {
    return std::min(1.0f, time/limit);
}

float Timer::GetTime() {
    return time;
}
